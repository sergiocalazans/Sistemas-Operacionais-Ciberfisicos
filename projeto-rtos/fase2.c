/* 
 * Projeto RTOS II - SOCPS
 *
 * Curso: Bacharelado em Ciência da Computação (BCC)
 * Turma: 4º U - Noite
 * 
 * Estudante: Sérgio Henrique da Cunha Calazans
 *
 * Programa no FreeRTOS destinado a controlar um software de quadricoptero
*/


#include "FreeRTOS.h"                                      // Inclui as definições principais do FreeRTOS.
#include "task.h"                                          // Inclui as funções para criação e gerenciamento de tarefas.
#include "semphr.h"                                        // Inclui as funções para utilização de semáforos.
#include "basic_io.h"                                      // Inclui a função vPrintString() utilizada nas aulas.
#include <stdio.h>                                         // Inclui printf() e sprintf().
#include <stdlib.h>                                        // Inclui a função rand().
#include <string.h>                                        // Inclui funções para manipulação de strings.

#define TAMANHO_PILHA 1000                                 // Define o tamanho da pilha das tarefas.
#define PRIORIDADE_MANOBRA 2                               // Define a mesma prioridade para as três tarefas de manobra.
#define PRIORIDADE_RADIO 1                                 // Define prioridade inferior para a tarefa de rádio frequência.

volatile long velocidadeMotor0 = 0;                        // Armazena a velocidade simulada do motor 0.
volatile long velocidadeMotor1 = 0;                        // Armazena a velocidade simulada do motor 1.
volatile long velocidadeMotor2 = 0;                        // Armazena a velocidade simulada do motor 2.
volatile long velocidadeMotor3 = 0;                        // Armazena a velocidade simulada do motor 3.

volatile char sentido[15];                                 // Armazena "horario" ou "antihorario" para a guinada.
volatile char direcao[15];                                 // Armazena "frente" ou "tras" para a arfagem.
volatile char orientacao[15];                              // Armazena "direita" ou "esquerda" para a rolagem.

xSemaphoreHandle semaforo;                                 // Declara o semáforo binário utilizado para exclusão mútua.

void guinada(void* pvParameters);                          // Declara a função da tarefa de guinada.
void arfagem(void* pvParameters);                          // Declara a função da tarefa de arfagem.
void rolagem(void* pvParameters);                          // Declara a função da tarefa de rolagem.
void radioFrequencia(void* pvParameters);                  // Declara a função da tarefa de rádio frequência.

void guinada(void* pvParameters)                           // Define a tarefa responsável pela guinada.
{                                                          // Inicia a função guinada.
    char* sentidoInicial = (char*)pvParameters;            // Recupera o sentido inicial recebido pelo xTaskCreate().

    xSemaphoreTake(semaforo, portMAX_DELAY);               // Solicita acesso exclusivo as variáveis globais.
    sprintf((char*)sentido, "%s", sentidoInicial);       // Copia o parâmetro inicial para a variável global sentido.
    xSemaphoreGive(semaforo);                              // Libera o semáforo para as demais tarefas.

    for (;;)                                               // Mantém a tarefa sendo executada continuamente.
    {                                                      // Inicia o laço da tarefa.
        if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) // Aguarda até conseguir acesso exclusivo aos dados.
        {                                                  // Inicia a região crítica.
            vPrintString("\n--- GUINADA ---\n");           // Exibe o nome da manobra atual.

            if (strcmp((char*)sentido, "horario") == 0)   // Verifica se o quadricoptero deve girar no sentido horário.
            {                                              // Inicia o tratamento do sentido horário.
                velocidadeMotor0++;                        // Aumenta a velocidade do motor 0.
                velocidadeMotor2++;                        // Aumenta a velocidade do motor 2.
                velocidadeMotor1--;                        // Diminui a velocidade do motor 1.
                velocidadeMotor3--;                        // Diminui a velocidade do motor 3.
            }                                              // Finaliza o tratamento do sentido horário.
            else                                           // Executa quando o sentido for anti-horário.
            {                                              // Inicia o tratamento do sentido anti-horário.
                velocidadeMotor0--;                        // Diminui a velocidade do motor 0.
                velocidadeMotor2--;                        // Diminui a velocidade do motor 2.
                velocidadeMotor1++;                        // Aumenta a velocidade do motor 1.
                velocidadeMotor3++;                        // Aumenta a velocidade do motor 3.
            }                                              // Finaliza o tratamento do sentido anti-horário.

            printf("Sentido: %s\n", (char*)sentido);      // Exibe o sentido atual da guinada.
            printf("Motor 0: %ld\n", velocidadeMotor0);    // Exibe a velocidade atual do motor 0.
            printf("Motor 1: %ld\n", velocidadeMotor1);    // Exibe a velocidade atual do motor 1.
            printf("Motor 2: %ld\n", velocidadeMotor2);    // Exibe a velocidade atual do motor 2.
            printf("Motor 3: %ld\n", velocidadeMotor3);    // Exibe a velocidade atual do motor 3.

            xSemaphoreGive(semaforo);                      // Libera o acesso a região crítica.
        }                                                  // Finaliza a região crítica.

        vTaskDelay(portTICK_RATE_MS * 10);                 // Atrasa a guinada em 10 ms.
    }                                                      // Finaliza o laço infinito.

    vTaskDelete(NULL);                                     // Exclui explicitamente a própria tarefa caso o laço termine.
}                                                          // Finaliza a tarefa guinada.

