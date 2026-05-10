// utilidades.cpp
#include <iostream>
#include "utilidades.h"
#include "constantes.h"

bool esCasillaBlanca(int fila, int col) {
    return (fila + col) % 2 == 0;
}

bool esCasillaNegra(int fila, int col) {
    return !esCasillaBlanca(fila, col);
}

void lexCasilla(const char* casilla, int* fila, int* col) {
    *col = casilla[0] - 'A';          // A-H → 0-7
    *fila = 8 - (casilla[1] - '0');   // 1-8 → 7-0
}

void moverPieza(char tablero[8][8], int f1, int c1, int f2, int c2) {
    tablero[f2][c2] = tablero[f1][c1];
    tablero[f1][c1] = VACIA;
}

bool validarRango(int fila, int col) {
    return fila >= 0 && fila < 8 && col >= 0 && col < 8;
}

void mensajeError(const char* texto) {
    std::cout << "Error: " << texto << std::endl;
}