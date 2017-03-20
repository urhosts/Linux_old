#include<stdio.h>
#include<stdlib.h>
#include<poll.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int startup(const char* _ip,int _port)
{
    assert(_ip);
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(2);
    }

    int opt=1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_port=htons(argv[2]);
    local.sin_addr.s_addr=inet_addr(agrv[1]);

    socklen_t len=sizeof(local);
    if(bind(sock,(struct sockaddr*)&local,len)<0)
    {
        perror("bind");
        exit(3);
    }
    if(listen(sock,5)<0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("Usage:%s [local_ip] [local_port]\n",argv[0]);
        exit(1);
    }

    int listen_sock=startup(atoi(argv[2]),argv[1]);
    while(1)
    {
        struct pollfd in_fds
        switch(poll())
        
    }

        



 return 0;  
}