void arfagem(void* pvParameters)                           // Define a tarefa responsável pela arfagem.
{                                                          // Inicia a função arfagem.
    char* direcaoInicial = (char*)pvParameters;            // Recupera a direção inicial recebida como parâmetro.

    xSemaphoreTake(semaforo, portMAX_DELAY);               // Solicita acesso exclusivo às variáveis globais.
    sprintf((char*)direcao, "%s", direcaoInicial);        // Define inicialmente a direção global.
    xSemaphoreGive(semaforo);                              // Libera o acesso às variáveis globais.

    for (;;)                                               // Mantém a tarefa sendo executada continuamente.
    {                                                      // Inicia o laço da tarefa.
        if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) // Tenta obter o semáforo antes de acessar os motores.
        {                                                  // Inicia a região crítica.
            vPrintString("\n--- ARFAGEM ---\n");           // Exibe a manobra que esta sendo executada.

            if (strcmp((char*)direcao, "frente") == 0)    // Verifica se o movimento deve ocorrer para frente.
            {                                              // Inicia o movimento para frente.
                velocidadeMotor2++;                        // Aumenta a velocidade do motor 2.
                velocidadeMotor3++;                        // Aumenta a velocidade do motor 3.
                velocidadeMotor0--;                        // Diminui a velocidade do motor 0.
                velocidadeMotor1--;                        // Diminui a velocidade do motor 1.
            }                                              // Finaliza o movimento para frente.
            else                                           // Executa quando a direção for para trás.
            {                                              // Inicia o movimento para trás.
                velocidadeMotor2--;                        // Diminui a velocidade do motor 2.
                velocidadeMotor3--;                        // Diminui a velocidade do motor 3.
                velocidadeMotor0++;                        // Aumenta a velocidade do motor 0.
                velocidadeMotor1++;                        // Aumenta a velocidade do motor 1.
            }                                              // Finaliza o movimento para trás.

            printf("Direcao: %s\n", (char*)direcao);      // Exibe a direção atual da arfagem.
            printf("Motor 0: %ld\n", velocidadeMotor0);    // Exibe a velocidade atual do motor 0.
            printf("Motor 1: %ld\n", velocidadeMotor1);    // Exibe a velocidade atual do motor 1.
            printf("Motor 2: %ld\n", velocidadeMotor2);    // Exibe a velocidade atual do motor 2.
            printf("Motor 3: %ld\n", velocidadeMotor3);    // Exibe a velocidade atual do motor 3.

            xSemaphoreGive(semaforo);                      // Libera o semáforo ao terminar a região critica.
        }                                                  // Finaliza a região crítica.

        vTaskDelay(portTICK_RATE_MS * 40);                 // Atrasa a tarefa por 40 ms.
    }                                                      // Finaliza o laço infinito.

    vTaskDelete(NULL);                                     // Exclui explícitamente a própria tarefa se o laço terminar.
}                                                          // Finaliza a tarefa arfagem.

