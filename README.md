# Sistemas Operacionais Ciberfísicos

Repositório destinado ao armazenamento de atividades práticas, exercícios e projetos desenvolvidos na disciplina de **Sistemas Operacionais Ciberfísicos**, do curso de **Bacharelado em Ciência da Computação da Pontifícia Universidade Católica do Paraná (PUCPR)**.

Os projetos exploram conceitos de sistemas operacionais, programação concorrente, sistemas de tempo real (RTOS), sincronização de tarefas, sistemas embarcados e Internet das Coisas (IoT).

## Tecnologias utilizadas

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-00979D?style=for-the-badge)
![Contiki-NG](https://img.shields.io/badge/Contiki--NG-4B8BBE?style=for-the-badge)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

- **C e C++:** desenvolvimento de programas, manipulação de recursos e programação concorrente.
- **FreeRTOS:** gerenciamento de tarefas, escalonamento, prioridades, semáforos e mutexes.
- **Contiki-NG:** programação orientada a eventos e processos em sistemas embarcados.
- **MicroPython:** desenvolvimento de aplicações IoT com ESP32.
- **Visual Studio:** desenvolvimento e execução de projetos C/C++.
- **Linux:** compilação e execução de aplicações Contiki-NG.

## Estrutura do repositório

| Diretório | Descrição |
|---|---|
| [`aula-1/`](./aula-1) | Exercícios introdutórios de programação em C. |
| [`aula-2/`](./aula-2) | Arquivos de projeto das atividades práticas. |
| [`aula-3/`](./aula-3) | Arquivos de projeto das atividades práticas. |
| [`calculadora/`](./calculadora) | Implementação de uma calculadora em C++. |
| [`produtor-consumidor/`](./produtor-consumidor) | Simulação do problema produtor-consumidor utilizando threads e sincronização. |
| [`monitoramento-dados-vitais/`](./monitoramento-dados-vitais) | Simulação de monitoramento de sinais vitais com FreeRTOS. |
| [`tde1/`](./tde1) | Aplicação multitarefa com compartilhamento de recursos e mutex. |
| [`projeto-rtos/`](./projeto-rtos) | Projeto de controle de um quadricóptero utilizando FreeRTOS. |
| [`projeto-smartcity/`](./projeto-smartcity) | Sistema de monitoramento ambiental com ESP32 e MicroPython. |
| [`contiki-os/`](./contiki-os) | Exemplos de processos, eventos e aplicações utilizando Contiki-NG. |
| [`smart-healthcare/`](./smart-healthcare) | Simulação de um smartwatch com monitoramento de sinais vitais no Contiki-NG. |

## Projetos desenvolvidos

### 1. Produtor-Consumidor

Implementação do problema clássico de sincronização entre processos, utilizando C++ e recursos de programação concorrente.

O programa simula a produção e o consumo de biscoitos por duas threads, representadas pelos personagens Marge e Homer.

**Conceitos aplicados:**
- Programação concorrente com `std::thread`.
- Exclusão mútua com `std::mutex`.
- Sincronização com `std::condition_variable`.
- Buffer circular compartilhado.
- Controle de capacidade e prevenção de condições de corrida.

**Código:** [`produtor-consumidor/simpson.cpp`](./produtor-consumidor/simpson.cpp)

### 2. Monitoramento de Dados Vitais — FreeRTOS

Simulação de um sistema de monitoramento de saúde que utiliza tarefas independentes para acompanhar indicadores fisiológicos.

São monitorados três parâmetros:

- Frequência cardíaca (BPM).
- Temperatura corporal (°C).
- Saturação de oxigênio (%).

Cada tarefa gera valores simulados, verifica limites estabelecidos e apresenta mensagens de alerta quando necessário.

**Conceitos aplicados:**
- Criação e gerenciamento de tarefas.
- Escalonamento com FreeRTOS.
- Execução periódica com `vTaskDelay()`.
- Simulação de sensores e monitoramento contínuo.

**Código:** [`monitoramento-dados-vitais/example.c`](./monitoramento-dados-vitais/example.c)

### 3. TDE I — Multitarefa e Mutex

Aplicação desenvolvida com FreeRTOS para demonstrar o compartilhamento seguro de recursos entre tarefas concorrentes.

O programa executa três tarefas:

1. Exibição da data atual.
2. Exibição do horário atual.
3. Simulação da temperatura da cidade de Curitiba.

Todas compartilham um recurso de saída, protegido por um mutex para controlar o acesso à região crítica.

**Conceitos aplicados:**
- Tarefas concorrentes.
- Compartilhamento de memória.
- Mutex e exclusão mútua.
- Sincronização de acesso a recursos.

**Código:** [`tde1/socps.c`](./tde1/socps.c)

### 4. Projeto RTOS — Controle de Quadricóptero

Projeto de simulação do controle de um quadricóptero utilizando tarefas do FreeRTOS.

A aplicação trabalha com as três movimentações fundamentais de orientação de uma aeronave:

- **Guinada (Yaw):** rotação em torno do eixo vertical.
- **Arfagem (Pitch):** inclinação para frente ou para trás.
- **Rolagem (Roll):** inclinação lateral.

O sistema simula alterações nas velocidades de quatro motores e utiliza mecanismos de sincronização para controlar o acesso aos dados compartilhados.

**Conceitos aplicados:**
- Sistemas operacionais de tempo real.
- Escalonamento por prioridades.
- Sincronização entre tarefas.
- Semáforos e regiões críticas.
- Controle concorrente de recursos.

**Arquivos:**
- [`fase1.txt`](./projeto-rtos/fase1.txt)
- [`fase2.c`](./projeto-rtos/fase2.c)

### 5. Smart City — Monitoramento Ambiental com ESP32

Projeto de Internet das Coisas desenvolvido em MicroPython, utilizando um ESP32 para monitoramento de condições ambientais.

**Componentes utilizados:**
- ESP32 — microcontrolador.
- DHT11 — sensor de temperatura e umidade.
- LDR — sensor de luminosidade.
- Buzzer — dispositivo de alerta sonoro.

O sistema realiza leituras periódicas dos sensores e identifica situações que exigem atenção.

| Condição | Comportamento |
|---|---|
| Ambiente normal | Buzzer desligado |
| Temperatura acima de 30 °C | 1 aviso sonoro |
| Luminosidade abaixo de 30% | 2 avisos sonoros |
| Ambas as condições | 3 avisos sonoros |

**Conceitos aplicados:**
- Sistemas embarcados.
- Leitura de sensores digitais e analógicos.
- Conversão de leituras ADC.
- Controle PWM.
- Monitoramento ambiental e automação IoT.

**Código:** [`projeto-smartcity/main.py`](./projeto-smartcity/main.py)

### 6. Contiki-NG — Processos e Eventos

Conjunto de exemplos e atividades desenvolvidos com o sistema operacional Contiki-NG, voltado a dispositivos embarcados e aplicações de Internet das Coisas.

Os exemplos exploram o modelo de execução orientado a eventos e o gerenciamento de processos cooperativos.

**Conceitos aplicados:**
- Declaração de processos com `PROCESS()`.
- Inicialização automática com `AUTOSTART_PROCESSES()`.
- Implementação de processos com `PROCESS_THREAD()`.
- Controle de execução com `PROCESS_BEGIN()` e `PROCESS_END()`.
- Espera por eventos e temporizadores.
- Compilação para plataformas suportadas pelo Contiki-NG.

**Exemplos:** [`contiki-os/`](./contiki-os)

### 7. Smart Healthcare — Contiki-NG

Simulação de um smartwatch capaz de monitorar sinais vitais por meio de processos independentes executados no Contiki-NG.

O sistema possui quatro processos:

| Processo | Responsabilidade |
|---|---|
| Batimentos cardíacos | Simular medições de frequência cardíaca. |
| Saturação de oxigênio | Monitorar valores simulados de SpO₂. |
| Temperatura corporal | Realizar medições simuladas de temperatura. |
| Alertas | Receber eventos e apresentar notificações. |

As medições são realizadas em intervalos de três segundos, utilizando temporizadores e comunicação entre processos.

O sistema gera alertas quando os valores simulados ultrapassam os limites definidos no código.

**Conceitos aplicados:**
- Programação orientada a eventos.
- Processos cooperativos.
- Temporizadores com `etimer`.
- Comunicação por eventos com `process_post()`.
- Monitoramento periódico e tratamento de alertas.

**Código:** [`smart-healthcare/socps.c`](./smart-healthcare/socps.c)

> **Observação:** os projetos de monitoramento de saúde utilizam dados simulados e limites definidos para fins acadêmicos. Não se destinam a diagnóstico ou monitoramento clínico real.

## Como executar

Os requisitos e procedimentos de execução variam conforme o projeto.

### Projetos C e C++ — Visual Studio

Os diretórios com arquivos `.sln` e `.vcxproj` podem ser abertos no Microsoft Visual Studio com suporte ao desenvolvimento para desktop em C++.

1. Clone o repositório:

   ```bash
   git clone https://github.com/sergiocalazans/Sistemas-Operacionais-Ciberfisicos.git
   ```

2. Abra a pasta do projeto desejado.
3. Execute o arquivo `.sln` correspondente.
4. Compile e execute o projeto no Visual Studio.

Para os projetos baseados em FreeRTOS, é necessário configurar o ambiente com as bibliotecas, os arquivos de cabeçalho e a implementação do FreeRTOS utilizados nas atividades.

### Projetos Contiki-NG — Linux

Os exemplos do Contiki-NG dependem de uma instalação do sistema operacional e de suas ferramentas de compilação.

**Repositório oficial:** https://github.com/contiki-ng/contiki-ng

Após configurar o ambiente, organize o projeto de maneira que os caminhos relativos presentes no `Makefile` apontem corretamente para a instalação do Contiki-NG.

Para compilar um exemplo:

```bash
make TARGET=native
```

Para executar o binário gerado, por exemplo:

```bash
./socps.native
```

O nome do executável pode variar conforme o valor de `CONTIKI_PROJECT` definido no `Makefile`.

**Importante:** alguns exemplos possuem caminhos relativos diferentes para o arquivo `Makefile.include`. Caso a compilação apresente erro, verifique a variável `CONTIKI` no `Makefile` do projeto.

### Smart City — ESP32 e MicroPython

**Requisitos:**
- Placa ESP32 com MicroPython instalado.
- Sensor DHT11.
- Sensor LDR e circuito de leitura.
- Buzzer.
- Ambiente de desenvolvimento compatível, como Thonny.

**Procedimento:**

1. Monte o circuito com os sensores e o buzzer.
2. Conecte o ESP32 ao computador.
3. Configure o interpretador MicroPython no ambiente de desenvolvimento.
4. Abra o arquivo `projeto-smartcity/main.py`.
5. Execute o programa na placa.

O sistema apresentará as leituras no terminal e emitirá alertas de acordo com as condições identificadas.

## Conceitos estudados

Ao longo das atividades, são explorados os seguintes conteúdos:

- Fundamentos de sistemas operacionais.
- Processos e threads.
- Concorrência e paralelismo.
- Escalonamento e prioridades.
- Sistemas operacionais de tempo real (RTOS).
- Regiões críticas e condições de corrida.
- Sincronização com semáforos e mutexes.
- Deadlock e compartilhamento de recursos.
- Programação orientada a eventos.
- Sistemas embarcados e Internet das Coisas.
- Sensores, atuadores e monitoramento de dados.

## Contexto acadêmico

| Informação | Descrição |
|---|---|
| Instituição | Pontifícia Universidade Católica do Paraná (PUCPR) |
| Curso | Bacharelado em Ciência da Computação |
| Disciplina | Sistemas Operacionais Ciberfísicos |
| Período | 4º período |
| Ano | 2026 |
| Natureza | Atividades práticas e projetos acadêmicos |

## Autor

**Sérgio Henrique da Cunha Calazans**

Acadêmico de Bacharelado em Ciência da Computação — PUCPR.

[![GitHub](https://img.shields.io/badge/GitHub-sergiocalazans-181717?style=flat-square&logo=github)](https://github.com/sergiocalazans)

---

Este repositório possui finalidade acadêmica, reunindo implementações práticas para estudo de sistemas operacionais, programação concorrente, sistemas embarcados e aplicações ciberfísicas.
