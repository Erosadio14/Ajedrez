#include "Alfil.h"
#include <cmath>

// Constructor: el símbolo del alfil siempre es 'A'
Alfil::Alfil(char color, int fila, int col)
    : Pieza(color, 'A', fila, col) {
}

Alfil::~Alfil() {
}

// Movimiento válido: diagonal y camino libre
bool Alfil::movimientoValido(Tablero& tab, int fd, int cd) const {
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    // Debe moverse en diagonal
    if (df != dc) return false;

    int pasoFila = (fd > fila) ? 1 : -1;
    int pasoCol  = (cd > col) ? 1 : -1;

    int f = fila + pasoFila;
    int c = col + pasoCol;

    while (f != fd && c != cd) {
        if (tab.getPieza(f, c) != nullptr) {
            return false;
        }
        f += pasoFila;
        c += pasoCol;
    }

    Pieza* destino = tab.getPieza(fd, cd);
    if (destino == nullptr || destino->getColor() != color) {
        return true;
    }

    return false;
}
