#include "contiki.h"
#include <stdio.h>

PROCESS(socps_process, "Processo 1");
PROCESS(socps_process2, "Processo 2");
PROCESS(socps_process3, "Processo 3");

AUTOSTART_PROCESSES(&socps_process,&socps_process2,&socps_process3);

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 15);

  while(true) {
    printf("SOCPS - 1\n");

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}

PROCESS_THREAD(socps_process2, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 10);

  while(true) {
    printf("SOCPS - 2\n");

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}

PROCESS_THREAD(socps_process3, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();
  
  etimer_set(&timer, CLOCK_SECOND * 5);

  while(true) {
    printf("SOCPS - 3\n");

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}

