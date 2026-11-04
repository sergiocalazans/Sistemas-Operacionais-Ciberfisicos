#include "contiki.h"
#include <stdio.h>
#include <random.h>

PROCESS(socps_process, "Processo 1");

AUTOSTART_PROCESSES(&socps_process);

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 5);

  int numero = 0;
  int max = 100;
  int min = 50;

  static char msg[50];

  while(true) {

    numero = random_rand() % (max - min) + min;

    sprintf(msg,"Numero Sorteado:  %d\n",numero);
    
    printf("%s",msg);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);

  }
  PROCESS_END();
}

