#include "contiki.h"
#include <stdio.h>

PROCESS(socps_process, "Processo Hello");
AUTOSTART_PROCESSES(&socps_process);

PROCESS_THREAD(socps_process, ev, data)
{

  PROCESS_BEGIN();

  while(true) {
    printf("SOCPS - Hello World!!!\n");
    
  }

  PROCESS_END();
}
