#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define MAX_CAPACITY 100

int main()
{
    //INIT QUEUE
    Queue* x=init();
    //DECLARED PROCESS ARRAY OF MAX CAPACITY
    Process p[MAX_CAPACITY];
    //SIZE OF THE PROCESS ARRAY
    int size=0;
    //WATCH_TIME WHICH WILL TAKE THE OUTPUT OF THE FUNCTION
    int watchTime= readInputs("process.txt",p,&size);
    //PROCEED WITH RR ALGORITHM
    roundRobinAlgorithm(p,size,watchTime);
    //DESTRUCT THE QUEUE
    Destroy(x);
    system("pause");
    return 0;
}
