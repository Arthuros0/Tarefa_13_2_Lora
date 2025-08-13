# Comunicação IoT com LoRa (RFM95W) — BitDogLab / RP2040

Projeto desenvolvido para a **Tarefa 13** da Residência em Sistemas Embarcados (37M3SE), com foco na comunicação ponto a ponto usando o módulo **LoRa RFM95W 915 MHz** e a placa **BitDogLab (RP2040)**.

O sistema possui dois modos de operação:
- **Transmissor**: lê dados dos sensores BMP280 (temperatura, altitude) e AHT20 (temperatura, umidade) e envia via LoRa.
- **Receptor**: recebe os dados via LoRa e exibe no display OLED SSD1306.

---

## 📋 Funcionalidades

- Seleção de modo via botões:
  - **Botão A** → Modo Transmissor
  - **Botão B** → Modo Receptor
  - **Botão SW** → Reinicialização USB Boot
- Modo **Transmissor**:
  - Leitura de sensores BMP280 e AHT20
  - Envio de dados via LoRa no formato CSV
- Modo **Receptor**:
  - Recepção de dados via LoRa
  - Conversão e exibição no display
- Indicação visual de status com LEDs RGB
- Exibição clara e organizada das informações no display OLED

---

## 🛠️ Hardware Utilizado

- **Placa**: BitDogLab (RP2040)
- **Módulo LoRa**: RFM95W 915 MHz (chip SX1276)
- **Sensores**:
  - BMP280 (temperatura e altitude)
  - AHT20 (temperatura e umidade)
- **Display OLED**: SSD1306
- **LED RGB** e **matriz de LEDs**
- **Botões**: A, B e SW

---

## 📂 Estrutura do Código
```
lib/
├── ssd1306/ # Controle do display OLED
├── display/ # Funções de exibição de dados
├── led/ # Controle dos LEDs RGB
├── button/ # Configuração e interrupção de botões
├── matrix_leds/ # Controle da matriz de LEDs
├── buzzer/ # Controle do buzzer
├── aht20/ # Driver do sensor AHT20
├── bmp280/ # Driver do sensor BMP280
├── sensors/ # Função central de leitura de sensores
└── rfm95/ # Controle do módulo LoRa RFM95W
```

Arquivo principal: `main.c`

Principais funções:
- `init_peripherals()` → Inicializa botões, LEDs, matriz de LEDs e display
- `setup_lora_mode()` → Seleção e configuração do modo LoRa
- `tx_operation_mode()` → Loop de leitura de sensores e envio via LoRa
- `rx_operation_mode()` → Loop de recepção e exibição
- `display_data()` → Exibição formatada no display OLED

---

##📡 Parâmetros LoRa
- Frequência: 915 MHz

- Potência de transmissão: 17 dBm (modo transmissor)

- Protocolo: SPI (RP2040 ↔ RFM95W)

- Formato de dados: CSV com 4 valores:
  - bmp_temp,altitude_m,aht_temp,humidity


