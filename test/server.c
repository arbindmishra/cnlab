//Client will send a set of numbers till "ZERO" is entered. After receiving "ZERO" the server will send SUM of those numbers to client.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 23990
#define BACKLOG 5

int main(){
 int srvsck2399,clisck2399;
 struct sockaddr_in serv_addr,cli_addr;
 socklen_t cli_addr_len=sizeof(cli_addr);
 int num;
 int sum=0;

 srvsck2399=socket(PF_INET,SOCK_STREAM,0);
 if(srvsck2399==-1){
  printf("\nSocket Creation Failed!");
  exit(1);
 }
 else{
  printf("\nSocket Creation Successful");
 }
 
 
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_port=htons(PORT);
 serv_addr.sin_addr.s_addr=INADDR_ANY;
 
 
 //Binding is necessary before listening as it tells OS where to listen for incoming connections
 
 if(bind(srvsck2399,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
  printf("\nBinding Failed!!!");
  close(srvsck2399);
  exit(1);
 }
 else{
  printf("\nBinding Successful");
 }
 
 
 if(listen(srvsck2399,BACKLOG)==-1){
  printf("\nCannot Listen to the connections");
  exit(1);
 }
 else{
  printf("\nServer listening to port %d",PORT);
 }
 
 
 clisck2399=accept(srvsck2399,(struct sockaddr*)&cli_addr,&cli_addr_len);
 if(clisck2399==-1){
  printf("\nCannot Accept The Connection\n");
  exit(1); 
 }
 else{
  printf("\nClient Connected Successfully\n");
 }
 
 while(1){
  ssize_t receivedBytes=recv(clisck2399,&num,sizeof(sum),0);
  
  if(receivedBytes<=0){
   printf("Error");
   exit(1);
  }
  
  if(num==0){
   send(clisck2399,&sum,sizeof(sum),0);
   exit(1);
  }
  else{
   sum+=num;
  }
 }
 
 close(clisck2399);
 close(srvsck2399);
 
 return 0;

}
