// SCU COEN 146
//
// This program implements the server side of stop & wait protocol
// the server receives file contents from a client
//
//
// For the stop and wait protocol, the assumestions are:
//      -- packet corruption, and packet loss

#include "tfv1.h"

// Global Variables
int state = 0; // we only have two states: 0 and 1
int sock;
struct sockaddr_in serverAddr;
socklen_t addr_size;

// List of functions
int main (int, char *[]);
int my_receive (PACKET *);
int calc_checksum (char *, int);

int main (int argc, char *argv[])
{
	FILE	*fp;
	int		n;
	PACKET	buf;

	// Port must be specified in as CLI argument
    if (argc != 2)
    {
        printf ("need the port number\n");
        return 1;
    }
    
    // Server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = atoi(argv[1]);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Create socket
	if ((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("socket error\n");
		return 1;
	}

	// Bind Socket
	if (bind (sock, (struct sockaddr *)&serverAddr, sizeof (serverAddr)) != 0)
	{
		printf ("bind error\n");
		return 1;
	}

	printf ("socket succesfully binded\n");

    // NOTE: this program uses UDP socket, so there is no need to listen to incoming connections!
    
	// Receive name of file using my_receive()
    // my_receive() function ensures the received data chunks are not corrupted
	if ((n = my_receive (&buf)) <= 0)
	{
		printf ("could not get the name of the file\n");
		return 1;
	}
    printf ("File name has been received!\n");
    
	// Open file
	if ((fp = fopen (buf.data, "wb")) == NULL)
	{
		printf ("error fopen\n");
		return 1;
	}

	printf ("Receiving file %s ... \n", buf.data);

    // my_receive() function ensures the received data chunks are not corrupted
	while ((n = my_receive (&buf)) > 0)
	{
		printf ("writing to file... n = %d\n", n);
        // STUDENT WORK
		// Write received data to file
		if (fwrite(&buf.data, sizeof(char), n, fp) != n) {
			printf("error fwrite");
			return 1;
		}
	}

	close (sock);
	fclose (fp);
	return 0;
}

// My_receive() function ensures the received data chunks are not corrupted
int my_receive (PACKET *recv_pck)
{
    int cs_in;
	int cs_calc;
	int	d;
	int r;
	int nbytes;

	HEADER			ack_packet;
	struct sockaddr	ret_addr;
	socklen_t		addr_size = sizeof (ret_addr);

	while (1)
	{
        // ssize_t recvfrom(int socket, void *restrict buffer, size_t length,
        //          int flags, struct sockaddr *restrict address, socklen_t *restrict address_len);
        // buffer: Points to the buffer where the message should be stored.
        // address: A null pointer, or points to a sockaddr structure in which the sending address is to be stored.
        // The length and format of the address depend on the address family of the socket.
        // address_len: Specifies the length of the sockaddr structure pointed to by the address argument.
		printf("Server port %d\n", serverAddr.sin_port);
		if ((nbytes = recvfrom (sock, recv_pck, sizeof(PACKET), 0, &ret_addr, &addr_size)) < 0)
	
			return -1;
	
        printf ("Received a UDP packet!\n");
        
		cs_in = recv_pck->header.checksum;
		recv_pck->header.checksum = 0;
        
		// STUDENT WORK
        // Recalculate checksum  
		cs_calc = calc_checksum(recv_pck, sizeof(HEADER) + recv_pck->header.len);
        
        // Check if checksum matches, and the sequence number is correct too
        if (cs_in == cs_calc  &&  recv_pck->header.seq_ack == state)
		{
            printf ("Checksum passed! Sequence number matched!\n");

			// STUDENT WORK
			// Good packet
            ack_packet.seq_ack = state;
			ack_packet.len = 0;
			ack_packet.checksum = calc_checksum((char *)&ack_packet, sizeof (HEADER) + ack_packet.len);
            
			// STUDENT WORK
            // simulating erroneous channel...corruption and loss

			// 20% chance of corruption (resets checksum)
			r = rand() % 10;
			if(r<2){
				printf("Packet corrupted!\n");
				ack_packet.checksum = 0;
			}

			// 20% chance of packet loss, otherwise send data to socket
			r = rand() % 10;
			if(r<2)
				printf("Packet lost!\n");
			else
				sendto(sock, &ack_packet, sizeof(HEADER), 0, (struct sockaddr *) &ret_addr, sizeof(ret_addr));
            
            // STUDENT WORK
			// Expecting next packet (change state)
            state = !state;
			return recv_pck->header.len;
		}
		else
		{
            printf ("Checksum/sequence number check failed!\n");

            // STUDENT WORK
			// Bad packet
            ack_packet.seq_ack = !state;
			ack_packet.checksum = 0;
            ack_packet.len = 0;
        	ack_packet.checksum = calc_checksum(&ack_packet, sizeof(HEADER) + ack_packet.len);

            printf ("Resending ack for sequence number: %d...\n", ack_packet.seq_ack );

			// STUDENT WORK
            // simulating erroneous channel...corruption and loss
            

			// 20% chance of corruption (resets checksum)
			r = rand() % 10;
			if(r<2){
				printf("Packet corrupted!\n");
				ack_packet.checksum = 0;
			}

			// 20% chance of packet loss, otherwise send data to socket
			r = rand() % 10;
			if(r<2)
				printf("Packet lost!\n");
			else
				sendto(sock, &ack_packet, sizeof(HEADER), 0, (struct sockaddr *) &ret_addr, sizeof(ret_addr));
            
		}

	}

	return -1;
}

// Checksum function
int calc_checksum (char *buf, int tbytes)
{
    int     i;
    char    cs = 0;
    char    *p;

    // STUDENT WORK
	// Use XOR with all bytes
	for(i=0; i<tbytes; i++)
		cs ^= buf[i];
    
    return (int)cs;
}

