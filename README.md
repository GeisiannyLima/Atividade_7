# **Projeto: Display de LED RGB com Raspberry Pi Pico**

Este projeto implementa o controle de uma matriz de LEDs RGB WS2812B utilizando um **Raspberry Pi Pico** e a linguagem **C**. O sistema permite a exibição de números de 0 a 9 na matriz de LEDs, além de possibilitar a interação com um botão para incrementar ou decrementar o número exibido.

## **Recursos do Projeto**
- Controle de uma matriz de **25 LEDs RGB (5x5)**.
- Uso da **PIO (Programmable I/O)** do Raspberry Pi Pico para comunicação eficiente com os LEDs WS2812B.
- Botão para **incrementar e decrementar** o número exibido na matriz.
- Configuração do **tempo de espera** entre as atualizações da matriz.
- Algoritmo para converter a posição da matriz no índice do vetor de LEDs.

## **Hardware Utilizado**
- **Raspberry Pi Pico**
- **Matriz de LEDs WS2812B (25 LEDs, formato 5x5)**
- **Botão de entrada** para interação
- **Resistores e fiação** conforme necessário

## **Bibliotecas Utilizadas**
- `pico/stdlib.h` → Funções básicas do Pico.
- `hardware/pio.h` → Controle de hardware com PIO.
- `hardware/clocks.h` → Manipulação de clocks do Pico.
- `ws2818b.pio.h` → Biblioteca gerada para controle dos LEDs.

## **Funcionamento**
1. **Inicialização da PIO**: Configura a máquina de estado para controle da matriz.
2. **Exibição dos números**: Os LEDs são acesos de acordo com padrões predefinidos para cada número de 0 a 9.
3. **Interação via botão**: O botão permite navegar pelos números, aumentando ou diminuindo o valor exibido.
4. **Atualização do Display**: Os LEDs são atualizados a cada interação ou mudança de estado.

## **Como Compilar e Executar**
1. Instale o **SDK do Raspberry Pi Pico** e configure o ambiente de desenvolvimento.
2. Compile o código utilizando `cmake` e `make`:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
