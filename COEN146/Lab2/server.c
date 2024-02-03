//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Sever's port number

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    char message[10] = "received!"; // message to be sent to the client when the destination file name is received
    int net_bytes_read;             // numer of bytes received over socket
    int socket_fd = 0;              // socket descriptor
    int connection_fd = 0;          // new connection descriptor
    struct sockaddr_in serv_addr;   // Address format structure
    char net_buff[1024];            // buffer to hold characters read from socket
    FILE *dest_file;                // pointer to the file that will include the received bytes over socket

    if (argc < 2) // Note: the name of the program is counted as an argument
    {
        printf("Port number not specified!\n");
        return 1;
    }
    printf("Starting Server...\n");

    // open socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("ERROR opening socket");
        exit(0);
    }
    printf("Opening Socket...\n");

    // setup sockadd_in structure
    serv_addr.sin_family = AF_INET;                // IPV4
    serv_addr.sin_port = htons(atoi(argv[1]));     // port
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // any IP address

    // bind socket
    bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Binding Socket...\n");

    // start listening on socket
    listen(socket_fd, 10);
    printf("Listening on Socket...\n");

    // start accepting connections on the socket
    connection_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL);
    if (connection_fd < 0)
    {
        perror("ERROR accepting connections");
        exit(0);
    }
    printf("Accepting Connections on Port %s\n", argv[1]);

    // receive file name
    char fileName[sizeof(net_buff)];
    net_bytes_read = read(connection_fd, fileName, sizeof(fileName));
    if (net_bytes_read < 0)
    {
        perror("ERROR reading filename from socket");
        exit(0);
    }

    // send confirmation to user
    int net_bytes_write = write(connection_fd, message, sizeof(message));
    if (net_bytes_write < 0)
    {
        perror("ERROR writing message to socket");
        exit(0);
    }

    // create file in write mode
    dest_file = fopen(fileName, "w");
    if (dest_file == NULL)
    {
        perror("ERROR creating destination file");
        exit(0);
    }

    // read contents from socket to buffer
    while ((net_bytes_read = read(connection_fd, net_buff, sizeof(net_buff))) > 0)
    {
        fwrite(net_buff, sizeof(char), net_bytes_read, dest_file);
    }

    fclose(dest_file);
    close(connection_fd);
    close(socket_fd);

    printf("File transfer completed.\n");
    return 0;
}
