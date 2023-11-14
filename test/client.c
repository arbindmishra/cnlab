


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 23990
#define SERVER_IP "127.0.0.1"

int main(){
 int sockfd2399;
 struct sockaddr_in serv_addr;
 int num;
 
 sockfd2399=socket(PF_INET,SOCK_STREAM,0);
 if(sockfd2399==-1){
  printf("\nSocket Creation Failed!");
 }
 else{
  printf("\nSocket Creation Successful");
 }
 
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_port=htons(PORT);
 serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
 
 if(connect(sockfd2399,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
  printf("\nConnection to server failed\n");
  exit(1);
 }
 else{
  printf("\nConnected to Server\n");
 }
 
 while(1){
  printf("Enter a number or 0 to stop");
  scanf("%d",&num);
  
  send(sockfd2399,&num,sizeof(num),0);
  
  if(num==0){
   int sum;
   recv(sockfd2399,&sum,sizeof(sum),0);
   printf("Sum of the numbers: %d\n",sum);
   exit(1);
  }
 }
 
 
 
 close(sockfd2399);
 
 return 0;

}
