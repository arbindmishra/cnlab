#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "192.168.1.9"
#define PORT 12345
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    char buffer[MAXBUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr=inet_addr(SERVER_IP);

    while (1) {
        // Input a message
        printf("Enter a message (or 'bye' to close the connection): ");
        fgets(buffer, MAXBUFLEN, stdin);

        // Send the message to the server
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
            perror("sendto");
            close(sockfd);
            exit(1);
        }

        // Check if the client wants to close the connection
        if (strcmp(buffer, "bye\n") == 0) {
            printf("Closing the connection.\n");
            break; // Exit the loop to close the client
        }
    }

    close(sockfd);
    return 0;
}

