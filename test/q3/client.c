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

  
  sockfd2399 = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd2399 < 0) {
    printf("Socket Creation Failed!!!");
    exit(1);
  }
  else{
   printf("Socket Creation Successful");
  }

  
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  
  if (connect(sockfd2399, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    printf("Connection Failed!!!");
    exit(1);
  }
  else{
   printf("Connection Successful");  
  }

  
  char string[1024];
  printf("Enter a string: ");
  scanf("%s", string);

  
  send(sockfd2399, string, strlen(string) + 1, 0);

  
  int word_count, char_count, vowel_count;
  recv(sockfd2399, &word_count, sizeof(word_count), 0);
  recv(sockfd2399, &char_count, sizeof(char_count), 0);
  recv(sockfd2399, &vowel_count, sizeof(vowel_count), 0);

  
  printf("The word count is: %d\n", word_count);
  printf("The character count is: %d\n", char_count);
  printf("The vowel count is: %d\n", vowel_count);

  
  close(sockfd2399);

  return 0;
}
