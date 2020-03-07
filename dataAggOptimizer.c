#include "dataAggOptimizer.h"
#include <stdlib.h>

struct data_optimizer_node * head=NULL;


void addNewIds(int * ids,int count){
    for(int i=0;i<count;i++){
        struct data_optimizer_node * iterator = head;
        int alreadyExists = 0;
        while(iterator != NULL)
        {            
            if(iterator->nodeId == ids[i]){
                alreadyExists = 1;
                break;
            }
        }
        if(alreadyExists == 0)
        {
            iterator = (struct data_optimizer_node *)malloc(sizeof(struct data_optimizer_node));
            iterator->nodeId = ids[0];
        }
        
    }
}
