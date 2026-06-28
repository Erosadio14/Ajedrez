#include "Torre.h"

// Constructor: el símbolo de la torre siempre es 'T'
Torre::Torre(char color, int fila, int col)
    : Pieza(color, 'T', fila, col) {
}

Torre::~Torre() {
}

// Movimiento válido: recto (horizontal o vertical) y camino libre
bool Torre::movimientoValido(Tablero& tab, int fd, int cd) const {
    // Debe moverse en la misma fila o columna
    if (fila != fd && col != cd) return false;

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
