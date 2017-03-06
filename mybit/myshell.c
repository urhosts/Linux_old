#include<unistd.h>
#include<ctype.h>
#include<stdio.h>
int main()
{
   while(1)
   { 
     printf("[ld@localhost myshell]#");
     fflush(stdout);
     char line[1024];
     ssize_t ret=read(0,line,1024);
     char *argv[20];
     char *start=line;
     argv[0]=start;
     int index=1;
     if(ret > 0)     //read successfully
     {
        while(*start)
        {
           if(isspace(*start)) //is space
           {
             *start='\0';
             start++;
             argv[index++]=start;
           } 
           else
           {
             start++;              
           }
        }
     }
     else    //read error
     {
        continue;
     }
     argv[index-1]=NULL;
     pid_t id=fork();
     if(id==0)
     {//child
       execvp(argv[0],argv);
     }
     else
     {
       sleep(1);
       wait(NULL);
     } 
  }
  return 0;
}
