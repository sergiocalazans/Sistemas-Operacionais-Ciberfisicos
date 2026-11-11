#include "contiki.h"
#include <stdio.h>

PROCESS(socps_process, "Processo Hello");

AUTOSTART_PROCESSES(&socps_process);

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();
	
  etimer_set(&timer, CLOCK_SECOND);
  //etimer_set(&timer, CLOCK_SECOND * 10);

  while(true) {

    printf("SOCPS - Hello World!!!\n");
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}
