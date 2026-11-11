#include "contiki.h"
#include <stdio.h>

void incrementar();
volatile int i = 0;
PROCESS(socps_process, "Processo Timer");

AUTOSTART_PROCESSES(&socps_process);

void incrementar(){
  i++;
}

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 3);

  while(true) {
    printf("Processo !!!\n");
    PROCESS_WAIT_EVENT();
    if(etimer_expired(&timer)){
	printf("Tempo expirado - 3 SEGUNDOS!!!\n");
        etimer_restart(&timer);
    }

  }
  PROCESS_END();
}

