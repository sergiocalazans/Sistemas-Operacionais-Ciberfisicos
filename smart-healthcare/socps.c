/**
 * Pontifícia Universidade Católica do Paraná (PUCPR)
 * Curso: Bacharelado em Ciência da Computação
 * Estudante: Sérgio Henrique da Cunha Calazans
 * Disciplina: Sistemas Operacionais Ciberfísicos
 * TDE II - Smart Healthcare
 *
 * Simulação de um smartwatch para monitoramento de sinais vitais.
 * Cada medição ocorre a cada três segundos, utilizando processos
 * e eventos do Contiki-NG.
 */

#include "contiki.h"
#include "sys/etimer.h"
#include "lib/random.h"
#include <stdio.h>

// Declaração dos três processos de monitoramento e do processo de alertas.
PROCESS(batimentos_process, "Monitor de batimentos cardíacos");
PROCESS(oxigenio_process, "Monitor de saturação de oxigênio");
PROCESS(temperatura_process, "Monitor de temperatura corporal");
PROCESS(alertas_process, "Alertas de sinais vitais");

// Inicializa automaticamente os quatro processos.
AUTOSTART_PROCESSES(&alertas_process, &batimentos_process, &oxigenio_process, &temperatura_process);

// Processo responsável por receber os eventos e informar os alertas.
PROCESS_THREAD(alertas_process, ev, data)
{
  PROCESS_BEGIN();

  printf("[SISTEMA] Monitor Smart Healthcare iniciado.\n");

  while(1) {
    // Aguarda uma mensagem enviada por um dos processos de monitoramento.
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_MSG);

    // O conteúdo da mensagem é um texto fixo enviado pelo processo de origem.
    if(data != NULL) {
      printf("[ALERTA] %s\n", (const char *)data);
    }
  }

  PROCESS_END();
}

// Processo de monitoramento dos batimentos cardíacos.
PROCESS_THREAD(batimentos_process, ev, data)
{
  // Variáveis estáticas preservam seus valores quando o processo aguarda eventos.
  static struct etimer temporizador;
  static int batimentos;

  PROCESS_BEGIN();

  // Configura o intervalo de três segundos entre medições.
  etimer_set(&temporizador, 3 * CLOCK_SECOND);

  while(1) {
    // Aguarda o término do temporizador deste processo.
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER && data == &temporizador);

    // Simula uma medição aleatória entre 20 e 140 BPM.
    batimentos = 20 + (random_rand() % 121);
    printf("[BATIMENTOS] %d BPM\n", batimentos);

    // Valores abaixo de 50 BPM ou acima de 90 BPM geram alertas.
    if(batimentos < 50) {
      process_post(&alertas_process, PROCESS_EVENT_MSG, (void *)"Batimento cardíaco baixo (abaixo de 50 BPM).");
    } else if(batimentos > 90) {
      process_post(&alertas_process, PROCESS_EVENT_MSG, (void *)"Batimento cardíaco alto (acima de 90 BPM).");
    }

    // Reinicia a contagem para a próxima medição.
    etimer_reset(&temporizador);
  }

  PROCESS_END();
}

// Processo de monitoramento da saturação de oxigênio no sangue.
PROCESS_THREAD(oxigenio_process, ev, data)
{
  static struct etimer temporizador;
  static int saturacao;

  PROCESS_BEGIN();

  // Configura o intervalo de três segundos entre medições.
  etimer_set(&temporizador, 3 * CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER && data == &temporizador);

    // Simula uma saturação aleatória entre 80% e 100%.
    saturacao = 80 + (random_rand() % 21);
    printf("[OXIGÊNIO] Saturação: %d%%\n", saturacao);

    // Saturação abaixo de 90% gera um evento de alerta.
    if(saturacao < 90) {
      process_post(&alertas_process, PROCESS_EVENT_MSG, (void *)"Saturação de oxigênio baixa (abaixo de 90%).");
    }

    // Reinicia a contagem para a próxima medição.
    etimer_reset(&temporizador);
  }

  PROCESS_END();
}

// Processo de monitoramento da temperatura corporal.
PROCESS_THREAD(temperatura_process, ev, data)
{
  static struct etimer temporizador;
  static int temperatura;

  PROCESS_BEGIN();

  // Configura o intervalo de três segundos entre medições.
  etimer_set(&temporizador, 3 * CLOCK_SECOND);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER && data == &temporizador);

    // Simula uma temperatura aleatória inteira entre 34 °C e 41 °C.
    temperatura = 34 + (random_rand() % 8);
    printf("[TEMPERATURA] %d °C\n", temperatura);

    // Identifica hipotermia abaixo de 35 °C e febre acima de 37 °C.
    if(temperatura < 35) {
      process_post(&alertas_process, PROCESS_EVENT_MSG, (void *)"Hipotermia: temperatura abaixo de 35 °C.");
    } else if(temperatura > 37) {
      process_post(&alertas_process, PROCESS_EVENT_MSG, (void *)"Febre: temperatura acima de 37 °C.");
    }

    // Reinicia a contagem para a próxima medição.
    etimer_reset(&temporizador);
  }

  PROCESS_END();
}
