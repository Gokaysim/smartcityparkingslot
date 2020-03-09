#include "dataAggOptimizer.h"
#include <stdlib.h>
#include "settings.h"
#include <stdio.h>

static struct data_optimizer_node * head=NULL;

static clock_time_t lastDataReceive = 0;
static clock_time_t averagaDataReceiveInterval = 0;
static clock_time_t averagaDataReceiveIntervalDataCount = 0;
static int totalDataReceiveCount = 0;
static int totalReceiveCount = 0;
static float averageDataReceiveCount = 0;

void initOptimizer(){
    clock_init();
}

int getNextNodeId(nodeId)
{
    #ifdef OPTIMIZE
    return nodeId+1;
    #else    
    struct data_optimizer_node * iterator = head;
    int maxNodeId = nodeId +1;
    while(iterator !=NULL)
    {
        if(maxNodeId<iterator->nodeId)
        {
            maxNodeId = iterator->nodeId;
        }
        iterator = iterator->next;        
    }
    return maxNodeId;    
    #endif
}

int getPreviousNodeId(int nodeId)
{
    #ifdef OPTIMIZE
    return nodeId-1;
    #else    
    struct data_optimizer_node * iterator = head;
    int minNodeId = nodeId -1;
    while(iterator !=NULL)
    {
        if(minNodeId < iterator->nodeId)
        {
            minNodeId = iterator->nodeId;
        }
        iterator = iterator->next;        
    }
    return minNodeId;    
    #endif
}

long getScheduleInterval()
{
    struct data_optimizer_node * iterator = head;
    int count = 0;
    while(iterator !=NULL)
    {
        count = count+1;
        iterator = iterator->next;        
    }
    long interval= averagaDataReceiveIntervalDataCount * count/3;

    if(interval<MIN_SCHEDULED_TIME)
    {
        return MIN_SCHEDULED_TIME;
    }
    else if(interval>MAX_SCHEDULED_TIME)
    {
        return MAX_SCHEDULED_TIME;
    }

    return interval;
}

void addNewIds(int * ids,int count){
    
    if(count>0)
    {
        averageDataReceiveCount = ((float)(averageDataReceiveCount *totalReceiveCount +count))/(totalReceiveCount +1);
        
        averagaDataReceiveInterval = (totalReceiveCount * averagaDataReceiveInterval + clock_time() - lastDataReceive)
        /(totalReceiveCount+1);
        
        if ((clock_time() - lastDataReceive)>200)
        {
            totalReceiveCount = totalReceiveCount +1;
        }
        
        averagaDataReceiveIntervalDataCount = (totalDataReceiveCount * averagaDataReceiveIntervalDataCount + clock_time() - lastDataReceive)
        /(totalDataReceiveCount+count);        
        
        totalDataReceiveCount = totalDataReceiveCount + count;    

        lastDataReceive= clock_time();
    }

    printf("averagaDataReceiveInterval: %ld \n",averagaDataReceiveInterval);
    printf("averagaDataReceiveIntervalDataCount: %ld\n",averagaDataReceiveIntervalDataCount);
    printf("totalDataReceiveCount: %d\n",totalDataReceiveCount);
    printf("totalReceiveCount: %d\n",totalReceiveCount);
    printf("averageDataReceiveCount: %.2f\n",averageDataReceiveCount);
    printf("count: %d \n",count);

    for(int i=0;i<count;i++){
        struct data_optimizer_node * iterator = head;
        struct data_optimizer_node * tail = head;
        int alreadyExists = 0;\     
        while(iterator != NULL)
        {            
            if(iterator->nodeId == ids[i]){
                alreadyExists = 1;
                break;
            }
            tail = iterator;
            iterator= iterator->next;
        }
        if(alreadyExists == 0)
        {
            if(tail == NULL)
            {
                tail = (struct data_optimizer_node *)malloc(sizeof(struct data_optimizer_node));
                tail->nodeId = ids[i];
                tail->next = NULL;
            }
            else {
                tail->next = (struct data_optimizer_node *)malloc(sizeof(struct data_optimizer_node));
                tail->next->nodeId = ids[i];
                tail->next->next = NULL;
            }
        }
        
    }
}
