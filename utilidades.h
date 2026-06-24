#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

// Parseo de casillas
void lexCasilla(const char* casilla, int* fila, int* col);
bool parsearCasilla(const string& entrada, int& fila, int& col);

// Validacion de rango
bool validarRango(int fila, int col);

// Color de casilla (para imprimir tablero)
bool esCasillaBlanca(int fila, int col);
bool esCasillaNegra(int fila, int col);

// Mensajes
void mensajeError(const char* texto);
void mensajeInvalido(const char* motivo);

// Conversion de coordenadas a string (ej: fila=0, col=4 -> "E1")
string coordAString(int fila, int col);

#endif