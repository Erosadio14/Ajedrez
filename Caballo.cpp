#include "Caballo.h"
#include <cmath>

// Constructor: el símbolo del caballo siempre es 'C'
Caballo::Caballo(char color, int fila, int col)
    : Pieza(color, 'C', fila, col) {
}

Caballo::~Caballo() {
}

Pieza* Caballo::clonar() const {
    return new Caballo(color, fila, col);
}

// Movimiento válido: en L (2+1 o 1+2)
bool Caballo::movimientoValido(const Tablero& tab, int fd, int cd) const {
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    // Movimiento en L
    if (!((df == 2 && dc == 1) || (df == 1 && dc == 2))) {
        return false;
    }

    // Casilla destino: vacía o pieza enemiga
    Pieza* destino = tab.getPieza(fd, cd);
    if (destino == nullptr || destino->getColor() != color) {
        return true;
    }

    return false;
}
