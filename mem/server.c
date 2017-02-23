#include"comm.h"

int main()
{
   int shmid=CreateShm();
   printf("%d\n",shmid);
   char* mem=(char*)shmat(shmid,NULL,0);
   while(1)
   {
      sleep(1);
      printf("%s\n",mem);
   }
   shmdt(mem);
   DestoryShm(shmid);
   return 0;
}
