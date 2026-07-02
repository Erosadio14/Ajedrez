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
    // Saber si el movimiento es diagonal.
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    // Descartar movimientos rectos o inválidos
    if (df != dc) return false;

    // Verificar camino libre (no salta piezas)
    int pasoFila = (fd > fila) ? 1 : -1;
    int pasoCol  = (cd > col) ? 1 : -1;

    int f = fila + pasoFila;
    int c = col + pasoCol;
    // Impedir que el alfil “salte” piezas
    while (f != fd && c != cd) {
        if (tab.getPieza(f, c) != nullptr) {
            return false; // hay una pieza bloqueando
        }
        f += pasoFila;
        c += pasoCol;
    }

    // Última casilla: puede estar vacía o tener pieza enemiga
    Pieza* destino = tab.getPieza(fd, cd);
    if (destino == nullptr || destino->getColor() != color) {
        return true;
    }

    return false;
}
