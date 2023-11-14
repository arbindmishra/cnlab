#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
  int sockfd2399;
  struct sockaddr_in server_addr;
  char buffer[1024];
  
  sockfd2399 = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd2399 < 0) {
    printf("\nSocket creation failed!!!");
    exit(1);
  }
  else{
   printf("\nSocket Creation Successful");
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (connect(sockfd2399, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("\nConnection Failed!!!");
    exit(1);
  }
  else{
   printf("\nConnection Successful");
  }

  
  printf("\nEnter a message: ");
  scanf("%s", buffer);

  send(sockfd2399, buffer, strlen(buffer) + 1, 0);

  int char_count;
  recv(sockfd2399, &char_count, sizeof(char_count), 0);

  printf("\nThe number of characters in the message is: %d\n", char_count);

  close(sockfd2399);

  return 0;
}
