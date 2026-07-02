#include "Rey.h"
#include <cmath>

Rey::Rey(char color, int fila, int col)
    : Pieza(color, 'R', fila, col) {
}

//  DESTRUCTOR
Rey::~Rey() {
}

Pieza* Rey::clonar() const {
    return new Rey(color, fila, col);
}

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