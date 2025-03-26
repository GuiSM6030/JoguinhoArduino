#include <LiquidCrystal.h>

// Definição dos pinos
#define BUZZER 8
#define LED_VERDE 6
#define LED_VERMELHO 7

// Botões com pull-up interno
#define BOTAO1 2
#define BOTAO2 3
#define BOTAO3 4
#define BOTAO4 5

void setup() {
    pinMode(BUZZER, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_VERMELHO, OUTPUT);

    pinMode(BOTAO1, INPUT_PULLUP);
    pinMode(BOTAO2, INPUT_PULLUP);
    pinMode(BOTAO3, INPUT_PULLUP);
    pinMode(BOTAO4, INPUT_PULLUP);
}
