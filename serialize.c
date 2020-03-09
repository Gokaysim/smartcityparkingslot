#include <stdio.h>
#include "data.h"
#include <stdlib.h>
#include <string.h>
#include "dataAggOptimizer.h"

#define MAX_STRING_LENGTH 1000

int countChars( char* s, char c)
{
    return *s == '\0'
              ? 0
              : countChars( s + 1, c ) + (*s == c);
}
int * parseStrToNodes(char * str,int * count)
{
    if(str == NULL)
    {
        *count = 0;
        return NULL;
    }
    *count = countChars(str,',');

    int * nodeIds = malloc(sizeof(int)*(*count));
    int index = 0;
    char * nodeIdStr= strtok(str,",");
    nodeIds[index] = atoi(nodeIdStr);
    index = index +1;
    while(1)
    {
        nodeIdStr = strtok(NULL,",");
        if(nodeIdStr == NULL)
        {
            break;
        }
        nodeIds[index] = atoi(nodeIdStr);
        index = index +1;
    }
    return nodeIds;
}


char** serialize(int nodeId, struct data_list_struct * data){
    char ** returnString = malloc(sizeof(char*)*2);
    
    returnString[0]=(char *)malloc(sizeof(char *) * MAX_STRING_LENGTH);
    returnString[1]=(char *)malloc(sizeof(char *) * MAX_STRING_LENGTH);
    for(int i= 0;i<MAX_STRING_LENGTH;i++)
    {
        returnString[0][i] = '-';
        returnString[1][i] = '-';
    }
    returnString[0][0]='\0';
    returnString[1][0]='\0';


    char numberStr[10];

    sprintf(numberStr, "%d|0:", nodeId);

    strcat(returnString[0],numberStr);
    strcat(returnString[1],numberStr);

    int dataToLeft = 0,dataToRight = 0;
    struct data_list_struct * iterator = data;
    // for empty
    while(iterator!=NULL)
    {
        //To left
        if(iterator->emptyDataSentDirection == -1|| iterator->emptyDataSentDirection == 0)
        {
            if(iterator->isEmpty)
            {
                dataToLeft = 1;                
                sprintf(numberStr, "%d,", iterator->nodeId);
                strcat(returnString[0],numberStr);
            }
        }

        //To right
        if(iterator->emptyDataSentDirection == 1|| iterator->emptyDataSentDirection == 0)
        {
            if(iterator->isEmpty)
            {
                dataToRight = 1;
                sprintf(numberStr, "%d,", iterator->nodeId);
                strcat(returnString[1],numberStr);
            }
        }
        iterator = iterator->next;
    }
    
    strcat(returnString[0],";1:");
    strcat(returnString[1],";1:");

    iterator = data;    
    while(iterator!=NULL)
    {
        //To left
        if(iterator->emptyDataSentDirection == -1|| iterator->emptyDataSentDirection == 0)
        {
            if(!iterator->isEmpty)
            {
                dataToLeft = 1;
                sprintf(numberStr, "%d,", iterator->nodeId);
                strcat(returnString[0],numberStr);
            }
        }

        //To right
        if(iterator->emptyDataSentDirection == 1|| iterator->emptyDataSentDirection == 0)
        {
            if(!iterator->isEmpty)
            {
                dataToRight = 1;
                sprintf(numberStr, "%d,", iterator->nodeId);
                strcat(returnString[1],numberStr);
            }
        }
        iterator = iterator->next;
    }
    strcat(returnString[0],";");
    strcat(returnString[1],";");

    if(dataToLeft == 0)
    {
        free(returnString[0]);
        returnString[0] = NULL;
    }
    if(dataToRight == 0)
    {
        free(returnString[1]);
        returnString[1] = NULL;
    }
    
    return returnString;
}

struct data_list_struct *  deserialize(int nodeId,char * input){
    
    struct data_list_struct * head = NULL;
    char *nodeIdStr=NULL,*emptynessStr=NULL;
    if(input!= NULL){
        nodeIdStr = strtok(input,"|");
        
        int requestNodeId = atoi(nodeIdStr);
        int nodeDiff = nodeId - requestNodeId;

        emptynessStr = strtok(NULL,"|");

        char * empty = strtok(emptynessStr,";");                
        char * notEmpty = strtok(NULL,";");

        strtok(empty,":");        
        char * emptyIdsStr = strtok(NULL,":");        
        int emptyCount;
        int * emptyNodeIdList= parseStrToNodes(emptyIdsStr,&emptyCount);

        strtok(notEmpty,":");        
        char * notEmptyIdsStr = strtok(NULL,":");        
        int notEmptyCount;
        int * notEmptyNodeIdList= parseStrToNodes(notEmptyIdsStr,&notEmptyCount);

        struct data_list_struct * iterator = NULL;
        for(int i=0;i<emptyCount;i++)
        {
            if(iterator == NULL)
            {
                iterator = (struct data_list_struct *)malloc(sizeof(struct data_list_struct));
                head = iterator;
            }
            else{  
                iterator->next = (struct data_list_struct *)malloc(sizeof(struct data_list_struct));
                iterator = iterator->next;
            }
            iterator->isEmpty = 1;
            iterator->emptyDataSentDirection = nodeDiff;
            iterator->nodeId = emptyNodeIdList[i];
            iterator->next = NULL;
        }        
        addNewIds(emptyNodeIdList,emptyCount,0);
        free(emptyNodeIdList);
        for(int i=0;i<notEmptyCount;i++)
        {
            if(iterator == NULL)
            {
                iterator = (struct data_list_struct *)malloc(sizeof(struct data_list_struct));
                head = iterator;
            }
            else{  
                iterator->next = (struct data_list_struct *)malloc(sizeof(struct data_list_struct));
                iterator = iterator->next;
            }
            iterator->isEmpty = 0;
            iterator->emptyDataSentDirection = nodeDiff;
            iterator->nodeId = notEmptyNodeIdList[i];
            iterator->next = NULL;
        }        
        addNewIds(notEmptyNodeIdList,notEmptyCount,1);
        free(notEmptyNodeIdList);        
    }        

    return head;
}