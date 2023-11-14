#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MYPORT 33500
#define CPORT 40000

int main(){
 int sockfdc;
 struct sockaddr_in my_addr, s_addr;
 char name="Message from client";
 
 sockfdc= socket(AF_INET,SOCK_DGRAM,0);
 if(sockfdc==-1){
  printf("Socket Creation Failed!!!\n");
 }
 else{
  printf("Socket Creation Successful\n");
 }
 
 my_addr.sin_family= AF_INET;
 my_addr.sin_port= htons(MYPORT);
 my_addr.sin_addr.s_addr = INADDR_ANY;
 
 if(bind(sockfdc,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==0){
  printf("Binding Successful\n");
 }
 else{
  printf("Binding Failed!!!\n");
 }
 
 s_addr.sin_family= AF_INET;
 s_addr.sin_port= htons(CPORT);
 s_addr.sin_addr.s_addr = INADDR_ANY;
 
 sendto(sockfdc, name, sizeof(name),0,(struct sockaddr*)&s_addr,sizeof(s_addr));
 
 close(sockfdc);
 
 return 0;
}
