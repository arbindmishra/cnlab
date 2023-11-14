//TCP CLIENT SERVER CONNECTION


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 23990
#define SERVER_IP "127.0.0.1"

int main(){
 int sockfd;
 struct sockaddr_in serv_addr;
 
 sockfd=socket(PF_INET,SOCK_STREAM,0);
 if(sockfd==-1){
  printf("\nSocket Creation Failed!");
 }
 else{
  printf("\nSocket Creation Successful");
 }
 
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_port=htons(PORT);
 serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
 
 if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
  printf("\nConnection to server failed\n");
  exit(1);
 }
 else{
  printf("\nConnected to Server\n");
 }
 
 
 
 close(sockfd);
 
 return 0;

}
