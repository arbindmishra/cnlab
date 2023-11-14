#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[MAXBUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("socket creation failed!!!");
        exit(1);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("binding failed");
        close(sockfd);
        exit(1);
    }

    printf("Server is waiting for data...\n");

    while (1) {
        // Receive data from client
        ssize_t received_bytes = recvfrom(sockfd, buffer, MAXBUFLEN - 1, 0, (struct sockaddr *)&client_addr, &client_len);
        if (received_bytes == -1) {
            printf("Receive Failed!!!");
            close(sockfd);
            exit(1);
        }
        buffer[received_bytes] = '\0'; // Null-terminate the received data

        // Check if the client wants to close the connection
        if (strcmp(buffer, "bye") == 0) {
            printf("Client closed the connection.\n");
            break; // Exit the loop to close the server
        }

        // Print received message and client information
        printf("Received from client: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

