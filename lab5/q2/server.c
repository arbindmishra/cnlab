#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 23990
#define MAXBUFLEN 1024

int main() {
    int sockfd;
    struct sockaddr_in sr, cl;
    socklen_t cl_len = sizeof(cl);
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
    sr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&sr, sizeof(sr)) == -1) {
        printf("bind failed");
        close(sockfd);
        exit(1);
    }

    printf("Server is waiting for data...\n");

    while (1) {
        // Receive two numbers from the client
        int num1, num2;
        ssize_t received_bytes = recvfrom(sockfd, buffer, MAXBUFLEN - 1, 0, (struct sockaddr *)&cl, &cl_len);
        if (received_bytes == -1) {
            printf("recvfrom failed");
            close(sockfd);
            exit(1);
        }
        buffer[received_bytes] = '\0';
        sscanf(buffer, "%d %d", &num1, &num2);

        // Calculate the sum
        int sum = num1 + num2;

        // Send the result back to the client
        snprintf(buffer, MAXBUFLEN, "Sum: %d", sum);
        if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cl, cl_len) == -1) {
            printf("sendto failed");
            close(sockfd);
            exit(1);
        }
        printf("Received: %d and %d, Result: %d\n", num1, num2, sum);
    }

    close(sockfd);
    return 0;
}


