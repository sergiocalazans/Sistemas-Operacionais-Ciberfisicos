#include <stdio.h>
#include <stdlib.h>

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
    if (b == 0) {
        printf("Erro: divisao por zero!\n");
        exit(EXIT_FAILURE);
    }

    return a / b;
}

double calculadora(char operacao, double a, double b) {
    double resultado;

    if (operacao == '+') {
        resultado = soma(a, b);
    }
    else if (operacao == '-') {
        resultado = subtracao(a, b);
    }
    else if (operacao == '*') {
        resultado = multiplicacao(a, b);
    }
    else if (operacao == '/') {
        resultado = divisao(a, b);
    }
    else {
        printf("Erro: operacao invalida!\n");
        exit(EXIT_FAILURE);
    }

    return resultado;
}

int main(void) {
    while (1) {
        double a;
        double b;
        double resultado;
        char operacao;

        printf("\nDigite a operacao (+, -, *, /) ou 's' para sair: ");

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

        printf("Digite o segundo numero: ");

        if (scanf_s("%lf", &b) != 1) {
            printf("Segundo numero invalido.\n");
            break;
        }

        resultado = calculadora(operacao, a, b);

        printf("Resultado: %.2f\n", resultado);
    }

    printf("Calculadora encerrada.\n");

    return 0;
}