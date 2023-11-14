#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MYPORT 5000
#define sport 6000
int main()
{
    int max= 100;
    int sock_c;
    sock_c = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_c == -1)
    {
        printf("error! socket not created\n");
    }
    else
    {
        printf("client udp socket created successfully\n");
    }
    struct sockaddr_in client;
    client.sin_family = AF_INET;        // host byte order
    client.sin_port = htons(MYPORT); // network byte order
    client.sin_addr.s_addr=INADDR_ANY;
    memset(&(client.sin_zero), '\0', 8);
    int b;
    b=bind(sock_c,(const struct sockaddr *)&client,sizeof(struct sockaddr_in));
    if(b==-1){
        puts("client udp bind unsuccessful");
    }else{
        puts("client udp bind success");
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;        
    server.sin_port = htons(sport);
    server.sin_addr.s_addr=INADDR_ANY;
    memset(&(server.sin_zero), '\0', 8);
    char msg[max];
    puts("enter message");
    fgets(msg,max,stdin);
    int s=sendto(sock_c,&msg,strlen(msg),0,(struct sockaddr *)&server,sizeof(struct sockaddr));
    if(s==-1)
        printf("error! send unsuccessful");
    else{
        printf("message sent\n");
        puts(msg);
    }
    
 close(sock_c);
 return 0;
}

