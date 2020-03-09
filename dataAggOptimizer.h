struct data_optimizer_node{
    int nodeId;
    struct data_optimizer_node *next;
    //TODO it will be considered
    // int aging;
    
};


void initOptimizer();

void addNewIds(int * ids,int count,int isNewEvent);


long getScheduleInterval();

int getPreviousNodeId(int nodeId);
int getNextNodeId(int nodeId);


