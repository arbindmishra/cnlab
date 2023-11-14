#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 23990
#define BACKLOG 5

int main(){
 int srvsck,clisck;
 struct sockaddr_in serv_addr,cli_addr;
 socklen_t cli_addr_len=sizeof(cli_addr);

 srvsck=socket(PF_INET,SOCK_STREAM,0);
 if(srvsck==-1){
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
 
 if(bind(srvsck,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
  printf("\nBinding Failed!!!");
  close(srvsck);
  exit(1);
 }
 else{
  printf("\nBinding Successful");
 }
 
 
 if(listen(srvsck,BACKLOG)==-1){
  printf("\nCannot Listen to the connections");
  exit(1);
 }
 else{
  printf("\nServer listening to port %d",PORT);
 }
 
 
 clisck=accept(srvsck,(struct sockaddr*)&cli_addr,&cli_addr_len);
 if(clisck==-1){
  printf("\nCannot Accept The Connection\n");
  exit(1); 
 }
 else{
  printf("\nClient Connected Successfully\n");
 }
 
 
 
 close(clisck);
 close(srvsck);
 
 return 0;

}
