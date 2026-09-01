/*
 * Atividade I - Sistemas Operacionais Ciberfísicos
 *
 * Nome: Sérgio Henrique da Cunha Calazans
 * Curso: Bacharelado em Ciência da Computação (BCC)
 * Turma: 4º U - Noite
 *
 * Programa de monitoramento de dados vitais utilizando FreeRTOS.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "basic_io.h"
#include <stdlib.h>

 /* Configurações das tarefas */
#define TAMANHO_PILHA      1000
#define PRIORIDADE_TAREFA  1
#define TEMPO_ESPERA       pdMS_TO_TICKS(1000)

/* Handles das tarefas */
xTaskHandle taskHandle1;
xTaskHandle taskHandle2;
xTaskHandle taskHandle3;

/* Protótipos das funções */
double sortearValor(double min, double max);
void vTaskBatimentos(void* pvParameters);
void vTaskTemperatura(void* pvParameters);
void vTaskSaturacao(void* pvParameters);

/*
 * Gera um valor aleatório entre o valor mínimo e máximo informado.
 */
double sortearValor(double min, double max) {

    return min + (double)rand() / RAND_MAX * (max - min);
}

/*
 * Tarefa responsável pelo monitoramento
 * dos batimentos cardíacos do paciente.
 */
void vTaskBatimentos(void* pvParameters) {

    double min = 20.0;
    double max = 140.0;
    double batimentos;

    /* Recebe a mensagem passada como parâmetro */
    char* msgTask = (char*)pvParameters;

    for (;;) {

        /* Gera os batimentos cardíacos aleatoriamente */
        batimentos = sortearValor(min, max);

        /* Exibe o valor no console */
        vPrintStringAndNumber(msgTask, batimentos);

        /* Verifica se os batimentos estao fora da faixa normal */
        if (batimentos < 50.0) {

            vPrintString("\nAlerta: Batimentos abaixo do normal!");

        }
        else if (batimentos > 90.0) {

            vPrintString("\nAlerta: Batimentos acima do normal!");

        }
        else {

            vPrintString("\nBatimentos normais.");
        }

        /* Aguarda um segundo antes da próxima medição */
        vTaskDelay(TEMPO_ESPERA);
    }

    /* Exclusao explícita da tarefa */
    vTaskDelete(NULL);
}

/*
 * Tarefa responsável pelo monitoramento
 * da temperatura corporal do paciente.
 */
void vTaskTemperatura(void* pvParameters) {

    double min = 34.0;
    double max = 41.0;
    double temperatura;

    /* Recebe a mensagem passada como parâmetro */
    char* msgTask = (char*)pvParameters;

    for (;;) {

        /* Gera a temperatura aleatoriamente */
        temperatura = sortearValor(min, max);

        /* Exibe o valor no console */
        vPrintStringAndNumber(msgTask, temperatura);

        /* Verifica a temperatura do paciente */
        if (temperatura < 35.0) {

            vPrintString("\nAlerta: Hipotermia!");

        }
        else if (temperatura > 37.5) {

            vPrintString("\nAlerta: Febre!");

        }
        else {

            vPrintString("\nTemperatura normal.");
        }

        /* Aguarda um segundo antes da próxima medição */
        vTaskDelay(TEMPO_ESPERA);
    }

    /* Exclusao explícita da tarefa */
    vTaskDelete(NULL);
}

/*
 * Tarefa responsável pelo monitoramento
 * da saturação de oxigênio do paciente.
 */
void vTaskSaturacao(void* pvParameters) {

    double min = 80.0;
    double max = 100.0;
    double oxigenio;

    /* Recebe a mensagem passada como parâmetro */
    char* msgTask = (char*)pvParameters;

    for (;;) {

        /* Gera a saturação de oxigênio aleatoriamente */
        oxigenio = sortearValor(min, max);

        /* Exibe o valor no console */
        vPrintStringAndNumber(msgTask, oxigenio);

        /* Verifica se a saturação está abaixo do normal */
        if (oxigenio < 90.0) {

            vPrintString("\nAlerta: Saturacao baixa!");

        }
        else {

            vPrintString("\nSaturacao normal.");
        }

        /* Aguarda um segundo antes da próxima medição */
        vTaskDelay(TEMPO_ESPERA);
    }

    /* Exclusão explícita da tarefa */
    vTaskDelete(NULL);
}

/*
 * Função principal do programa.
 * Cria as três tarefas com a mesma prioridade
 * e inicia o escalonador do FreeRTOS.
 */
int main_(void) {

    /* Cria a tarefa de monitoramento dos batimentos */
    xTaskCreate(
        vTaskBatimentos,
        "Batimentos",
        TAMANHO_PILHA,
        (void*)"\nBatimentos: ",
        PRIORIDADE_TAREFA,
        &taskHandle1
    );

    /* Cria a tarefa de monitoramento da temperatura */
    xTaskCreate(
        vTaskTemperatura,
        "Temperatura",
        TAMANHO_PILHA,
        (void*)"\nTemperatura: ",
        PRIORIDADE_TAREFA,
        &taskHandle2
    );

    /* Cria a tarefa de monitoramento da saturação */
    xTaskCreate(vTaskSaturacao,
        "Saturacao",
        TAMANHO_PILHA,
        (void*)"\nSaturacao: ",
        PRIORIDADE_TAREFA,
        &taskHandle3
    );

    /* Inicia o escalonador do FreeRTOS */
    vTaskStartScheduler();

    return 0;
}
