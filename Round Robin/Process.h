#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Process
{
    char name[10];
    int sT;//Start Time
    int eT;//End Time
} Process;
#include "Queue.h"
/**
* Reads Input from a file
*
*@param path
*       file path which holds the input
*@param PArr
*       array of Processes which we will save our inputs to
*@param s
*       size of the Processes array
*/
int readInputs(const char* path,Process* PArr,int* s);
/**
* Do the RR Algorithm
*
*@param PArr
*       array of Processes which we will load our inputs from
*@param watchTime
*       The Range Which will the RR Algorithm will work on
*/
void roundRobinAlgorithm(Process* PArr,int s,int watchTime);
#endif // PROCESS_H_INCLUDED
