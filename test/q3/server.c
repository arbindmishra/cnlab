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


  sockfd2399 = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd2399 < 0) {
    printf("\nSocket creation failed");
    exit(1);
  }
  else{
   printf("\nSocket creation successful");
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
    printf("\nCannot Listen");
    exit(1);
  }
  else{
   printf("\nListening...");
  }


  client_len = sizeof(client_addr);
  client_sock2399 = accept(sockfd2399, (struct sockaddr*)&client_addr, &client_len);
  if (client_sock2399 < 0) {
    printf("\nCannot Accept");
    exit(1);
  }


  char string[1024];
  recv(client_sock2399, string, sizeof(string), 0);


  int word_count = 1, char_count = 0, vowel_count = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] == ' ') {
      word_count++;
    } else if (string[i] == 'a' || string[i] == 'e' || string[i] == 'i' || string[i] == 'o' || string[i] == 'u') {
      vowel_count++;
    }
    char_count++;
  }

  send(client_sock2399, &word_count, sizeof(word_count), 0);
  send(client_sock2399, &char_count, sizeof(char_count), 0);
  send(client_sock2399, &vowel_count, sizeof(vowel_count), 0);
  printf("All the required information sent to client\n");


  close(client_sock2399);
  close(sockfd2399);

  return 0;
}
