#include <Servo.h>

// =====================================================
// 1. DEFINIÇÃO DOS SERVOS E PINOS
// =====================================================

Servo base;
Servo ombro;
Servo cotovelo;
Servo garra;

const int PINO_BASE = 5;
const int PINO_OMBRO = 6;
const int PINO_COTOVELO = 3;
const int PINO_GARRA = 4;


// =====================================================
// 2. POSIÇÕES ATUAIS DOS SERVOS
// =====================================================

// Considera que os servos começam na posição de 90 graus.
// Ajuste esses valores caso o braço comece em outra posição.

int posBase = 90;
int posOmbro = 90;
int posCotovelo = 90;
int posGarra = 90;


// =====================================================
// 3. CONFIGURAÇÃO DOS MOVIMENTOS
// =====================================================

const int PASSO = 1;
const int TEMPO_PASSO = 12;
const int TEMPO_ENTRE_COMANDOS = 200;


// =====================================================
// 4. FUNÇÃO DE MOVIMENTO SUAVE
// =====================================================

void moverSuave(Servo &motor, int &posicaoAtual, int destino) {

  if (destino > posicaoAtual) {

    for (int angulo = posicaoAtual; angulo <= destino; angulo += PASSO) {
      motor.write(angulo);
      delay(TEMPO_PASSO);
    }

  } else {

    for (int angulo = posicaoAtual; angulo >= destino; angulo -= PASSO) {
      motor.write(angulo);
      delay(TEMPO_PASSO);
    }
  }

  motor.write(destino);
  posicaoAtual = destino;

  delay(TEMPO_ENTRE_COMANDOS);
}

// =====================================================
// 5. IDENTIFICAÇÃO DOS MOTORES
// =====================================================

// B = Base (0)
// O = Ombro (1)
// C = Cotovelo (2)
// G = Garra (3)


// =====================================================
// 6. SEQUÊNCIAS DE MOVIMENTO DAS HASTES
// =====================================================

// HASTE AB

int HASTE_AB[][2] = {
  {0, 15},
  {2, 60},
  {1, 10},
  {2, 120},
  {3, 180},
  {2, 60},
  {1, 90},
  {0, 82},
  {2, 105},
  {1, 35},
  {3, 110}
};


// HASTE AC

int HASTE_AC[][2] = {
  {1, 90},
  {2, 60},
  {0, 15},
  {1, 0},
  {2, 50},
  {1, 0},
  {2, 165},
  {3, 180},
  {2, 60},
  {1, 90},
  {0, 175},
  {2, 70},
  {1, 45},
  {3, 110}
};


// HASTE BC

int HASTE_BC[][2] = {
  {0, 82},
  {1, 0},
  {2, 170},
  {3, 180},
  {2, 30},
  {1, 80},
  {2, 30},
  {0, 175},
  {2, 70},
  {1, 45},
  {3, 110}
};


// =====================================================
// 7. EXECUÇÃO DOS COMANDOS
// =====================================================

void executarComando(int motor, int angulo) {

  switch (motor) {

    case 0:
      moverSuave(base, posBase, angulo);
      break;

    case 1:
      moverSuave(ombro, posOmbro, angulo);
      break;

    case 2:
      moverSuave(cotovelo, posCotovelo, angulo);
      break;

    case 3:
      moverSuave(garra, posGarra, angulo);
      break;
  }
}


void executarSequencia(int sequencia[][2], int tamanho) {

  for (int i = 0; i < tamanho; i++) {
    executarComando(sequencia[i][0], sequencia[i][1]);
  }
}


void moverHasteAB() {
  executarSequencia(HASTE_AB, sizeof(HASTE_AB) / sizeof(HASTE_AB[0]));
}


void moverHasteAC() {
  executarSequencia(HASTE_AC, sizeof(HASTE_AC) / sizeof(HASTE_AC[0]));
}


void moverHasteBC() {
  executarSequencia(HASTE_BC, sizeof(HASTE_BC) / sizeof(HASTE_BC[0]));
}


// =====================================================
// 8. MOVIMENTAÇÃO DOS DISCOS
// =====================================================

void moverDisco(int origem, int destino) {

  if (origem == 0 && destino == 1) {
    moverHasteAB();
  }

  else if (origem == 0 && destino == 2) {
    moverHasteAC();
  }

  else if (origem == 1 && destino == 2) {
    moverHasteBC();
  }
}


// =====================================================
// 9. ALGORITMO RECURSIVO DE TORRE DE HANÓI
// =====================================================

void resolverHanoi(int discos, int origem, int auxiliar, int destino) {

  if (discos == 1) {
    moverDisco(origem, destino);
    return;
  }

  resolverHanoi(discos - 1, origem, destino, auxiliar);

  moverDisco(origem, destino);

  resolverHanoi(discos - 1, auxiliar, origem, destino);
}


// =====================================================
// 10. CONFIGURAÇÃO INICIAL E LOOP
// =====================================================

void setup() {

  base.attach(PINO_BASE);
  ombro.attach(PINO_OMBRO);
  cotovelo.attach(PINO_COTOVELO);
  garra.attach(PINO_GARRA);

  // Posição inicial considerada para os quatro servos
  base.write(posBase);
  ombro.write(posOmbro);
  cotovelo.write(posCotovelo);
  garra.write(posGarra);

  delay(1500);

  // Resolver Torre de Hanói com dois discos
  resolverHanoi(2, 0, 1, 2);
}


void loop() {

}