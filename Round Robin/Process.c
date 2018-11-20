#include "Process.h"

int readInputs(const char* path,Process* PArr,int* s)
{
    FILE* f=NULL;
    char Buffer[64];
    f=fopen(path,"r");
    if(f==NULL)
    {
        return -1;
    }
    int timeSlots;
    fgets(Buffer,64,f);
//sscanf(Buffer,"%d",&timeSlots);//UNCOMMENT IF NO STRING ON FIRST LINE
    sscanf(Buffer,"%*[^=]%*c %d",&timeSlots);//IGNORE FIRST LINE TILL THE NUMBER
    int i=0;
    while(!feof(f))
    {
        fgets(Buffer,64,f);
        sscanf(Buffer,"%s %d %d",&PArr[i].name,&PArr[i].sT,&PArr[i].eT);
        (*s)++;
        i++;
    }
    fclose(f);
    return timeSlots;
}


//PSEUDO CODE IN REPORT
void roundRobinAlgorithm(Process* PArr,int s,int watchTime)
{
    Queue* pQ=init();
    int i,k;
    for(k=0; k<s; k++)
    {
        if(PArr[k].sT==0)
        {
            Enqueue(pQ,PArr[k]);
        }
    }
    for(i=0; i<watchTime; i++)
    {
        if(isEmpty(pQ))
        {
            printf("idle (%d --> %d)\n",i,i+1);
            for(k=0; k<s; k++)
            {
                if(PArr[k].sT==i+1)
                {
                    Enqueue(pQ,PArr[k]);
                }
            }
        }
        else
        {
            Process p=Dequeue(pQ);
            printf("%s (%d --> %d)",p.name,i,i+1);
            p.eT--;
            for(k=0; k<s; k++)
            {
                if(PArr[k].sT==i+1)
                {
                    Enqueue(pQ,PArr[k]);
                }
            }
            if(p.eT==0)
            {
                printf(" %s Aborts\n",p.name);
            }
            else
            {
                Enqueue(pQ,p);
                printf("\n");
            }
        }
    }
    printf("stop\n");


}
