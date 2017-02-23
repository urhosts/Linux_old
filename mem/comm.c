#include"comm.h"

static int CommShm(int flags)
{
   key_t _k=ftok(PATHNAME,PROJID);
   if(_k<0)
   {
     perror("ftok");
     return -1;
   }
   int shmid=shmget(_k,SIZE,flags);
   if(shmid<0)
   {
     perror("shmget");
     return -2;
   }
    return shmid;
}

int CreateShm()
{
    return CommShm(IPC_CREAT|IPC_EXCL|0666);
}
int GetShm()
{
    return CommShm(IPC_CREAT);
}
int DestoryShm(int shmid)
{
    if(shmctl(shmid,IPC_RMID,NULL)<0)
    {
      perror("shmctl");
      return -1;
    }
    return 0;
}
