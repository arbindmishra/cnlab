#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1 "
#define PORT 23990
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in sr_addr;
    socklen_t sr_addr_len = sizeof(sr_addr);
    char buffer[MAXBUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("socket failed");
        exit(1);
    }

    // Configure server address
    memset(&sr_addr, 0, sizeof(sr_addr));
    sr_addr.sin_family = AF_INET;
    sr_addr.sin_port = htons(PORT);
    sr_addr.sin_addr.s_addr=inet_addr(SERVER_IP);

    const char *message = "Hello from client";

    // Send a message to the server
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&sr_addr, sr_addr_len) == -1) {
        printf("sendto failed");
        close(sockfd);
        exit(1);
    }

    // Receive a response from the server
    ssize_t received_bytes = recvfrom(sockfd, buffer, MAXBUFLEN - 1, 0, (struct sockaddr *)&sr_addr, &sr_addr_len);
    if (received_bytes == -1) {
        printf("recvfrom failed");
        close(sockfd);
        exit(1);
    }
    buffer[received_bytes] = '\0'; // Null-terminate the received data

    printf("Received from server: %s\n", buffer);

    close(sockfd);
    return 0;
}

