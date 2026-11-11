#include "contiki.h"
#include <stdio.h>
#include <random.h>

volatile int i = 0;
PROCESS(socps_process, "Processo 1");
PROCESS(display_process, "Processo 2");

AUTOSTART_PROCESSES(&socps_process,&display_process);

void incrementar(){
  i++;
}

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 3);

  static char msg[50]; 

  while(true) {
    
    incrementar();

    printf("Processo 1 - %d\n",i);

    if((i % 5) == 0){

    	sprintf(msg,"Hello World");
	process_post(&display_process,PROCESS_EVENT_MSG,&msg);
    }

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

  }
  PROCESS_END();
}

PROCESS_THREAD(display_process, ev, data)
{

  PROCESS_BEGIN();

  while(true) {
    
    PROCESS_WAIT_EVENT();

    if(PROCESS_EVENT_MSG == ev){
    	printf("Processo 2 - %s\n", (char*)data);
    }

  }

  PROCESS_END();
}
