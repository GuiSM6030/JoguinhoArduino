#include <LiquidCrystal.h>

#define BUZZER 8
#define LED_VERDE 6
#define LED_VERMELHO 7
#define LED_BOTAO1 A1
#define LED_BOTAO2 A2

#define BOTAO1 2
#define BOTAO2 3
#define BOTAO3 4
#define BOTAO4 5

LiquidCrystal lcd(9, 11, 10, 12, 13, A0);

#define NOTA_E4  330  // Mi (Botão 1 - Verde)
#define NOTA_A4  440  // Lá (Botão 2 - Vermelho)
#define NOTA_Cs5 554  // Dó# (Botão 3 - Amarelo)
#define NOTA_E5  659  // Mi (Botão 4 - Azul)

int jingleBell[] = {NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_E5, NOTA_A4, NOTA_E4};
int jingleDurations[] = {4, 4, 2, 4, 4, 2};

int funkyTown[] = {NOTA_E4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_Cs5, NOTA_Cs5, NOTA_A4};
int funkyDurations[] = {4, 4, 4, 4, 4, 4, 4, 4};

int gonnaFlyNow[] = {NOTA_E4, NOTA_A4, NOTA_Cs5, NOTA_Cs5, NOTA_E5, NOTA_E4};
int gonnaFlyDurations[] = {4, 4, 4, 4, 2, 2};

int happyBirthday[] = {NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4, NOTA_Cs5, NOTA_A4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4, NOTA_E5, NOTA_Cs5};
int happyBirthdayDurations[] = {4, 8, 4, 4, 4, 2, 4, 8, 4, 4, 4, 2};

int myGirl[] = {NOTA_E4, NOTA_A4, NOTA_E4, NOTA_Cs5, NOTA_E5, NOTA_Cs5, NOTA_A4, NOTA_A4, NOTA_E4, NOTA_E4, NOTA_A4, NOTA_E4};
int myGirlDurations[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

struct Musica {
  const char* nome;
  int* notas;
  int* duracoes;
  int tamanho;
  int niveis;
};

Musica musicas[] = {
  {"Jingle Bell", jingleBell, jingleDurations, sizeof(jingleBell)/sizeof(int), 5},
  {"Funky Town", funkyTown, funkyDurations, sizeof(funkyTown)/sizeof(int), 4},
  {"Rocky Theme", gonnaFlyNow, gonnaFlyDurations, sizeof(gonnaFlyNow)/sizeof(int), 4},
  {"Happy Birthday", happyBirthday, happyBirthdayDurations, sizeof(happyBirthday)/sizeof(int), 5},
  {"My Girl", myGirl, myGirlDurations, sizeof(myGirl)/sizeof(int), 4}
};

const int NUM_MUSICAS = sizeof(musicas)/sizeof(Musica);
int musicaSelecionada = 0;
int nivelAtual = 1;
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
 
  lcd.print("Pressione um");
  lcd.setCursor(0, 1);
  lcd.print("botao p/ comecar");
  
  while(digitalRead(BOTAO1) && digitalRead(BOTAO2) && digitalRead(BOTAO3) && digitalRead(BOTAO4)) {
    delay(100);
  }
  
  menuSelecaoMusica();
}

void loop() {
}

void tocarMusicaCompleta() {
  emJogo = true;
  for(int i = 0; i < musicas[musicaSelecionada].tamanho; i++) {
    int nota = musicas[musicaSelecionada].notas[i];
    int duracao = 1500 / musicas[musicaSelecionada].duracoes[i];
    
    acenderLedDaNota(nota);
    tone(BUZZER, nota, duracao);

    int pausa = duracao * 1.3;
    delay(pausa);
    
    noTone(BUZZER);
    apagarLedsBotoes();

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

  for(int i = 0; i < musicas[musicaSelecionada].tamanho; i++) {
    sequencia[i] = i; 
  }
  
  while(nivelAtual <= musicas[musicaSelecionada].niveis) {
    lcd.clear();
    lcd.print("Nivel ");
    lcd.print(nivelAtual);
    lcd.print("/");
    lcd.print(musicas[musicaSelecionada].niveis);
    lcd.setCursor(0, 1);
    lcd.print("Prestem atencao!");
    delay(1000);

    tocarSequencia(nivelAtual);

    if(!verificarResposta(nivelAtual)) {
      lcd.clear();
      lcd.print("Voce errou!");
      piscarLed(LED_VERMELHO, 3);
      delay(1000);
      menuSelecaoMusica();
      return;
    }
    
    lcd.clear();
    lcd.print("Correto!");
    piscarLed(LED_VERDE, 3);
    nivelAtual++;
    delay(1000);
  }
  
  lcd.clear();
  lcd.print("Parabens, voce");
  lcd.setCursor(0, 1);
  lcd.print("venceu!");
  piscarLed(LED_VERDE, 5);
  delay(3000);
  menuSelecaoMusica();
}

void tocarSequencia(int tamanho) {
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

