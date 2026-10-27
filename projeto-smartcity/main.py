from machine import Pin, ADC
import dht
import time

# Sensores e atuador
sensor_temp = dht.DHT11(Pin(4))
sensor_luz = ADC(Pin(34))
sensor_luz.atten(ADC.ATTN_11DB)
buzzer = Pin(18, Pin.OUT)
buzzer.value(0)

# Limites demonstrativos
TEMP_MAX = 30
LUMINOSIDADE_MIN = 30

def tocar_buzzer(quantidade):
    for _ in range(quantidade):
        buzzer.value(1)
        time.sleep_ms(200)
        buzzer.value(0)
        time.sleep_ms(200)

def ler_luminosidade():
    leitura = sensor_luz.read()
    percentual = leitura / 4095 * 100
    return leitura, percentual

def verificar_ambiente(temperatura, luminosidade):
    calor = temperatura > TEMP_MAX
    escuro = luminosidade < LUMINOSIDADE_MIN
    if calor and escuro:
        print('ALERTA: Calor e baixa luminosidade!')
        tocar_buzzer(3)
    elif calor:
        print('ALERTA: Temperatura elevada!')
        tocar_buzzer(1)
    elif escuro:
        print('ALERTA: Luminosidade baixa!')
        tocar_buzzer(2)
    else:
        print('Ambiente dentro dos parametros.')
        buzzer.value(0)

while True:
    try:
        sensor_temp.measure()
        temperatura = sensor_temp.temperature()
        umidade = sensor_temp.humidity()
        leitura_adc, luminosidade = ler_luminosidade()
        print('\n--- MONITORAMENTO AMBIENTAL ---')
        print('Temperatura:', temperatura, 'C')
        print('Umidade:', umidade, '%')
        print('Luminosidade relativa: {:.1f}%'.format(luminosidade))
        print('ADC:', leitura_adc)
        verificar_ambiente(temperatura, luminosidade)
    except OSError as erro:
        print('Erro na leitura do sensor:', erro)
        buzzer.value(0)
    time.sleep(2)
