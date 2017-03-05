#pragma once

#ifndef COMM_H
#define COMM_H

#include<stdio.h>
#include<sys/types.h>
#include<ipc.h>

#define PATHNAME
#define PROJID



int createmsgqueue();
int getmsgqueue();
int sendmessage();
int receivemessage();
int destorymsgqueue();


#endif  //COMM_H
