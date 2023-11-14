#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
int main() {
  int sockfd2399, client_sock2399;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len;
  char buffer[1024];

  sockfd2399 = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd2399 < 0) {
    printf("Socket Creation Failed!!!");
    exit(1);
  }
  else{
   printf("\nSocket Creation Successful");
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sockfd2399, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("\nBinding Failed!!!");
    exit(1);
  }
  else{
   printf("\nBinding Successful");
  }

  if (listen(sockfd2399, 1) < 0) {
    printf("\nCannot listen");
    exit(1);
  }
  else{
   printf("\nListening");
  }

  client_len = sizeof(client_addr);
  client_sock2399 = accept(sockfd2399, (struct sockaddr*)&client_addr, &client_len);
  if (client_sock2399 < 0) {
    printf("\nAccept not possible");
    exit(1);
  }

  
  recv(client_sock2399, buffer, sizeof(buffer), 0);

  int char_count = strlen(buffer);

  send(client_sock2399, &char_count, sizeof(char_count), 0);
  printf("\nWord count sent to client\n");


  close(client_sock2399);
  close(sockfd2399);

  return 0;
}
