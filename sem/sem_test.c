#include"comm.h"
#include"unistd.h"

int main()
{
   int semid=createSemSet(1);
   initSemSet(semid,0);
   
   pid_t id=fork();
   if(id==0)     //child success
   { 
     while(1)
     {
       P(semid,0);
       printf("A");
       fflush(stdout);
       usleep(5000);
       printf("A");
       fflush(stdout);
       usleep(10000);
       V(semid,0);
     }
   }
   else
   {   
     while(1)
     {
       P(semid,0);
       printf("B");
       fflush(stdout);
       usleep(100000);
       printf("B");
       fflush(stdout);
       usleep(120000);
       V(semid,0);
     }
     wait(NULL);
   }
   destorySemSet(semid);
   return 0;
}
