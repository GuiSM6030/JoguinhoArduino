#include <LiquidCrystal.h>

// Definição dos pinos
#define BUZZER 8
#define LED_VERDE 6
#define LED_VERMELHO 7

// Novos LEDs para os botões
#define LED_BOTAO1 A1
#define LED_BOTAO2 A2

// Botões com pull-up interno
#define BOTAO1 2
#define BOTAO2 3
#define BOTAO3 4
#define BOTAO4 5

LiquidCrystal lcd(9, 11, 10, 12, 13, A0);

// Notas 
#define NOTA_E4  330  // Mi (Botão 1 - Verde)
#define NOTA_A4  440  // Lá (Botão 2 - Vermelho)
#define NOTA_Cs5 554  // Dó# (Botão 3 - Amarelo)
#define NOTA_E5  659  // Mi (Botão 4 - Azul)

// sequências das músicas
// Musica 1
int musica1[] = {NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_E5, NOTA_A4, NOTA_E4};
int musica1Durations[] = {4, 4, 2, 4, 4, 2};

// Musica 2 
int musica2[] = {NOTA_E4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_Cs5, NOTA_Cs5, NOTA_A4};
int musica2Durations[] = {4, 4, 4, 4, 4, 4, 4, 4};

// musica 3 
int musica3[] = {NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_Cs5, NOTA_E5, NOTA_E4};
int musica3Durations[] = {4, 4, 4, 4, 2, 2};

// musica 4 
int musica4[] = {NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4, NOTA_Cs5, NOTA_A4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4, NOTA_E5, NOTA_Cs5};
int musica4Durations[] = {4, 8, 4, 4, 4, 2, 4, 8, 4, 4, 4, 2};

