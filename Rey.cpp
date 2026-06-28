#include "Rey.h"
#include <cmath>

// ============================================================
//  CONSTRUCTOR
//  El símbolo del Rey siempre se inicializa como 'R'
// ============================================================
Rey::Rey(char color, int fila, int col)
    : Pieza(color, 'R', fila, col) {
}

//  DESTRUCTOR
Rey::~Rey() {
}

// ============================================================
//  CLONAR
//  Crea una copia idéntica del Rey en su posición actual.
//  Esencial para las simulaciones de jaque en el tablero.
// ============================================================
Pieza* Rey::clonar() const {
    return new Rey(color, fila, col);
}

// ============================================================
//  MOVIMIENTO VÁLIDO
//  Verifica la geometría del movimiento del Rey:
//  Máximo 1 casilla de distancia en cualquier dirección.
// ============================================================
bool Rey::movimientoValido(const Tablero& tab, int fd, int cd) const {
    // Calcular el diferencial de pasos en filas y columnas
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    // No es válido moverse a la misma casilla actual
    if (df == 0 && dc == 0) return false;

    // El rey solo puede avanzar una casilla (horizontal, vertical o diagonal)
    if (df > 1 || dc > 1) return false;

    // Verificar la casilla de destino en el tablero
    Pieza* destino = tab.getPieza(fd, cd);

    // El movimiento es geométricamente válido si la casilla está vacía
    // o si contiene una pieza del color enemigo para capturarla
    if (destino == nullptr || destino->getColor() != color) {
        return true;
    }

    return false;
}