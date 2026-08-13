#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Protótipos */
double soma(double a, double b);
double subtracao(double a, double b);
double multiplicacao(double a, double b);
double divisao(double a, double b);
double raiz_quadrada(double a);
double exponenciacao(double a, double b);
double calculadora(char operacao, double a, double b);
void menu();

int main(void) {
    for (;;) {
        double a;
        double b;
        double resultado;
        char operacao;

        menu();

        if (scanf_s(" %c", &operacao, 1) != 1) {
            printf("Erro ao ler a operacao.\n");
            break;
        }

        if (operacao == 's' || operacao == 'S') {
            break;
        }

        printf("Digite o primeiro numero: ");

        if (scanf_s("%lf", &a) != 1) {
            printf("Primeiro numero invalido.\n");
            break;
        }

        if (operacao == 'r' || operacao == 'R') {
            b = 0;
        }
        else {
            printf("Digite o segundo numero: ");

            if (scanf_s("%lf", &b) != 1) {
                printf("Segundo numero invalido.\n");
                break;
            }
        }

        if ((operacao == '/' && b == 0) ||
            ((operacao == 'r' || operacao == 'R') && a < 0)) {

            if (operacao == '/') {
                printf("Erro: divisao por zero!\n");
            }
            else {
                printf("Erro: raiz quadrada de numero negativo!\n");
            }

            continue;
        }

        resultado = calculadora(operacao, a, b);

        printf("Resultado: %.2f\n", resultado);
    }

    printf("Calculadora encerrada.\n");

    return 0;
}

double soma(double a, double b) {
    return a + b;
}

double subtracao(double a, double b) {
    return a - b;
}

double multiplicacao(double a, double b) {
    return a * b;
}

double divisao(double a, double b) {
    return a / b;
}

double raiz_quadrada(double a) {
    return sqrt(a);
}

double exponenciacao(double a, double b) {
    return pow(a, b);
}

double calculadora(char operacao, double a, double b) {
    double resultado = 0;

    switch (operacao) {
    case '+':
        resultado = soma(a, b);
        break;

    case '-':
        resultado = subtracao(a, b);
        break;

    case '*':
        resultado = multiplicacao(a, b);
        break;

    case '/':
        resultado = divisao(a, b);
        break;

    case 'R':
    case 'r':
        resultado = raiz_quadrada(a);
        break;

    case 'E':
    case 'e':
        resultado = exponenciacao(a, b);
        break;

    default:
        printf("Erro: operacao invalida!\n");
        break;
    }

    return resultado;
}

void menu() {
    printf("\nCalculadora Simples\n");
    printf("Operacoes disponiveis:\n");
    printf("+ : Adicao\n");
    printf("- : Subtracao\n");
    printf("* : Multiplicacao\n");
    printf("/ : Divisao\n");
    printf("r : Raiz Quadrada\n");
    printf("e : Exponenciacao\n");
    printf("s : Sair\n");
    printf("Escolha uma operacao: ");
}
