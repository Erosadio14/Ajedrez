#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

// Parseo de casillas
void lexCasilla(const char* casilla, int* fila, int* col);

// Convierte entrada del jugador a coordenadas internas (ej: "E2" -> fila=1, col=4)
bool parsearCasilla(const string& entrada, int& fila, int& col);

// Validacion de rango
bool validarRango(int fila, int col);

// Color de casilla (para imprimir tablero)
bool esCasillaBlanca(int fila, int col);
bool esCasillaNegra(int fila, int col);

// Mensajes
void mensajeError(const char* texto);
void mensajeInvalido(const char* motivo);

// Convierte coordenadas internas a string legible (ej: (1,4) -> "E2")
string coordAString(int fila, int col);

#endif