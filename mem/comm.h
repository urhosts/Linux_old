#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>



#define PATHNAME "."
#define PROJID 0x6666
#define SIZE 4096*1


int CreateShm();
int GetShm();
int DestoryShm(int shmid);

#endif
