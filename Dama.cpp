#include "Dama.h"
#include <cmath>

// Constructor: el símbolo de la dama siempre es 'D'
Dama::Dama(char color, int fila, int col)
    : Pieza(color, 'D', fila, col) {
}

Dama::~Dama() {
}

// Movimiento válido: combina torre (líneas rectas) y alfil (diagonales)
bool Dama::movimientoValido(Tablero& tab, int fd, int cd) const {
    int df = abs(fd - fila);
    int dc = abs(cd - col);

    // Verificar si es movimiento de torre o alfil
    bool esDiagonal = (df == dc);
    bool esRecto = (fila == fd || col == cd);

    if (!esDiagonal && !esRecto) return false;

    // Calcular pasos según dirección
    int pasoFila = (fd > fila) ? 1 : (fd < fila ? -1 : 0);
    int pasoCol  = (cd > col) ? 1 : (cd < col ? -1 : 0);

    int f = fila + pasoFila;
    int c = col + pasoCol;

    // Recorrer camino hasta destino
    while (f != fd || c != cd) {
        if (tab.getPieza(f, c) != nullptr) {
            return false; // hay una pieza bloqueando
        }
        f += pasoFila;
        c += pasoCol;
    }

    // Última casilla: vacía o pieza enemiga
    Pieza* destino = tab.getPieza(fd, cd);
    if (destino == nullptr || destino->getColor() != color) {
        return true;
    }

    return false;
}