// musica 5 
int musica5[] = {NOTA_E4, NOTA_A4, NOTA_E4, NOTA_Cs5, NOTA_E5, NOTA_Cs5, NOTA_A4, NOTA_A4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4};
int musica5Durations[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

struct Musica {
  const char* nome;
  int* notas;
  int* duracoes;
  int tamanho;
  int niveis;
};

Musica musicas[] = {
  {"Musica 1", musica1, musica1Durations, sizeof(musica1)/sizeof(int), 5},
  {"Musica 2", musica2, musica2Durations, sizeof(musica2)/sizeof(int), 4},
  {"Musica 3", musica3, musica3Durations, sizeof(musica3)/sizeof(int), 4},
  {"Musica 4", musica4, musica4Durations, sizeof(musica4)/sizeof(int), 5},
  {"Musica 5", musica5, musica5Durations, sizeof(musica5)/sizeof(int), 4}
};

const int NUM_MUSICAS = sizeof(musicas)/sizeof(Musica);
int musicaSelecionada = 0;
int nivelAtual = 1;
int vidas = 3;  // Sistema de vidas adicionado
int sequencia[12]; 
int indiceSequencia = 0;
bool emJogo = false;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  pinMode(LED_BOTAO1, OUTPUT);
  pinMode(LED_BOTAO2, OUTPUT);
  
  pinMode(BOTAO1, INPUT_PULLUP);
  pinMode(BOTAO2, INPUT_PULLUP);
  pinMode(BOTAO3, INPUT_PULLUP);
  pinMode(BOTAO4, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  randomSeed(analogRead(A3));
  
  // Mensagem inicial
  lcd.print("Pressione um");
  lcd.setCursor(0, 1);
  lcd.print("botao p/ comecar");
  
  // Espera qualquer botão ser pressionado
  while(digitalRead(BOTAO1) && digitalRead(BOTAO2) && digitalRead(BOTAO3) && digitalRead(BOTAO4)) {
    delay(100);
  }
  
  menuSelecaoMusica();
}

void loop() {
  // O loop principal é controlado pelas funções chamadas no setup
}

void tocarMusicaCompleta() {
  emJogo = true;
  for(int i = 0; i < musicas[musicaSelecionada].tamanho; i++) {
    int nota = musicas[musicaSelecionada].notas[i];
    int duracao = 1500 / musicas[musicaSelecionada].duracoes[i];
    
    acenderLedDaNota(nota);
    tone(BUZZER, nota, duracao);
    
    // Pausa proporcional à duração da nota
    int pausa = duracao * 1.3;
    delay(pausa);
    
    noTone(BUZZER);
    apagarLedsBotoes();
    
    // Pequena pausa entre notas
    delay(duracao * 0.2);
  }
  emJogo = false;
}

void acenderLedDaNota(int nota) {
  if(nota == NOTA_E4) {
    digitalWrite(LED_BOTAO1, HIGH);
  } 
  else if(nota == NOTA_A4) {
    digitalWrite(LED_BOTAO2, HIGH);
  }
  else if(nota == NOTA_Cs5) {
    digitalWrite(LED_VERMELHO, HIGH);
  }
  else if(nota == NOTA_E5) {
    digitalWrite(LED_VERDE, HIGH);
  }
}

void apagarLedsBotoes() {
  digitalWrite(LED_BOTAO1, LOW);
  digitalWrite(LED_BOTAO2, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, LOW);
}

void menuSelecaoMusica() {
  emJogo = false;
  vidas = 3; // Reset de vidas ao voltar ao menu
  while(true) {
    lcd.clear();
    lcd.print("Escolha a musica:");
    lcd.setCursor(0, 1);
    lcd.print(musicas[musicaSelecionada].nome);
    
    while(true) {
      if(!digitalRead(BOTAO1)) {
        musicaSelecionada = (musicaSelecionada - 1 + NUM_MUSICAS) % NUM_MUSICAS;
        delay(200);
        break;
      }
      if(!digitalRead(BOTAO2)) {
        musicaSelecionada = (musicaSelecionada + 1) % NUM_MUSICAS;
        delay(200);
        break;
      }
      if(!digitalRead(BOTAO3)) {
        delay(200);
        lcd.clear();
        lcd.print("Tocando musica...");
        tocarMusicaCompleta();
        iniciarJogo();
        return;
      }
      delay(50);
    }
  }
}

void iniciarJogo() {
  nivelAtual = 1;
  emJogo = true;
  
  // Gera a sequência completa uma vez no início
  for(int i = 0; i < musicas[musicaSelecionada].tamanho; i++) {
    sequencia[i] = i; // Usa todas as notas em ordem
  }
  
  while(nivelAtual <= musicas[musicaSelecionada].niveis && vidas > 0) {
    lcd.clear();
    lcd.print("Nivel ");
    lcd.print(nivelAtual);
    lcd.print("/");
    lcd.print(musicas[musicaSelecionada].niveis);
    lcd.setCursor(0, 1);
    lcd.print("Vidas: ");
    lcd.print(vidas);
    delay(1000);
    
    // Toca a sequência até o nível atual
    tocarSequencia(nivelAtual);
    
    // Espera a resposta do jogador
    if(!verificarResposta(nivelAtual)) {
      vidas--; // Perde uma vida
      lcd.clear();
      lcd.print("Errou! Vidas: ");
      lcd.print(vidas);
      piscarLed(LED_VERMELHO, 3);
      
      if(vidas > 0) {
        // Ainda tem vidas, reinicia o nível
        nivelAtual = 1;
        delay(1000);
        continue;
      } else {
        // Sem vidas, volta para o menu
        lcd.clear();
        lcd.print("Game Over!");
        lcd.setCursor(0, 1);
        lcd.print("Voltando ao menu");
        delay(2000);
        menuSelecaoMusica();
        return;
      }
    }
    
    lcd.clear();
    lcd.print("Correto!");
    piscarLed(LED_VERDE, 3);
    nivelAtual++;
    delay(1000);
  }
  
  if(vidas > 0) {
    lcd.clear();
    lcd.print("Parabens, voce");
    lcd.setCursor(0, 1);
    lcd.print("venceu!");
    piscarLed(LED_VERDE, 5);
    delay(3000);
  }
  menuSelecaoMusica();
}

void tocarSequencia(int tamanho) {
  lcd.clear();
  lcd.print("Prestem atencao!");
  delay(500);
  
  for(int i = 0; i < tamanho; i++) {
    int notaIndex = sequencia[i];
    int nota = musicas[musicaSelecionada].notas[notaIndex];
    int duracao = 1000 / musicas[musicaSelecionada].duracoes[notaIndex];
    
    acenderLedDaNota(nota);
    tone(BUZZER, nota, duracao);
    delay(duracao + 50);
    noTone(BUZZER);
    apagarLedsBotoes();
  }
}

bool verificarResposta(int tamanho) {
  lcd.clear();
  lcd.print("Repita a");
  lcd.setCursor(0, 1);
  lcd.print("sequencia!");
  delay(1000);
  
  indiceSequencia = 0;
  
  while(indiceSequencia < tamanho) {
    int botaoPressionado = -1;
    
    while(botaoPressionado == -1) {
      if(!digitalRead(BOTAO1)) {
        botaoPressionado = 0;
        digitalWrite(LED_BOTAO1, HIGH);
      }
      else if(!digitalRead(BOTAO2)) {
        botaoPressionado = 1;
        digitalWrite(LED_BOTAO2, HIGH);
      }
      else if(!digitalRead(BOTAO3)) {
        botaoPressionado = 2;
        digitalWrite(LED_VERMELHO, HIGH);
      }
      else if(!digitalRead(BOTAO4)) {
        botaoPressionado = 3;
        digitalWrite(LED_VERDE, HIGH);
      }
      delay(50);
    }
    
    int nota;
    switch(botaoPressionado) {
      case 0: nota = NOTA_E4; break;
      case 1: nota = NOTA_A4; break;
      case 2: nota = NOTA_Cs5; break;
      case 3: nota = NOTA_E5; break;
    }
    
    int duracao = 200;
    tone(BUZZER, nota, duracao);
    delay(duracao);
    noTone(BUZZER);
    apagarLedsBotoes();
    
    int notaEsperada = musicas[musicaSelecionada].notas[sequencia[indiceSequencia]];
    if(nota != notaEsperada) {
      return false;
    }
    
    indiceSequencia++;
    delay(100);
  }
  
  return true;
}

void piscarLed(int led, int vezes) {
  for(int i = 0; i < vezes; i++) {
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  }
}
