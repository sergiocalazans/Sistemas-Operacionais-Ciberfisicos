
from machine import Pin, ADC, PWM
import dht
import time

# ==========================================
# SMART CITY - MONITORAMENTO AMBIENTAL
# ESP32 + DHT11 + LDR + BUZZER
# ==========================================

# --- CONFIGURACAO DOS SENSORES ---

# Sensor DHT11
sensor_temp = dht.DHT11(Pin(15))

# Sensor de luminosidade LDR
sensor_luz = ADC(Pin(34))
sensor_luz.atten(ADC.ATTN_11DB)

# Buzzer com PWM
buzzer = PWM(Pin(18))
buzzer.freq(1500)
buzzer.duty(0)

# --- PARAMETROS DO SISTEMA ---

TEMP_MAX = 30
LUMINOSIDADE_MIN = 30

INTERVALO_LEITURA = 3

# --- FUNCOES ---

def emitir_som(frequencia, duracao):
    """Aciona o buzzer usando PWM."""
    buzzer.freq(frequencia)
    buzzer.duty(512)
    time.sleep(duracao)
    buzzer.duty(0)


def tocar_buzzer(quantidade):
    """Emite a quantidade de avisos definida."""
    for i in range(quantidade):
        emitir_som(1500, 0.5)
        time.sleep(0.2)


def ler_temperatura():
    """Le temperatura e umidade do DHT11."""
    sensor_temp.measure()

    temperatura = sensor_temp.temperature()
    umidade = sensor_temp.humidity()

    return temperatura, umidade


def ler_luminosidade():
    """Le o LDR e calcula a luminosidade relativa."""
    leitura = sensor_luz.read()

    # Escala invertida conforme a montagem
    luminosidade = ((4095 - leitura) / 4095) * 100

    return leitura, luminosidade


def verificar_ambiente(temperatura, luminosidade):
    """Verifica as condicoes ambientais."""

    temperatura_alta = temperatura > TEMP_MAX
    luminosidade_baixa = luminosidade < LUMINOSIDADE_MIN

    if temperatura_alta and luminosidade_baixa:
        print("ALERTA: Temperatura alta e pouca luz!")
        tocar_buzzer(3)

    elif temperatura_alta:
        print("ALERTA: Temperatura elevada!")
        tocar_buzzer(1)

    elif luminosidade_baixa:
        print("ALERTA: Luminosidade baixa!")
        tocar_buzzer(2)

    else:
        print("STATUS: Ambiente dentro dos parametros.")
        buzzer.duty(0)


def exibir_dados(temperatura, umidade, adc, luminosidade):
    """Exibe as informacoes no terminal."""

    print("\n================================")
    print("    SMART CITY - MONITORAMENTO")
    print("================================")

    print("Temperatura: {} C".format(temperatura))
    print("Umidade: {} %".format(umidade))
    print("Luminosidade: {:.1f} %".format(luminosidade))
    print("Leitura ADC:", adc)

    print("--------------------------------")


# --- PROGRAMA PRINCIPAL ---

print("Inicializando Smart City...")
time.sleep(2)

try:
    while True:
        try:
            # Leitura dos sensores
            temperatura, umidade = ler_temperatura()
            adc, luminosidade = ler_luminosidade()

            # Exibicao dos dados
            exibir_dados(
                temperatura,
                umidade,
                adc,
                luminosidade
            )

            # Verificacao dos alertas
            verificar_ambiente(
                temperatura,
                luminosidade
            )

        except OSError as erro:
            print("Erro na leitura do sensor:", erro)
            buzzer.duty(0)

        time.sleep(INTERVALO_LEITURA)

except KeyboardInterrupt:
    print("\nMonitoramento encerrado.")

finally:
    buzzer.duty(0)
    buzzer.deinit()
