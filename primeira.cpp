
#define BUZZER 8
#define LED_VERDE 6
#define LED_VERMELHO 7

#define BOTAO1 2
#define BOTAO2 3
#define BOTAO3 4
#define BOTAO4 5

LiquidCrystal lcd(9, 11, 10, 12, 13, A0);

int funkyTown[] = {262, 330, 392, 262, 392, 330, 262};
int botaoNotas[] = {262, 330, 392, 523};

void tocarNota(int nota) {
    tone(BUZZER, nota, 300);
    delay(400);
    noTone(BUZZER);
}
