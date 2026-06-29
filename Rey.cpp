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
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    if (df == 0 && dc == 0) return false;
    if (df > 1 || dc > 1) return false;

    Pieza* destino = tab.getPieza(fd, cd);
    if (destino != nullptr && destino->getColor() == color) return false;

    // Simular el movimiento en una copia del tablero
    Tablero* copia = tab.clonar();
    copia->mover(fila, col, fd, cd);

    // Verificar si el rey queda en jaque en esa posicion
    bool quedaEnJaque = copia->estaEnJaque(color);
    delete copia;

    return !quedaEnJaque;
}