#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define PORT 23990
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in sr;
    socklen_t sr_len = sizeof(sr);
    char buffer[MAXBUFLEN];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("socket failed");
        exit(1);
    }

    // Configure server address
    memset(&sr, 0, sizeof(sr));
    sr.sin_family = AF_INET;
    sr.sin_port = htons(PORT);
    sr.sin_addr.s_addr=inet_addr(SERVER_IP);

    int num1, num2;

    // Input two numbers
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    // Send the numbers to the server
    snprintf(buffer, MAXBUFLEN, "%d %d", num1, num2);
    if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&sr, sr_len) == -1) {
        printf("sendto failed");
        close(sockfd);
        exit(1);
    }

    // Receive and display the result from the server
    ssize_t received_bytes = recvfrom(sockfd, buffer, MAXBUFLEN - 1, 0, (struct sockaddr *)&sr, &sr_len);
    if (received_bytes == -1) {
        printf("recvfrom failed");
        close(sockfd);
        exit(1);
    }
    buffer[received_bytes] = '\0';
    printf("Server response: %s\n", buffer);

    close(sockfd);
    return 0;
}

