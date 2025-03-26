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

    lcd.begin(16, 2);
    lcd.print("Pressione um");
    lcd.setCursor(0, 1);
    lcd.print("botao para comecar");
}

// Array com a sequência da música "Funky Town"
int funkyTown[] = {262, 330, 392, 262, 392, 330, 262};

// Notas correspondentes a cada botão
int botaoNotas[] = {262, 330, 392, 523};

LiquidCrystal lcd(9, 11, 10, 12, 13, A0);


