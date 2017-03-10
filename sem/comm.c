#include"comm.h"


static int commSemSet(int nums,int flags)
{
   key_t _k=ftok(PATHNAME,PROJID);
   int semid=semget(_k,nums,flags);
   if(semid<0)
   {
     perror("semget");
     return -1;
   }
   return semid;
}
int createSemSet(int nums)
{
   int flags=IPC_CREAT|IPC_EXCL|0666;
   return commSemSet(nums, flags);
}


int initSemSet(int semid,int which)
{
    union semun un;
    un.val=1;
    int ret=semctl(semid,which,SETVAL,un);
    if(ret<0)
    {
       perror("semctl");
       return -1;     
    }
    return 0;
}

int getSemSet()
{ 
   return commSemSet(0,0);
}

static int semOp(int semid,int which,int op)
{
   struct sembuf buf;
   buf.sem_num=which;
   buf.sem_op=op;
   buf.sem_flg=0;
   int ret=semop(semid,&buf,1);
   if(ret<0)
   {
     perror("semop");
     return -1;
   }
   return 0;   
}

int P(int semid,int which)
{      
  return semOp(semid,which,-1);
}

int V(int semid,int which)
{
  return semOp(semid,which,1);
}

int destorySemSet(int semid)
{
   int ret=semctl(semid,0,IPC_RMID);
   if(ret<0)
   {
      perror("semctl");
      return -1;
   }
   return 0;   
}
