
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
void client_chunk_handler(coap_message_t *response)
{  
}


PROCESS(er_example_server, "Node Server");
AUTOSTART_PROCESSES(&er_example_server);

//Static variables
static struct etimer scheduledTimer;
static struct etimer randomEventGenerator;
static char* sendToIpv6 = NULL;

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
  // coap_init_engine();
  initOptimizer();
  coap_activate_resource(&res_data, "data/send");
  srand(time(NULL));

  etimer_set(&scheduledTimer, SCHEDULED_TIMER_INVERVAL);
  etimer_set(&randomEventGenerator,getRandomEventGeneratorInverval());

  while(1) {
    PROCESS_WAIT_EVENT();
    if(etimer_expired(&scheduledTimer)&&false) { 
      printf("scheduled\n");
      sendToOtherNodes();

      // Request send
      if(output[0]!=NULL && node_id != MIN_NODE_ID)
      {        
        printf("left %s\n",output[0]);
        int sendNodeId = node_id-1;
        LOG_SENT(sendNodeId,output[0]);      
        sendToIpv6 = GET_SERVER_EP_FOR_NODE(sendNodeId);
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 

        coap_endpoint_parse(sendToIpv6, strlen(sendToIpv6), &server_ep);      
        coap_set_payload(request, (uint8_t *)output[0], strlen(output[0]));                 
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
        free(sendToIpv6);
      }

      if(output[1]!=NULL && node_id != MAX_NODE_ID)
      {
      
        printf("right %s\n",output[1]);
        int sendNodeId = node_id+1;
        LOG_SENT(sendNodeId,output[1]);
        sendToIpv6 = GET_SERVER_EP_FOR_NODE(sendNodeId);        
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 
        coap_endpoint_parse(sendToIpv6, strlen(sendToIpv6), &server_ep);                        

        coap_set_payload(request, (uint8_t *)output[1], strlen(output[1]));
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
        free(sendToIpv6);
      }
      etimer_set(&scheduledTimer, SCHEDULED_TIMER_INVERVAL);
    }
    if(etimer_expired(&randomEventGenerator)) {
      printf("event\n");
      if(isEmpty == 0 )
      {
        isEmpty = 1;
      }
      else{
        isEmpty = 0;
      }
      add_to_top_of_list(node_id,isEmpty,0);
      sendToOtherNodes();

      // Request send
      if(output[0]!=NULL && node_id != MIN_NODE_ID )
      {
        int sendNodeId = node_id-1;
        LOG_SENT(sendNodeId,output[0]);
        printf("left %s\n",output[0]);
        sendToIpv6 = GET_SERVER_EP_FOR_NODE(sendNodeId);
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 

        coap_endpoint_parse(sendToIpv6, strlen(sendToIpv6), &server_ep);      
        coap_set_payload(request, (uint8_t *)output[0], strlen(output[0]));                 
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);        
        free(sendToIpv6);
      }

      if(output[1]!=NULL && node_id != MAX_NODE_ID)
      {
        int sendNodeId = node_id+1;
        printf("right %s\n",output[1]);
        LOG_SENT(sendNodeId,output[1]);
        sendToIpv6 = GET_SERVER_EP_FOR_NODE(sendNodeId);
        coap_init_message(request, COAP_TYPE_CON, COAP_POST, 0);
        coap_set_header_uri_path(request,"/data/send"); 
        coap_endpoint_parse(sendToIpv6, strlen(sendToIpv6), &server_ep);                        

        coap_set_payload(request, (uint8_t *)output[1], strlen(output[1]));
        COAP_BLOCKING_REQUEST(&server_ep, request, client_chunk_handler);
        free(sendToIpv6);
      }
      etimer_set(&randomEventGenerator,getRandomEventGeneratorInverval());
    }   
  }
  PROCESS_END();
}

