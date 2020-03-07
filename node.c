
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "contiki.h"
#include "contiki-net.h"
#include "coap-engine.h"
#include "coap-blocking-api.h"
#include "sys/node-id.h"
#include <string.h>

/* Log configuration */
#include "log.h"
// #include "test.h"
#include "settings.h"
#include "sys/log.h"
#include "dataAggOptimizer.h"
#include "data.h"
#include "helpers.h"
#include "serialize.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_APP
#define SERVER_EP "coap://[fe80::201:1:1:1]"



static coap_message_t request[1];
static coap_endpoint_t server_ep;
extern coap_resource_t
  res_data;
  static char ** output;
static int requestCount =0;
void client_chunk_handler(coap_message_t *response)
{
  requestCount = requestCount-1;
  if(requestCount == 0)
  {
    free(output[0]);
    free(output[1]);
    free(output);
  }    
}



PROCESS(er_example_server, "Node Server");
AUTOSTART_PROCESSES(&er_example_server);

//Static variables
static struct etimer scheduledTimer;
static struct etimer randomEventGenerator;

//Helper Functions
int getRandomEventGeneratorInverval(){
    return (rand()%(RANDOM_GENERATOR_INTERVAL_MAX-RANDOM_GENERATOR_INTERVAL_MIN))+RANDOM_GENERATOR_INTERVAL_MIN;
}

void sendToOtherNodes(){
  int totalCount = get_left_length_list() + get_right_length_list();  
  struct data_list_struct * data = 
  pop_n_from_list(totalCount);

  output = 
  serialize(node_id,data);  
}
static int isEmpty = 1;
PROCESS_THREAD(er_example_server, ev, data)
{
  
  PROCESS_BEGIN();
  PROCESS_PAUSE();
  /*
   * Bind the resources to their Uri-Path.
   * WARNING: Activating twice only means alternate path, not two instances!
   * All static variables are the same for each URI path.
   */
  coap_activate_resource(&res_data, "data/send");
  srand(time(NULL));

  etimer_set(&scheduledTimer, SCHEDULED_TIMER_INVERVAL);
  etimer_set(&randomEventGenerator,getRandomEventGeneratorInverval());

  // test();
  int continueLoop = 1;
  while(continueLoop) {
    PROCESS_WAIT_EVENT();
    if(etimer_expired(&scheduledTimer)) {      
      sendToOtherNodes();

      if(output[0]!=NULL)
      {
        requestCount+=1;
      }
      if(output[1]!=NULL)
      {
        requestCount+=1;
      }
      //Request send
      if(output[0]!=NULL)
      {
        // printf("left %s\n",output[0]);
        // LOG_SENT(node_id-1,output[0]);
        // char * leftEndPoint = GET_SERVER_EP_FOR_NODE(node_id-1);
        // coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        // coap_set_header_uri_path(request,"/data/send"); 

        // coap_endpoint_parse(leftEndPoint, strlen(leftEndPoint), &server_ep);      
        // coap_set_payload(request, (uint8_t *)output[0], strlen(output[0]));                 
        // COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
      }

      if(output[1]!=NULL)
      {
        // printf("right %s\n",output[1]);
        // LOG_SENT(node_id+1,output[1]);
        // char * rightEndPoint = GET_SERVER_EP_FOR_NODE(node_id+1);
        // coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        // coap_set_header_uri_path(request,"/data/send"); 
        // coap_endpoint_parse(rightEndPoint, strlen(rightEndPoint), &server_ep);                        

        // coap_set_payload(request, (uint8_t *)output[1], strlen(output[1]));
        // COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
      }
      etimer_set(&scheduledTimer, SCHEDULED_TIMER_INVERVAL);     
    }
    else if(etimer_expired(&randomEventGenerator)) {
      if(isEmpty == 0 )
      {
        isEmpty = 1;
      }
      else{
        isEmpty = 0;
      }
      add_to_top_of_list(node_id,isEmpty,0);
      sendToOtherNodes();

      if(output[0]!=NULL)
      {
        requestCount+=1;
      }
      if(output[1]!=NULL)
      {
        requestCount+=1;
      }
      //Request send
      if(output[0]!=NULL)
      {
        printf("left %s\n",output[0]);
        LOG_SENT(node_id-1,output[0]);
        char * leftEndPoint = GET_SERVER_EP_FOR_NODE(node_id-1);
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 

        coap_endpoint_parse(leftEndPoint, strlen(leftEndPoint), &server_ep);      
        coap_set_payload(request, (uint8_t *)output[0], strlen(output[0]));                 
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
      }

      if(output[1]!=NULL)
      {
        printf("right %s\n",output[1]);
        LOG_SENT(node_id+1,output[1]);
        char * rightEndPoint = GET_SERVER_EP_FOR_NODE(node_id+1);
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 
        coap_endpoint_parse(rightEndPoint, strlen(rightEndPoint), &server_ep);                        

        coap_set_payload(request, (uint8_t *)output[1], strlen(output[1]));
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
      }
      etimer_set(&randomEventGenerator,getRandomEventGeneratorInverval());
    }   
  }  
  PROCESS_END();
}

