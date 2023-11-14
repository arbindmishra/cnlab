#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
 int sockfds_tcp;
 struct sockaddr_in my_addr;
 
 sockfds_tcp= socket(AF_INET,SOCK_STREAM,0);
 if(sockfds_tcp==-1){
  printf("Socket Creation Failed!!!\n");
 }
 else{
  printf("Socket Creation Successful\n");
 }
 
 my_addr.sin_family= AF_INET;
 my_addr.sin_port= htons(8080);
 my_addr.sin_addr.s_addr = INADDR_ANY;
 
 if(bind(sockfds_tcp,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==0){
  printf("Binding Successful\n");
 }
 else{
  printf("Binding Failed!!!\n");
 }
 
 close(sockfds_tcp);

 return 0;
}

