#include "contiki.h"
#include <stdio.h>

PROCESS(hello_world_process, "Hello World Process");
AUTOSTART_PROCESSES(&hello_world_process);

PROCESS_THREAD(hello_world_process, ev, data)
{
  PROCESS_BEGIN();

  printf("Hello, World! Contiki-NG rodando com sucesso!\n");

  PROCESS_END();
}
