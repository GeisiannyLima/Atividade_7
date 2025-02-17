#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

// Configuração dos pinos dos botões
#define BUTTON_A_PIN 5

// Inicializa a máquina PIO para controle da matriz de LEDs.
void npInit(uint pin) {
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

// Atribui uma cor RGB a um LED.
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

// Limpa o buffer de pixels.
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
 #include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

// Biblioteca gerada pelo arquivo .pio durante compilação.
#include "ws2818b.pio.h"

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

// Configuração dos pinos dos botões
#define BUTTON_A_PIN 5

// Inicializa a máquina PIO para controle da matriz de LEDs.
void npInit(uint pin) {
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

// Atribui uma cor RGB a um LED.
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

// Limpa o buffer de pixels.
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

// Escreve os dados do buffer nos LEDs.
void npWrite() {
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Função para converter a posição do matriz para uma posição do vetor.
int getIndex(int x, int y) {
  if (y % 2 == 0) {
    return 24-(y * 5 + x); // Linha par (esquerda para direita).
  } else {
    return 24-(y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
  }
}

// Função para desenhar o número atual.
void drawNumber(int number) {
  // Definindo números de 0 a 9 como padrões de LEDs.
  int numbers[10][5][5][3] = {
    // Definição dos padrões para números de 0 a 9
    // O formato é [linha][coluna][RGB]
    // 0
    {
      {{24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
    },
    //1
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
    },
    //2
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //3
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //4
    {
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //5
    {
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //6
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
      {{24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //7
    {
      {{24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //8
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {0, 0, 0}}
    }
    //9
    {
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}},
      {{24, 243, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}, {24, 243, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}},
      {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {24, 243, 0}}
    }
    // Continue a definição dos números de 2 a 9 de maneira similar...
  };
  
  // Limpar os LEDs antes de desenhar
  npClear();

  // Desenhar o número correspondente
  for (int linha = 0; linha < 5; linha++) {
    for (int coluna = 0; coluna < 5; coluna++) {
      int posicao = getIndex(linha, coluna);
      npSetLED(posicao, numbers[number][linha][coluna][0], numbers[number][linha][coluna][1], numbers[number][linha][coluna][2]);
    }
  }
  npWrite();
}

int main() {
  stdio_init_all();

  // Configuração dos pinos dos botões
  gpio_init(BUTTON_A_PIN);
  gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_A_PIN);

  // Inicializa a matriz de LEDs
  npInit(LED_PIN);
  npClear();

  // Valor inicial
  int valor = 0;

  // Loop principal
  while (true) {
    // Verificar se o botão A foi pressionado
    if (gpio_get(BUTTON_A_PIN) == 0) {
      valor++;
      if (valor > 9) {
        valor = 0;  // Reseta para 0 quando ultrapassar o limite
      }

      drawNumber(valor);  // Desenha o número na matriz de LEDs
      sleep_ms(500); // Debounce para o botão
    }
  }
}