void rolagem(void* pvParameters)                           // Define a tarefa responsável pela rolagem.
{                                                          // Inicia a função rolagem.
    char* orientacaoInicial = (char*)pvParameters;         // Recupera a orientação inicial recebida como parâmetro.

    xSemaphoreTake(semaforo, portMAX_DELAY);               // Obtém acesso exclusivo para inicializar a variável global.
    sprintf((char*)orientacao, "%s", orientacaoInicial);  // Define a orientação inicial.
    xSemaphoreGive(semaforo);                              // Libera o semáforo.

    for (;;)                                               // Mantém a tarefa executando continuamente.
    {                                                      // Inicia o laço da tarefa.
        if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) // Solicita acesso exclusivo aos motores.
        {                                                  // Inicia a região crítica.
            vPrintString("\n--- ROLAGEM ---\n");           // Exibe o nome da manobra.

            if (strcmp((char*)orientacao, "direita") == 0) // Verifica se a rolagem deve ocorrer para direita.
            {                                              // Inicia a rolagem para direita.
                velocidadeMotor0++;                        // Aumenta a velocidade do motor 0.
                velocidadeMotor3++;                        // Aumenta a velocidade do motor 3.
                velocidadeMotor1--;                        // Diminui a velocidade do motor 1.
                velocidadeMotor2--;                        // Diminui a velocidade do motor 2.
            }                                              // Finaliza a rolagem para direita.
            else                                           // Executa quando a orientação for esquerda.
            {                                              // Inicia a rolagem para esquerda.
                velocidadeMotor0--;                        // Diminui a velocidade do motor 0.
                velocidadeMotor3--;                        // Diminui a velocidade do motor 3.
                velocidadeMotor1++;                        // Aumenta a velocidade do motor 1.
                velocidadeMotor2++;                        // Aumenta a velocidade do motor 2.
            }                                              // Finaliza a rolagem para esquerda.

            printf("Orientacao: %s\n", (char*)orientacao);// Exibe a orientação atual.
            printf("Motor 0: %ld\n", velocidadeMotor0);    // Exibe a velocidade atual do motor 0.
            printf("Motor 1: %ld\n", velocidadeMotor1);    // Exibe a velocidade atual do motor 1.
            printf("Motor 2: %ld\n", velocidadeMotor2);    // Exibe a velocidade atual do motor 2.
            printf("Motor 3: %ld\n", velocidadeMotor3);    // Exibe a velocidade atual do motor 3.

            xSemaphoreGive(semaforo);                      // Libera o semáforo depois da alteração dos motores.
        }                                                  // Finaliza a região crítica.

        vTaskDelay(portTICK_RATE_MS * 20);                 // Atrasa a tarefa de rolagem por 20 ms.
    }                                                      // Finaliza o laço infinito.

    vTaskDelete(NULL);                                     // Exclui explícitamente a tarefa caso o laço termine.
}                                                          // Finaliza a tarefa rolagem.

