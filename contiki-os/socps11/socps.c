#include "contiki.h"
#include <stdio.h>

void incrementar();
volatile int i = 0;
PROCESS(socps_process, "Processo 1");
PROCESS(socps_process2, "Processo 2");

AUTOSTART_PROCESSES(&socps_process,&socps_process2);

void incrementar(){
  i++;
}

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 2);

  while(true) {

    incrementar();
    printf("SOCPS - 1 - %d\n",i);

    if((i % 3) == 0){
    
	    process_post(&socps_process2,PROCESS_EVENT_MSG,NULL);
    }

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

  }
  PROCESS_END();
}

PROCESS_THREAD(socps_process2, ev, data)
{

  PROCESS_BEGIN();

  while(true) {
 
    printf("SOCPS - 2\n");
    
    PROCESS_WAIT_EVENT();

    if(PROCESS_EVENT_MSG == ev){
    	printf("### OCORREU UM EVENTO ###\n");
    }

  }

  PROCESS_END();
}
