#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <condition_variable>

int* fila = nullptr;

int capacidade = 0;
int primeiro = 0;
int ultimo = 0;
int quantidade = 0;

const int TOTAL_BISCOITOS = 10;

std::mutex mutexFila;
std::condition_variable podeProduzir;
std::condition_variable podeConsumir;


/* Protótipos */
void inserir(int elemento);
int pegar();
int totalNaFila();
void produtor();
void consumidor();


int main()
{
    printf("Digite a capacidade da lata de biscoitos: ");

    if (scanf_s("%d", &capacidade) != 1 || capacidade <= 0)
    {
        printf("Capacidade invalida.\n");
        return 1;
    }

    fila = (int*)malloc(capacidade * sizeof(int));

    if (fila == nullptr)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("\nLata criada com capacidade para %d biscoitos.\n\n", capacidade);

    std::thread marge(produtor);
    std::thread homer(consumidor);

    marge.join();
    homer.join();

    free(fila);
    fila = nullptr;

    printf("\nTodos os biscoitos foram produzidos e consumidos.\n");
    printf("Memoria liberada com sucesso.\n");

    return 0;
}


int totalNaFila()
{
    return quantidade;
}


void inserir(int elemento)
{
    fila[ultimo] = elemento;

    ultimo = (ultimo + 1) % capacidade;

    quantidade++;
}


int pegar()
{
    int elemento = fila[primeiro];

    primeiro = (primeiro + 1) % capacidade;

    quantidade--;

    return elemento;
}


void produtor()
{
    for (int i = 1; i <= TOTAL_BISCOITOS; i++)
    {
        int biscoito = i;

        std::unique_lock<std::mutex> lock(mutexFila);

        podeProduzir.wait(lock, []()
            {
                return quantidade < capacidade;
            });

        inserir(biscoito);

        printf("Marge produziu o biscoito %d.\n", biscoito);
        printf("Total na lata: %d\n\n", totalNaFila());

        lock.unlock();

        podeConsumir.notify_one();
    }
}


void consumidor()
{
    for (int i = 1; i <= TOTAL_BISCOITOS; i++)
    {
        std::unique_lock<std::mutex> lock(mutexFila);

        podeConsumir.wait(lock, []()
            {
                return quantidade > 0;
            });

        int biscoito = pegar();

        printf("Homer consumiu o biscoito %d.\n", biscoito);
        printf("Total na lata: %d\n\n", totalNaFila());

        lock.unlock();

        podeProduzir.notify_one();
    }
}