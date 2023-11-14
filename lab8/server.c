#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
int main() {
    int server_socket, client_socket, max_clients = 10;
    int client_sockets[max_clients];
    fd_set readfds;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[1024];
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        puts("Socket creation failed");
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        puts("Binding failed");
    }
    if (listen(server_socket, 5) == -1) {
        puts("Listening failed");
    }
    printf("Server listening on port 8080...\n");
    for (int i = 0; i < max_clients; i++) {
        client_sockets[i] = 0;
    }
    FD_ZERO(&readfds);
    FD_SET(server_socket, &readfds);
    int max_fd = server_socket;
    while (1) {
        fd_set temp = readfds;
        if (select(max_fd + 1, &temp, NULL, NULL, NULL) < 0) {
            puts("Select failed");
        }
        if (FD_ISSET(server_socket, &temp)) {
            client_len = sizeof(client_addr);
            client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
            if (client_socket == -1) {
                puts("Accept failed");
                continue;
            }
            for (int i = 0; i < max_clients; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = client_socket;
                    if (client_socket > max_fd) {
                        max_fd = client_socket;
                    }
                    printf("New connection established\n");
                    break;
                }
            }
            FD_SET(client_socket, &readfds);
        }
        for (int i = 0; i < max_clients; i++) {
            if (client_sockets[i] > 0 && FD_ISSET(client_sockets[i], &temp)) {
                int n = recv(client_sockets[i], buffer, sizeof(buffer), 0);
                if (n <= 0) {
                    printf("Connection closed\n");
                    close(client_sockets[i]);
                    FD_CLR(client_sockets[i], &readfds);
                    client_sockets[i] = 0;
                } else {
                    buffer[n] = '\0';
                    printf("Received from client %d: %s", i, buffer);
                }
            }
        }
    }
    close(server_socket);
    return 0;
}
