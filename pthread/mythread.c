#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>

void* thread_run(void* arg)
{
   int count=5;
   while(count--)
   {
      sleep(1);
      printf("new thread  pid:%d  ppid:%d  tid:%lu\n",\
                   getpid(),getppid(),pthread_self());    
   }
   printf("new thread run over!\n");
   //return (void*)21;
   //pthread_exit((void*)21);
}

int main()
{
   pthread_t tid;
   int ret=pthread_create(&tid,NULL,thread_run,NULL);
   if(ret<0)
   {
     printf("create thread error!\n");
     return -1;
   }  
    printf("main thread  pid:%d  ppid:%d  tid:%lu\n",\
                   getpid(),getppid(),pthread_self());   
 
    int exitcode=0;  
    pthread_join(tid,(void**)&exitcode);
    printf("join new thread  done!,%d\n",exitcode); 
    return 0;
}










