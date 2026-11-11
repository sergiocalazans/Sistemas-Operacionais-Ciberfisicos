#include "contiki.h"
#include <stdio.h>

void incrementar();
volatile int i = 0;
static struct ctimer timer;

PROCESS(socps_process, "Processo Timer");
PROCESS(socps_process2, "Processo Timer");

AUTOSTART_PROCESSES(&socps_process,&socps_process2);

void incrementar(){
  i++;
}

void ctimer_callback(void *ptr){

  ctimer_reset(&timer);
  printf("CHAMADA DE CALLBACK - CTIMER\n");

}



PROCESS_THREAD(socps_process, ev, data)
{

  PROCESS_BEGIN();

  ctimer_set(&timer, CLOCK_SECOND * 3, ctimer_callback, NULL);
  
  while(true) {
    printf("SOCPS - 1 \n");
    PROCESS_WAIT_EVENT();
    
    printf("### SOCPS 1 - OCORREU UM EVENTO ###\n");

  }
  PROCESS_END();
}

PROCESS_THREAD(socps_process2, ev, data)
{

  static struct etimer timer2;

  PROCESS_BEGIN();

  etimer_set(&timer2, CLOCK_SECOND * 3);

  while(true) {
    printf("SOCPS - 2 - %d \n",i);
    incrementar();

    if(i == 5){
	printf("SOCPS 2 - ENVIANDO EVENTO\n");
	process_post(&socps_process,PROCESS_EVENT_MSG,NULL);

    }
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer2));
    etimer_reset(&timer2);

  }
  PROCESS_END();
}

