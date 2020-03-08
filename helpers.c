#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#define BASE_SERVER_EP "coap://[fe80::"

char* intToString(int num, char* str, int base) 
{ 
    int i = 0; 
    int isNegative = 0; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = 1; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative==1) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // // Reverse the string 
    // reverse(str, i); 

    int index = 0;
    int len = strlen(str);

    while ( index < len/2 )
    {
      char temp = str[index];
      str[index] = str[len-1-index];
      str[len-1-index] = temp;

      index = index +1;
    }
  
    return str; 
} 


char * GET_SERVER_EP_FOR_NODE(int nodeId){
  char *buf = malloc(sizeof(char)*5);
  for(int i=0;i<5;i++)
  {
      buf[i]='-';
  }
  intToString(nodeId+512, buf, 16);
  char *val = malloc(sizeof(char) * 50 );
  for(int i=0;i<50;i++)
  {
      val[i]='-';
  }
  val[0] = '\0';

  strcat(val,BASE_SERVER_EP);
  strcat(val,buf);
  intToString(nodeId, buf, 16);
  strcat(val,":");
  strcat(val,buf);
  strcat(val,":");
  strcat(val,buf);
  strcat(val,":");
  strcat(val,buf);
  strcat(val,"]");
  free(buf);

  printf("%s \n",val);
  return val;
}

int getRandomEventGeneratorInverval(){
    return (rand()%(RANDOM_GENERATOR_INTERVAL_MAX-RANDOM_GENERATOR_INTERVAL_MIN))+RANDOM_GENERATOR_INTERVAL_MIN;
}