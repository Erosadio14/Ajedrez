#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>
using namespace std;

// Colores
const int BLANCAS = 0;
const int NEGRAS  = 1;

// Turnos
const int TURNO_BLANCAS = 0;
const int TURNO_NEGRAS  = 1;

// Limites del tablero
const int TAM_TABLERO = 8;

// Reglas especiales
const int MAX_MOVIMIENTOS_SIN_CAPTURA = 50;
const int MAX_REPETICIONES            = 3;
const int MAX_HISTORIAL               = 200;

// piezas
const char PEON_B    = 'P';
const char TORRE_B   = 'T';
const char CABALLO_B = 'C';
const char ALFIL_B   = 'A';
const char DAMA_B    = 'D';
const char REY_B     = 'R';

const char PEON_N    = 'p';
const char TORRE_N   = 't';
const char CABALLO_N = 'c';
const char ALFIL_N   = 'a';
const char DAMA_N    = 'd';
const char REY_N     = 'r';

// Archivo de persistencia
const char ARCHIVO_PARTIDA[] = "partida.txt";

#endif