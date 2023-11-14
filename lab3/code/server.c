#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MYPORT 6000
#define cport 5000
int main()
{
    int max=100;
    int sock_s;
    sock_s = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_s == -1)
    {
        printf("error! socket not created\n");
    }
    else
    {
        printf("server udp socket created successfully\n");
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;        
    server.sin_port = htons(MYPORT);
    server.sin_addr.s_addr=INADDR_ANY;
    memset(&(server.sin_zero), '\0', 8);
    int b;
    b=bind(sock_s,(const struct sockaddr *)&server,sizeof(struct sockaddr_in));
    if(b==-1){
        puts("server udp bind unsuccessful");
    }else{
        puts("server udp bind success");
    }
    struct sockaddr_in client;
    client.sin_family = AF_INET;        
    client.sin_port = htons(cport);
    client.sin_addr.s_addr=INADDR_ANY;
    memset(&(client.sin_zero), '\0', 8);
    char msg[max];
    int s=sizeof(struct sockaddr);
    int r=recvfrom(sock_s,&msg,max,0,(struct sockaddr *)&client,&s);
    if(r==-1)
        printf("error! receive unsuccessful");
    else{
        printf("message received\n");
        puts(msg);
    }
 close(sock_s);
 return 0;
} 
