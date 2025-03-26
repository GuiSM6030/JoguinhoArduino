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

// Array com a sequência da música "Funky Town"
int funkyTown[] = {262, 330, 392, 262, 392, 330, 262};
// Notas correspondentes a cada botão
int botaoNotas[] = {262, 330, 392, 523};
LiquidCrystal lcd(9, 11, 10, 12, 13, A0);

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

void tocarNota(int nota) {
    tone(BUZZER, nota, 300);
    delay(400);              
    noTone(BUZZER);
}

bool verificarSequencia(int nivel) {
    for (int i = 0; i < nivel; i++) {
        bool notaCorreta = false;
        
        while (!notaCorreta) {
            if (digitalRead(BOTAO1) == LOW) {
                tocarNota(botaoNotas[0]);
                if (botaoNotas[0] == funkyTown[i]) {
                    notaCorreta = true;
                } else {
                    return false;
                }
                while (digitalRead(BOTAO1) == LOW); 
            }
            
            if (digitalRead(BOTAO2) == LOW) {
                tocarNota(botaoNotas[1]);
                if (botaoNotas[1] == funkyTown[i]) {
                    notaCorreta = true;
                } else {
                    return false;
                }
                while (digitalRead(BOTAO2) == LOW);
            }
            
            if (digitalRead(BOTAO3) == LOW) {
                tocarNota(botaoNotas[2]);
                if (botaoNotas[2] == funkyTown[i]) {
                    notaCorreta = true;
                } else {
                    return false;
                }
                while (digitalRead(BOTAO3) == LOW);
            }
            
            if (digitalRead(BOTAO4) == LOW) {
                tocarNota(botaoNotas[3]);
                if (botaoNotas[3] == funkyTown[i]) {
                    notaCorreta = true;
                } else {
                    return false;
                }
                while (digitalRead(BOTAO4) == LOW);
            }
        }
    }
    return true;
}

void loop() {
    // Inicia o jogo ao pressionar qualquer botão
    if (digitalRead(BOTAO1) == LOW || digitalRead(BOTAO2) == LOW || 
        digitalRead(BOTAO3) == LOW || digitalRead(BOTAO4) == LOW) {
        
        int nivel = 3; // Nível inicial
        bool ganhou = true;

        while (ganhou && nivel <= 7) {
            // Mostra o nível atual
            lcd.clear();
            lcd.print("Nivel: ");
            lcd.print(nivel);
            delay(1000);

            // Toca a sequência para memorização
            for (int i = 0; i < nivel; i++) {
                tocarNota(funkyTown[i]);
                delay(500);
            }

            lcd.clear();
            lcd.print("Sua vez!");

            // Verifica a resposta do jogador
            if (!verificarSequencia(nivel)) {
                ganhou = false;
                lcd.clear();
                lcd.print("Errou! Fim do jogo");
                digitalWrite(LED_VERMELHO, HIGH);
                delay(2000);
                digitalWrite(LED_VERMELHO, LOW);
            } else {
                lcd.clear();
                lcd.print("Correto!");
                digitalWrite(LED_VERDE, HIGH);
                delay(1000);
                digitalWrite(LED_VERDE, LOW);
                nivel++;
            }
        }

        // Mensagem de vitória
        if (ganhou) {
            lcd.clear();
            lcd.print("Parabens! Venceu!");
            delay(2000);
        }
        
        // Reinicia o jogo
        lcd.clear();
        lcd.print("Pressione um");
        lcd.setCursor(0, 1);
        lcd.print("botao para jogar");
    }
}

