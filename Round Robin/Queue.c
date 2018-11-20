#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
//#define Process Process
/**
********************************************************
********************QUEUE DATASTRUCTURE*****************
********************************************************
*              NODE       NODE       NODE              *
*  pt          +------+ pt +------+ pt +------+ pt     *
* TOP->        | data | -> | data | -> | data | -> NULL*
*              +------+    +------+    +------+        *
********************************************************
********************************************************
********************************************************
**/
Queue* init()
{
    Queue* q;
    q=(Queue*)malloc(sizeof(Queue));
    q->Top=NULL;
    return q;
}


void Enqueue(Queue* q,Process t)
{
    if(q->Top==NULL)
    {
        q->Top=(Node*)malloc(sizeof(Node));
        q->Top->data=t;
        q->Top->next=NULL;
        return;
    }
    Node* iterator=q->Top;
    while(iterator->next!=NULL)
    {
        iterator=iterator->next;
    }
    iterator->next=(Node*)malloc(sizeof(Node));
    iterator=iterator->next;
    iterator->next=NULL;
    iterator->data=t;
}


Process Dequeue(Queue* q)
{
    Node* iterator=q->Top;
    q->Top=q->Top->next;
    Process value=iterator->data;
    free(iterator);
    return value;
}


void Destroy(Queue* q)
{
    if(q->Top!=NULL)free(q->Top);
    free(q);
}


int isEmpty(Queue* q)
{
    return !q->Top;
}