void radioFrequencia(void* pvParameters)                   // Define a quarta tarefa responsável pela rádio frequencia.
{                                                          
    int x;                                                 // Armazena o número aleatório relacionado ao sentido.
    int y;                                                 // Armazena o número aleatório relacionado à direção.
    int z;                                                 // Armazena o número aleatório relacionado à orientação.

    for (;;)                                               // Mantém à recepção simulada de comandos continuamente.
    {                                                      // Inicia o laço da tarefa.
        x = rand() % 100;                                  // Sorteia um número entre 0 e 99 para a guinada.
        y = rand() % 100;                                  // Sorteia um número entre 0 e 99 para a arfagem.
        z = rand() % 100;                                  // Sorteia um número entre 0 e 99 para a rolagem.

        if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) // Obtém acesso exclusivo às variáveis globais.
        {                                                  // Inicia a região crítica do rádio.
            if (x % 2 == 0)                                // Verifica se o primeiro número sorteado e par.
            {                                              // Inicia o caso par para guinada.
                sprintf((char*)sentido, "horario");       // Define o sentido da guinada como horário.
            }                                              // Finaliza o caso par.
            else                                           // Executa se o número sorteado for ímpar.
            {                                              // Inicia o caso ímpar.
                sprintf((char*)sentido, "antihorario");   // Define o sentido da guinada como anti-horário.
            }                                              // Finaliza o caso ímpar.

            if (y % 2 == 0)                                // Verifica se o segundo número sorteado e par.
            {                                              // Inicia o caso par para arfagem.
                sprintf((char*)direcao, "frente");        // Define a direção como frente.
            }                                              // Finaliza o caso par.
            else                                           // Executa se o número sorteado for ímpar.
            {                                              // Inicia o caso ímpar.
                sprintf((char*)direcao, "tras");          // Define a direção como trás.
            }                                              // Finaliza o caso ímpar.

            if (z % 2 == 0)                                // Verifica se o terceiro numero sorteado e par.
            {                                              // Inicia o caso par para rolagem.
                sprintf((char*)orientacao, "direita");    // Define a orientação como direita.
            }                                              // Finaliza o caso par.
            else                                           // Executa se o número sorteado for ímpar.
            {                                              // Inicia o caso ímpar.
                sprintf((char*)orientacao, "esquerda");   // Define a orientação como esquerda.
            }                                              // Finaliza o caso ímpar.

            vPrintString("\n=== RADIO FREQUENCIA ===\n");  // Informa que novos comandos foram recebidos.
            printf("Numeros sorteados: %d %d %d\n", x, y, z); // Exibe os três números aleatórios.
            printf("Sentido: %s\n", (char*)sentido);      // Exibe o novo sentido da guinada.
            printf("Direcao: %s\n", (char*)direcao);      // Exibe a nova direção da arfagem.
            printf("Orientacao: %s\n", (char*)orientacao);// Exibe a nova orientação da rolagem.

            xSemaphoreGive(semaforo);                      // Libera o semáforo para as tarefas de manobra.
        }                                                  // Finaliza a região crítica.

        vTaskDelay(portTICK_RATE_MS * 100);                // Atrasa a tarefa por 100 ms.
    }                                                      // Finaliza o laço infinito.

    vTaskDelete(NULL);                                     // Exclui explícitamente a tarefa caso o laço termine.
}                                                          // Finaliza a tarefa de rádio frequência.

int main_(void)                                            // Define a função principal
{                                                          
    char* sentidoInicial = "horario";                      // Define o primeiro comando da guinada.
    char* direcaoInicial = "frente";                       // Define o primeiro comando da arfagem.
    char* orientacaoInicial = "direita";                   // Define o primeiro comando da rolagem.

    vSemaphoreCreateBinary(semaforo);                      // Cria o semáforo binário.

	// Cria a tarefa de guinada
    xTaskCreate(guinada,                           // Informa a função executada pela tarefa.
        "Guinada",                                 // Define o nome da tarefa.
        TAMANHO_PILHA,                             // Define o tamanho da pilha.
        sentidoInicial,                            // Passa o sentido inicial como parâmetro.
        PRIORIDADE_MANOBRA,                        // Define a prioridade da tarefa.
        NULL);                                     // Não armazena um handle.

	// Cria a tarefa de arfagem
    xTaskCreate(arfagem,                                   
        "Arfagem",                                 
        TAMANHO_PILHA,                            
        direcaoInicial,                            // Passa a direção inicial como parâmetro.
        PRIORIDADE_MANOBRA,                        
        NULL);                                     

	// Cria a tarefa de rolagem
    xTaskCreate(rolagem,                                   
        "Rolagem",                                 
        TAMANHO_PILHA,                             
        orientacaoInicial,                         // Passa a orientacao inicial como parametro.
        PRIORIDADE_MANOBRA,                        
        NULL);                                     


	// Cria a tarefa de rádio frequência
    xTaskCreate(radioFrequencia,                           
        "Radio Frequencia",                       
        TAMANHO_PILHA,                             
        NULL,                                      // A tarefa de rádio não necessita receber parâmetro.
        PRIORIDADE_RADIO,                          // Define prioridade inferior às tarefas de manobra.
        NULL);                                    

    vTaskStartScheduler();                                 // Inicia o escalonador do FreeRTOS.

	for (;;) {}                                            // Laço de segurança caso o escalonador falhe.

    return 0;                                              // Retorna zero caso a função principal seja finalizada.
}                                                          