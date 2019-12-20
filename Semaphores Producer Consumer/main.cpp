#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <termios.h>
#include <vector>
#define SHARED 1
///UTILITY MACROS
#define EMSG "Monitor thread:Buffer full!!\n"
#define DMSG "Collector thread:nothing is in the buffer!\n"
using namespace std;
class RingBuffer;//forward declaring
///--------SHARED MEMORY SECTION------------
sem_t empty, full,mutex,bufferMutex;
pthread_attr_t attr;
int bSize;
RingBuffer* buffer;
int shared_counter;
bool running;
uint32_t t1,t2;//t1 input for monitor sleep , t2 is max rand for other threads
constexpr uint32_t LEAST_SLEEP=10000;//10ms least random sleep
uint32_t nCounterThreads;
///GET CHAR FROM USER [TERMINAL STRUCTS]
static struct termios old, neww;
///--------------------------------

class RingBuffer
{
public:
    RingBuffer(int size)
    {
        buffer=reinterpret_cast<int*>(malloc(size*sizeof(int)));
        start=0;
        end=0;
        bufferSize=size;
        currentSize=0;
    }
    //ASSUMING ONLY POSITIVE VALUES TO ENQUEUE AND DEQUEUE
    int enqueue(int val)
    {
        if(currentSize<bufferSize)
        {
            buffer[end]=val;
            end++;
            end=end%bufferSize;
            currentSize++;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    int dequeue()
    {
        if(currentSize>0)
        {
            int value=buffer[start];
            start++;
            start=start%bufferSize;
            currentSize--;
            return value;
        }
        else
        {
            return -1;
        }
    }
    inline int getCurrentSize()const
    {
        return currentSize;
    }
    inline int getEnd()const
    {
        return end;
    }
    inline int getStart()const
    {
        return start;
    }
private:
    int start;
    int end;
    int bufferSize;
    int currentSize;
    int* buffer;
};

class MCounter
{
public:
    MCounter()
    {
        int* inData=new int;
        *inData = mccounter;
        int ret=pthread_create(&mcid, &attr,count, reinterpret_cast<void*>(inData));
        if(ret!=0)
        {
            printf("mcounter thread could not be created .. , err =%d\n",ret);
        }
        mccounter++;
    }
    void endJob()
    {
        pthread_join(mcid, NULL);
    }
private:
    //let the message be OS scheduling this thread to work.
    static void* count(void* input)
    {
        int mcid=*reinterpret_cast<int*>(input);
        while(running) //infinite loop waiting to get scheduled by OS
        {
            printf("Counter thread %d:received a message\n",mcid);
            if(sem_trywait(&mutex)==0)
            {
                shared_counter++;
                printf("Counter thread %d:now adding to counter,counter value=%d\n",mcid,shared_counter);
            }
            else
            {
                printf("Counter thread %d:waiting to write\n",mcid);
                sem_wait(&mutex);
                shared_counter++;
                printf("Counter thread %d:now adding to counter,counter value=%d\n",mcid,shared_counter);
            }
            sem_post(&mutex);

            usleep((rand()%t2)+LEAST_SLEEP);//randomly sleep at least 1ms to t1 time
        }
        delete input;
        return NULL;
    }
    static int mccounter;
    pthread_t mcid;
};

class Monitor
{
public:
    Monitor()
    {
        int ret=pthread_create(&mid, &attr, monitor, NULL);
        if(ret!=0)
        {
            printf("monitor thread could not be created .. , err =%d\n",ret);
        }
    }
    void endJob()
    {
        pthread_join(mid, NULL);
    }
private:
    static void* monitor(void* input)
    {
        while(running)
        {
            int cval=-1;
///---------------------INTERACTION WITH COUNTER THREADS
            if(sem_trywait(&mutex)==0)
            {
                cval=shared_counter;
                shared_counter=0;
                printf("Monitor thread:reading a count value of %d\n",cval);
            }
            else
            {
                printf("Monitor thread:waiting to read counter\n");
                sem_wait(&mutex);
                cval=shared_counter;
                shared_counter=0;
                printf("Monitor thread:reading a count value of %d\n",cval);
            }
            sem_post(&mutex);
///------------------------------------------------

///---------------------INTERACTION WITH COLLECTOR THREAD
            if(buffer->getCurrentSize()==bSize)
            {
                printf(EMSG);
            }
            sem_wait(&empty);
            if(sem_trywait(&bufferMutex)==0)
            {
                int bpos=buffer->getEnd();
                int ret=buffer->enqueue(cval);
                printf("Monitor thread:writing to buffer at position %d[Current Size=%d]\n",bpos,buffer->getCurrentSize());
            }
            else
            {
                printf("Monitor thread:waiting to write value to buffer\n");
                sem_wait(&bufferMutex);
                int bpos=buffer->getEnd();
                int ret=buffer->enqueue(cval);
                printf("Monitor thread:writing to buffer at position %d[Current Size=%d]\n",bpos,buffer->getCurrentSize());
            }
            sem_post(&bufferMutex);
            sem_post(&full);
///------------------------------------------------

            usleep(t1);
        }
        return NULL;
    }
    pthread_t mid;
};

class Collector
{
public:
    Collector()
    {
        int ret=pthread_create(&cid, &attr,collect, NULL);
        if(ret!=0)
        {
            printf("collector thread could not be created .. , err =%d\n", ret);
        }
    }
    void endJob()
    {
        pthread_join(cid, NULL);
    }
private:
    static void* collect(void* input)
    {
        while(running)
        {
            if(buffer->getCurrentSize()==0)
            {
                printf(DMSG);
            }
            sem_wait(&full);

            if(sem_trywait(&bufferMutex)==0)
            {
                int bpos=buffer->getStart();
                int ret=buffer->dequeue();
                printf("Collector thread:reading from buffer at position %d[Current Size=%d],value=%d\n",bpos,buffer->getCurrentSize(),ret);
            }
            else
            {
                printf("Collector thread:waiting to read value from buffer\n");
                sem_wait(&bufferMutex);
                int bpos=buffer->getStart();
                int ret=buffer->dequeue();
                printf("Collector thread:reading from buffer at position %d[Current Size=%d],value=%d\n",bpos,buffer->getCurrentSize(),ret);

            }
            sem_post(&bufferMutex);
            sem_post(&empty);
            usleep((rand()%t2)+LEAST_SLEEP);
        }
        return NULL;
    }
    pthread_t cid;
};
///Set Static variables
int MCounter::mccounter=0;
///--------------------------
int main(int argc,char **argv)
{
///user defined variables
    bSize=2;//used to initialize buffer and buffer mutex
    buffer=new RingBuffer(bSize);
    t1=3000000;//2s sleep intervals
    t2=2000000;
    nCounterThreads=4;//4 message counter threads
    running=true;//all threads should start with running state..
///----------------------------

///THREAD ATTRIB INIT
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
///---------------------------------------------------
///Semaphores initialization
    sem_init(&empty, SHARED, bSize);  /* sem empty = buffer size */
    sem_init(&full, SHARED, 0);   /* sem full = 0  */
    sem_init(&bufferMutex, SHARED, 1);   /* buffer CS semaphore*/
    sem_init(&mutex,SHARED,1);

///----------------

///make the threads
    vector<MCounter> mcounterArr;
    for(int i=0; i<nCounterThreads; i++)
    {
        mcounterArr.emplace_back(MCounter());
    }
    Monitor mon;
    Collector col;
///-------------TERMINATE ON USER CLICKING ESC/SPACE-------------------------------

    tcgetattr(0, &old); //get IO Settings to old struct
    neww = old; //make neww struct same as old then modify it
    neww.c_lflag &= ~ICANON; //disable buffered IO
    neww.c_lflag &= ECHO;//Enable Echoing
    tcsetattr(0, TCSANOW, &neww); //apply terminal IO settings
    char in;
    while(in =getchar())
    {
        if((int)in==27||(int)in==32)
        {
            running=false;
            break;
        }
    }
///------------------------------------------------
///JOIN THREADS
    for(int i=0; i<nCounterThreads; i++)
    {
        mcounterArr[i].endJob();
    }
    mon.endJob();
    col.endJob();
///
///DESTROY SEMAPHORES
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&bufferMutex);
    sem_destroy(&full);
///---------------
    return 0;
}
