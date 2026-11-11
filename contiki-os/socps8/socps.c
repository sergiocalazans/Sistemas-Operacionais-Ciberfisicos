#include "contiki.h"
#include <stdio.h>

// comentar o prototipo para mostra o erro
void incrementar();
int escalonarThreadProcesso2();

volatile int i = 0;

PROCESS(socps_process, "Processo 1");
PROCESS(socps_process2, "Processo 2");

AUTOSTART_PROCESSES(&socps_process,&socps_process2);

PROCESS_THREAD(socps_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_SECOND * 2);

  while(true) {

    printf("SOCPS - 1 - i=%d\n",i);
    incrementar();

    if(escalonarThreadProcesso2()){

    	process_poll(&socps_process2);
    }

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
  }

  PROCESS_END();
}

int escalonarThreadProcesso2(){
	
	if(i > 7){
		return 1;
	}
	else
	{
		return 0;
	}
}

void incrementar(){

	i++;
}

PROCESS_THREAD(socps_process2, ev, data)
{

  PROCESS_BEGIN();

  while(true) {
 
    printf("SOCPS - 2 \n");

    //PROCESS_YIELD();
    /*Diferente da funcao PROCESS_YIELD() a funcao PROCESS_EXIT() para o 
     * proceso nao sendo possivel ser habilitada pela funcao process_poll() 
     * no socps_process (processo 1)
    */

    PROCESS_EXIT(); 

  }

  PROCESS_END();
}
