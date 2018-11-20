#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "Process.h"
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

///Defined in the Above graph ^^
typedef struct Node
{
    Process data;
    struct Node* next;//POINTER TO THE ONLY TOP NODE
} Node;
typedef struct Queue
{
    Node* Top;//POINTER TO THE ONLY TOP NODE
} Queue;
Queue* init();
/**
* function to Add elements to the Queue
*
*@param q
*       The Queue Pointer which the requested Process will be put in
*@param t
*       The Process which will be added to the Queue
*/
void Enqueue(Queue* q,Process t);
/**
* function to Dequeue elements from the Queue
*
*@param q
*       The Queue Pointer which it will Dequeue element from
*/
Process Dequeue(Queue* q);
/**
* function to Check if Queue is Empty
*
*@param q
*       The Queue Pointer which it will query about its state
*@return int
*       1 for Empty
*       else for Not Empty
*/
int isEmpty(Queue* q);
/**
* function to free Queue memory
*
*@param q
*       The Queue Pointer which it will Destruct(free its memory)
*/
void Destroy(Queue* q);

#endif // QUEUE_H_INCLUDED
