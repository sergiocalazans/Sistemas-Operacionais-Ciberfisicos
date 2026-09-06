/*
 * TDE 1 - Sistemas Operacionais Ciberfísicos
 *
 * Nome: Sérgio Henrique da Cunha Calazans
 * Curso: Bacharelado em Ciência da Computação (BCC)
 * Turma: 4º U - Noite
 *
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "basic_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições de constantes
#define TAMANHO_PILHA 1000
#define PRIORIDADE_TAREFA 1
#define TEMPO_ESPERA 1000
#define MAX_TEMP 40.0

// Variável global que simula o display
char display[100];

// Mutex responsável por proteger o display
SemaphoreHandle_t mutexDisplay;

// Protótipos 
void vTask1(void* pvParameters);
void vTask2(void* pvParameters);
void vTask3(void* pvParameters);


// TAREFA 1 - Mostra a data atual
void vTask1(void* pvParameters)
{
    // Identificador da tarefa, passado como parâmetro
    int id = *((int*)pvParameters);

    // Variáveis para obter a data atual
    time_t segundos;
    struct tm* datetimeNow;

    for (;;)
    {
        // Tenta obter o mutex do display, aguardando indefinidamente se não estiver disponível
        if (xSemaphoreTake(mutexDisplay, portMAX_DELAY) == pdTRUE)
        {
            // Obtendo o tempo em segundos
            time(&segundos);
            // Converter unidade segundos para tempo local
            datetimeNow = localtime(&segundos);
            // Obtendo o dia
            int dia = datetimeNow->tm_mday;
            // Obtendo o mês
            int mes = datetimeNow->tm_mon + 1; // Adiciona 1, pois os meses começam em 0
            // Obtendo o ano
            int ano = datetimeNow->tm_year + 1900; // Adiciona 1900, pois o ano é contado a partir de 1900

            // Adiciona conteúdo na variável display
            sprintf(display, "Task %d - Data atual: %02d/%02d/%04d\r\n", id, dia, mes, ano);

            // Imprime o conteúdo do display na saída do console
            vPrintString(display);

            // Libera o display
            xSemaphoreGive(mutexDisplay);
        }

        // Aguarda o tempo definido em TEMPO_ESPERA antes de executar novamente
        vTaskDelay(TEMPO_ESPERA / portTICK_PERIOD_MS);
    }
}


// TAREFA 2 - Mostra a hora atual
void vTask2(void* pvParameters)
{
    // Identificador da tarefa, passado como parâmetro
    int id = *((int*)pvParameters);

    // Variáveis para obter a hora atual
    time_t segundos;
    struct tm* datetimeNow;

    for (;;)
    {
        // Tenta obter o mutex do display, aguardando indefinidamente se não estiver disponível
        if (xSemaphoreTake(mutexDisplay, portMAX_DELAY) == pdTRUE)
        {
            // Obtendo o tempo em segundos
            time(&segundos);
            // Converter unidade segundos para tempo local
            datetimeNow = localtime(&segundos);
            // Obtendo a hora
            int hour = datetimeNow->tm_hour;
            // Obtendo os minutos
            int min = datetimeNow->tm_min;
            // Obtendo os segundos
            int sec = datetimeNow->tm_sec;

            // Adiciona conteúdo na variável display
            sprintf(display, "Task %d - Hora atual: %02d:%02d:%02d\r\n", id, hour, min, sec);

            // Imprime o conteúdo do display na saída do console
            vPrintString(display);

            // Libera o display
            xSemaphoreGive(mutexDisplay);
        }

        // Aguarda o tempo definido em TEMPO_ESPERA antes de executar novamente
        vTaskDelay(TEMPO_ESPERA / portTICK_PERIOD_MS);
    }
}


// TAREFA 3 - Cidade e temperatura aleatória
void vTask3(void* pvParameters)
{
    // Identificador da tarefa, passado como parâmetro
    int id = *((int*)pvParameters);

    for (;;)
    {
        // Tenta obter o mutex do display, aguardando indefinidamente se não estiver disponível
        if (xSemaphoreTake(mutexDisplay, portMAX_DELAY) == pdTRUE)
        {
            // Obtendo um número float aleatório, o valor máximo definido em MAX_TEMP
            float temp = ((float)rand() / (float)RAND_MAX) * MAX_TEMP;

            // Adiciona conteúdo na variável display 
            sprintf(display, "Task %d - Curitiba - Temperatura: %.1f C\r\n", id, temp);

            // Imprime o conteúdo do display na saída do console
            vPrintString(display);

            // Libera o display
            xSemaphoreGive(mutexDisplay);
        }

        // Aguarda o tempo definido em TEMPO_ESPERA antes de executar novamente
        vTaskDelay(TEMPO_ESPERA / portTICK_PERIOD_MS);
    }
}


// Função principal
int main_(void) {
    // Identificadores das tarefas
    static int idTask1 = 1;
    static int idTask2 = 2;
    static int idTask3 = 3;

    // Inicializa a geração de números aleatórios
    srand((unsigned int)time(NULL));

    // Criação do mutex
    mutexDisplay = xSemaphoreCreateMutex();

    // Verifica se o mutex foi criado com sucesso
    if (mutexDisplay != NULL)
    {
        // Criação das tarefas

        // Tarefa 1
        xTaskCreate(vTask1, "Task 1", TAMANHO_PILHA, (void*)&idTask1, PRIORIDADE_TAREFA, NULL);

        // Tarefa 2
        xTaskCreate(vTask2, "Task 2", TAMANHO_PILHA, (void*)&idTask2, PRIORIDADE_TAREFA, NULL);

        // Tarefa 3
        xTaskCreate(vTask3, "Task 3", TAMANHO_PILHA, (void*)&idTask3, PRIORIDADE_TAREFA, NULL);

        // Inicia o escalonador
        vTaskStartScheduler();
    }

    for (;;);

    return 0;
}