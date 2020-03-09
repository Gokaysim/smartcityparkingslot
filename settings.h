
#include "contiki.h"

#define RANDOM_GENERATOR_INTERVAL_MIN CLOCK_SECOND *1
#define RANDOM_GENERATOR_INTERVAL_MAX CLOCK_SECOND*3

//Purpose of this consts is that When coap cannot find machine to connect it does not continued the process
//To prevent this behaviour below const prevents sending requests to non existing nodes

#define MIN_NODE_ID  1
#define MAX_NODE_ID  5

//If it is defined, it optimizes as line topology
//Otherwise it does not optimizes as line topology. And sends data as star topology
#define OPTIMIZE 


#define MIN_SCHEDULED_TIME 1000
#define MAX_SCHEDULED_TIME 20000


#define EVENT_GENERATION_STOP CLOCK_SECOND * 250
#define PROCESS_STOP CLOCK_SECOND * 300



