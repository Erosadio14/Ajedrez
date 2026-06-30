#include <iostream>
#include <cctype>
#include "utilidades.h"
#include "constantes.h"

using namespace std;

bool esCasillaBlanca(int fila, int col) {
    return (fila + col) % 2 == 0;
}

bool esCasillaNegra(int fila, int col) {
    return !esCasillaBlanca(fila, col);
}

void lexCasilla(const char* casilla, int* fila, int* col) {
    *col  = casilla[0] - 'A';
    *fila = casilla[1] - '1';
}

bool parsearCasilla(const string& entrada, int& fila, int& col) {
    if (entrada.size() < 2) return false;

    char columna = toupper((unsigned char)entrada[0]);
    char filaCar = entrada[1];

    if (columna < 'A' || columna > 'H') return false;
    if (filaCar  < '1' || filaCar  > '8') return false;

    col  = columna - 'A';   // 'A'→0, 'H'→7
    fila = filaCar  - '1';  // '1'→0, '8'→7

    return true;
}

bool validarRango(int fila, int col) {
    return fila >= 0 && fila < TAM_TABLERO &&
           col  >= 0 && col  < TAM_TABLERO;
}

void mensajeError(const char* texto) {
    cout << "Error: " << texto << endl;
}

void mensajeInvalido(const char* motivo) {
    cout << "\n***** Movimiento NO VALIDO : " << motivo << " *****\n" << endl;
}

string coordAString(int fila, int col) {
    string resultado = "";
    resultado += (char)('A' + col);   // col 0→'A', col 4→'E'
    resultado += (char)('1' + fila);  // fila 0→'1', fila 6→'7'
    return resultado;
}