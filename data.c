#include <stdio.h>
#include "data.h"
#include <stdlib.h>

#include "contiki.h"
#include "sys/node-id.h"

struct data_list_struct * head;


void init_list(){
}


void add_to_list(int nodeId,int isEmpty,int emptyDataSentDirection)
{
    if(head == NULL){
        head = (struct data_list_struct *)malloc(sizeof(struct data_list_struct));
        head->isEmpty = isEmpty;
        head->emptyDataSentDirection = emptyDataSentDirection;
        head->nodeId = nodeId;
        head->next = NULL;
        return;
    }

    struct data_list_struct * iterator = head;
    struct data_list_struct * last = NULL;
    while(iterator != NULL)
    {
        if(iterator->nodeId == nodeId){
            iterator->isEmpty = isEmpty;
            iterator->emptyDataSentDirection = emptyDataSentDirection;
            return;
        }
        last = iterator;
        iterator = iterator->next; 
    }
    last->next = (struct data_list_struct *) malloc(sizeof(struct data_list_struct));

    last->next->isEmpty = isEmpty;
    last->next->emptyDataSentDirection = emptyDataSentDirection;
    last->next->nodeId = nodeId;
    last->next->next = NULL;
}

struct data_list_struct * pop_n_from_list(int n){

   
    if(head == NULL)
    {
        return NULL;
    }
    struct data_list_struct * oldHead = head;
    struct data_list_struct * iterator = head;
        
    while(1)
    {        
        n= n-1;
        if(n==0 || iterator->next == NULL)
        {
            head = iterator->next;
            iterator->next= NULL;            
            break;
        }        
        iterator = iterator->next;
    }

    return oldHead;
}

int get_left_length_list(){
    int count = 0;
    struct data_list_struct * iterator = head;
    while(iterator!=NULL)
    {
        if(iterator->emptyDataSentDirection == -1 || iterator->emptyDataSentDirection == 0)
        {
            count=count+1;
        }
        iterator = iterator->next;
    }
    return count;
}

int get_right_length_list(){
    int count = 0;
    struct data_list_struct * iterator = head;
    while(iterator!=NULL)
    {
        if(iterator->emptyDataSentDirection == 1 || iterator->emptyDataSentDirection == 0)
        {
            count=count+1;
        }
        iterator = iterator->next;
    }
    return count;
}

void print_all(struct data_list_struct * listOfHeader){
    struct data_list_struct * iterator = listOfHeader;
    printf("Node Id\t isEmpty\t emptyDataSentDirection\n");
    while(iterator!=NULL)
    {
        printf("%d\t %d\t %d \n",iterator->nodeId,iterator->isEmpty, iterator->emptyDataSentDirection);
        iterator = iterator->next;
    }
}

void print_all_head(){
    print_all(head);
}

void destroy_list(struct data_list_struct * listOfHeader){
    if(listOfHeader == NULL)
    {
        return;
    }
    while (1)
    {     
        struct data_list_struct * next = listOfHeader->next;
        free(listOfHeader);
        listOfHeader = next;
        if(listOfHeader == NULL)
        {
            break;
        }
    }
}

void add_to_top_of_list(int nodeId,int isEmpty,int emptyDataSentDirection){
    struct data_list_struct *temp = (struct data_list_struct *) malloc(sizeof(struct data_list_struct));
    temp->next =NULL;
    temp->isEmpty = isEmpty;
    temp->emptyDataSentDirection = emptyDataSentDirection;
    temp->nodeId = nodeId;
    if(head == NULL)
    {
        head = temp;
        return;
    }
    temp->next = head;
    head = temp;

}