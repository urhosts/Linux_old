#include"comm.h"

int main()
{
   int shmid=GetShm();
   char* mem=(char*)shmat(shmid,NULL,0);
   
   int i=0;
   while(1)
   {
      sleep(1);
      mem[i++]='A';
      i%=(SIZE-1);
      mem[SIZE]='\0';
   }
   shmdt(mem);
   return 0;
}
