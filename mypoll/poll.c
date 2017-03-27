/*************************************************************************
	> File Name: poll.c
	> Author: hosts
	> Mail: hosts@gsxio.com
	> Created Time: Tue 21 Mar 2017 03:21:56 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <libgen.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define MAXNUM 1024

//int startup(char *_ip; int _port)
//{
//    //assert(_ip);
//    int soc = socket(AF_INET, SOCK_STREAM, 0);
//    if(sock < 0)
//    {
//        perror("sock");
//        exit(1);
//    }
//
//    int opt = 1;
//    setsockopt = (sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
//
//    struct sockaddr_in local;
//    local.sin_family = AF_INET;
//    local.sin_port = htons(argv[2]);
//    local.sin_addr.s_addr = inet_addr(argv[1]);
//
//    socklen_t len = sizeof(local);
//    if(bind(sock, (struct sockaddr*)&local, len) < 0)
//    {
//        perror("bind");
//        exit(2);
//    }
//    if(listen(sock, 5) < 0)
//    {
//        perror("listen");
//        exit(3);
//    }
//    return sock;
//}


int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s [ip] [port]\n",basename(argv[1]));
        return 1;
    }

    int port = atoi(argv[2]);
    char *ip = argv[1];
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    inet_aton(ip, &servAddr.sin_addr);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen < 0)
    {
        perror("socket\n");
        return 2;
    }

    int ret = bind(listenfd, (struct sockaddr*)&servAddr, sizeof(servAddr));

    if(ret < 0)
    {
        perror("bind\n");
        return 3;
    }

    ret = listen(listenfd, 5);
    if(ret < 0)
    {
        perror("listen\n");
        return 4;
    }

    struct pollfd pollfds[MAXNUM];
    int maxNum = 1;
    pollfds[0].fd = listenfd;
    pollfds[0].events = POLLIN;
    pollfds[0].revents = 0;

    int timeout = 3000;
    while(1)
    {
        int num = poll(pollfds, maxNum, timeout);
        int i = 0;
        switch(num)
        {
            case -1:
                perror("poll\n");
                break;
            case 0:
                printf("timeout\n");
            default:
                for(i = 0;i < maxNum; i++)
                {
                    if((pollfds[i].fd == listenfd) && (pollfds[i].revents & POLLIN))
                    {
                        struct sockaddr_in clientAddr;
                        socklen_t len = sizeof(clientAddr);
                        int connfd = accept(listenfd, (struct sockaddr*)&clientAddr, &len);
                        if(connfd < 0)
                        {
                            perror("accept\n");
                            return 5;
                        }
                        if(maxNum >= MAXNUM)
                        {
                            char *msg = "sorry, server error, please connect a little";
                            send(connfd, msg, strlen(msg), 0);
                            close(connfd);
                            continue;
                        }
                        pollfds[maxNum].fd = connfd;
                        pollfds[maxNum].events = POLLIN;
                        pollfds[maxNum].revents = 0;
                        maxNum++;
                        printf("come a new client, fd is %d\n",connfd);
                    }
                    else if(pollfds[i].revents & POLLIN)
                    {
                        char buf[1024];
                        memset(buf, '\0', sizeof(buf));
                        ssize_t s = recv(pollfds[i].fd, buf, sizeof(buf)-1, 0);
                        if(s < 0)
                        {
                            perror("recv\n");
                            continue;
                        }
                        else if(s == 0)
                        {
                            printf("client %d is quit!\n", pollfds[i].fd);
                            close(pollfds[i].fd);
                            pollfds[i] = pollfds[maxNum-1];
                            maxNum--;
                            i--;
                        }
                        else
                        {
                            buf[s] = '\0';
                            printf("from client %d# %s\n", pollfds[i].fd, buf);
                        }
                    }
                }
        }
    }
    close(listenfd);
    return 0;
}

//int main(int argc, char *argv[])
//{
//    if( argv != 3 )
//    {
//        printf("Usage: %s [local_ip] [local_port]\n",argv[0]);
//        exit(4);
//    }
//    
//    int timeout = 3000;
//    char buf[1024];
//    struct pollfd fd_poll[1];
//    while(1)
//    {
//        fd_poll[0].fd = 0;
//        fd_poll[0].evenets = POLLIN;
//        fd_poll[0].revents = 0;
//        memset(buf, '\0', sizeof(buf));
//        switch(poll(fd_poll, 1, timeout))
//        {
//            case 0:
//                perror("timeout!");
//                break;
//            case -1:
//                perror("poll");
//                break;
//            default:
//                {
//                    if( fd_poll[0].revents & POLLIN )
//                    {
//                        getc(buf);
//                        printf("buf: %s\n",buf);
//                    }
//                }
//            break;
//        }
//    }
//    return 0;
//}
