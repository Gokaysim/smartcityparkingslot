#include <stdio.h>
#include <string.h>
#include "coap-engine.h"
#include "coap.h"
#include "sys/node-id.h"
#include "log.h"
#include "serialize.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_APP



static void res_any_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);

/* This resource mirrors the incoming request. It shows how to access the options and how to set them for the response. */
RESOURCE(res_data,
         "title=\"Returns your decoded message\";rt=\"Debug\"",
         res_any_handler,
         res_any_handler,
         res_any_handler,
         res_any_handler);

static void
res_any_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const uint8_t *chunk;
  coap_get_payload(request, &chunk);
  LOG_RECEIVED((char *)chunk);
  struct data_list_struct * data= deserialize(node_id,(char *)chunk);

  struct data_list_struct *  iterator = data;
  while(iterator!=NULL)
  {
    add_to_list(iterator->nodeId,iterator->isEmpty,iterator->emptyDataSentDirection);
    iterator = iterator->next;
  }
  destroy_list(data);

  // print_all_head();
}