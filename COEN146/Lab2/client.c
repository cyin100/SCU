//
// Behnam Dezfouli
// CSEN, Santa Clara University
//
// This program implements a client that connects to a server and transfers the bytes read from a file over the established connection
//
// The input arguments are as follows:
// argv[1]: Sever's IP address
// argv[2]: Server's port number
// argv[3]: Source file
// argv[4]: Destination file at the server side which includes a copy of the source file
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define SIZE 10
int main (int argc, char *argv[])
{
    int sockfd = 0; // socket descriptor
    char net_buff[SIZE]; // to hold the bytes read from socket
    char file_buff[SIZE]; // to hold the bytes read from source file
    struct sockaddr_in serv_addr; // server address structure
    int net_bytes_read; // numer of bytes received over socket
    FILE *source_file; // pointer to the source file
    if (argc < 5)
    {
        printf ("Usage: ./%s <server ip address> <server port number> <source file><destination file>\n", argv[0]);
        return 1;
    }

    // Make sure intial values are zero
    memset (net_buff, '0', sizeof (net_buff));
    memset (file_buff, '0', sizeof (file_buff));
    memset (&serv_addr, '0', sizeof (serv_addr));

    // Parse command line arguments
    const char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    const char *source_file_path = argv[3];
    const char *destination_file = argv[4];

    // Create socket and return if invalid
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("create socket error");
        return 1;
    }

    // Server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    // Convert address to numeric binary form
    if(inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0){
        perror("inet_pton error");
        close(sockfd);
        return 1;
    }
    
    // Connect to the server
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("connect to server error");
        close(sockfd);
        return 1;
    }

    // Open source file for read
    source_file = fopen(source_file_path, "r");
    if(source_file == NULL){
        perror("open file error");
        close(sockfd);
        return 1;
    }

    // Send destination file name
    size_t dest_file_length = strlen(destination_file);
    if(write(sockfd, destination_file, dest_file_length+1) < 0){
        perror("writing dest file name error");
        fclose(source_file);
        close(sockfd);
        return 1;
    }

    // Read confirmation from server
    int n = read(sockfd, net_buff, sizeof(net_buff));
    printf("Confirmation Message from Server: %s\n", net_buff);

    // Read from source file and send to server
    size_t bytes_read;
    while ((bytes_read = fread(file_buff, 1, SIZE, source_file)) > 0){
        size_t bytes_sent = write(sockfd, file_buff, bytes_read);
        if(bytes_sent < 0){
            perror("writing to file error");
            fclose(source_file);
            close(sockfd);
            return 1;
        }
        memset(file_buff, '0', SIZE);
    }

    // Close source file and socket
    fclose(source_file);
    close(sockfd);
    return 0;
}