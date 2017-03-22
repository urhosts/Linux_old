#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int fd[2];
    int ret=socketpair(PF_LOCAL,SOCK_STREAM,0,fd);
    if(ret!=0)
    {
        perror("socketpair");
        return -1;
    }

    pid_t id=fork();
    if(id<0)
    {
        perror("fork");
        return id;
    }
    else if(id==0)    //child
    {
        const char* msg="hello world!";
        char buf[1024];
        close(fd[0]);     //close stdin
        while(1)
        {
            memset(buf,0,sizeof(buf));
            strcpy(buf,msg);
            write(fd[1],buf,sizeof(buf));
            read(fd[1],buf,sizeof(buf));
            sleep(1);
            printf("client say:%s\n",buf);
        }
    }
    else
    {
        //father
        const char* msg="hello world!";
        close(fd[1]);   
        char buf[1024];
        while(1)
        {
            memset(buf,0,sizeof(buf));
            read(fd[0],buf,sizeof(buf));
            printf("father echo:%s\n",buf);
            strcpy(buf,msg);
            write(fd[0],buf,sizeof(buf));
        }
    }
    return 0;
}
