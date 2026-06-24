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
    if (entrada.size() != 2) {
        mensajeInvalido("casilla invalida, ingrese columna y fila (ej. E2)");
        return false;
    }
    char buf[4];
    buf[0] = toupper((unsigned char)entrada[0]);
    buf[1] = entrada[1];
    buf[2] = '\0';

    if (buf[0] < 'A' || buf[0] > 'H') {
        mensajeInvalido("casilla invalida, la letra debe ser entre A y H");
        return false;
    }
    if (buf[1] < '1' || buf[1] > '8') {
        mensajeInvalido("casilla invalida, el numero debe ser entre 1 y 8");
        return false;
    }

    lexCasilla(buf, &fila, &col);
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
    string s = "  ";
    s[0] = (char)('A' + col);
    s[1] = (char)('1' + fila);
    return s;
}