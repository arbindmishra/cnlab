#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MYPORT 33500
#define CPORT 40000

int main(){
 int sockfds;
 struct sockaddr_in my_addr,c_addr;
 socklen_t addr_len=sizeof(struct sockaddr);
 int receive1;
 int receive2;
 
 sockfds= socket(AF_INET,SOCK_DGRAM,0);
 if(sockfds==-1){
  printf("Socket Creation Failed!!!\n");
 }
 else{
  printf("Socket Creation Successful\n");
 }
 
 my_addr.sin_family= AF_INET;
 my_addr.sin_port= htons(CPORT);
 my_addr.sin_addr.s_addr = INADDR_ANY;
 
 if(bind(sockfds,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==0){
  printf("Binding Successful\n");
 }
 else{
  printf("Binding Failed!!!\n");
 }
 
 int r=recvfrom(sockfds,receive1,sizeof(receive),0,(struct sockaddr*)&c_addr,&addr_len);
 if(r==-1){
   printf("Error");	 
 }
 else{
  printf("Message Received");
  printf("%d\n",receive1);
 }
 
 int r1=recvfrom(sockfds,receive1,sizeof(receive),0,(struct sockaddr*)&c_addr,&addr_len);
 if(r1==-1){
   printf("Error");	 
 }
 else{
  printf("Message Received");
  printf("%d\n",receive2);
 }
 
 //c_addr.sin_family=AF_INET;
 //c_addr.sin_port=htons(33500);
 //c_addr.sin_addr.s_addr= INADDR_ANY;
 
	 
 
 close(sockfds);
 
 return 0;
}
