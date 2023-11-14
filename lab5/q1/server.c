#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 23990
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in sr_addr, cl_addr;
    socklen_t client_len = sizeof(cl_addr);
    char buffer[MAXBUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("socket creation failed");
        exit(1);
    }

    // Configure server address
    memset(&sr_addr, 0, sizeof(sr_addr));
    sr_addr.sin_family = AF_INET;
    sr_addr.sin_port = htons(PORT);
    sr_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&sr_addr, sizeof(sr_addr)) == -1) {
        printf("bind failed");
        close(sockfd);
        exit(1);
    }

    printf("Server is waiting for data...\n");

    while (1) {
        // Receive data from client
        ssize_t received_bytes = recvfrom(sockfd, buffer, MAXBUFLEN - 1, 0, (struct sockaddr *)&cl_addr, &client_len);
        if (received_bytes == -1) {
            printf("recvfrom failed");
            close(sockfd);
            exit(1);
        }
        buffer[received_bytes] = '\0'; // Null-terminate the received data

        // Print received message and client information
        printf("Received from client: %s\n", buffer);

        // Send a response to the client
        const char *response = "Hello from server!";
        if (sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cl_addr, client_len) == -1) {
            printf("sendto failed");
            close(sockfd);
            exit(1);
        }
    }

    close(sockfd);
    return 0;
}


