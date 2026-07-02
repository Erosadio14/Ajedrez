#include "Peon.h"
#include <cmath>

//  CONSTRUCTOR
Peon::Peon(char color, int fila, int col)
    : Pieza(color, 'P', fila, col) {
}

//  Destructor
Peon::~Peon() {
}

Pieza* Peon::clonar() const {
    return new Peon(color, fila, col);
}

//  Validar Movimiento

bool Peon::movimientoValido(const Tablero& tab, int fd, int cd) const {

    int direccion = (color == 'B') ? 1 : -1;
    int filaInicial = (color == 'B') ? 1 : 6;

    int df = fd - fila;
    int dc = abs(cd - col);

    if (df == 0 && dc == 0) return false;

    // A: Movimiento vertical hacia adelante (Misma columna: dc == 0)
    if (dc == 0) {
        if (df == direccion) {
            return tab.getPieza(fd, cd) == nullptr;
        }

        // Avance doble (2 casillas - solo desde su fila inicial)
        if (fila == filaInicial && df == 2 * direccion) {
            // Tanto la casilla intermedia como el destino deben estar completamente vacíos
            return tab.getPieza(fila + direccion, col) == nullptr &&
                   tab.getPieza(fd, cd) == nullptr;
        }
    }
    // B: Captura diagonal tradicional (Se mueve 1 columna a los lados y avanza)
    else if (dc == 1 && df == direccion) {
        Pieza* destino = tab.getPieza(fd, cd);

        // Captura normal: hay una pieza en el destino y es del enemigo
        if (destino != nullptr && destino->getColor() != color) {
            return true;
        }

        // C: Captura al paso (En Passant) - Geometría inicial
        int filaEnPassant = (color == 'B') ? 4 : 3;
        if (fila == filaEnPassant && destino == nullptr) {
            // El peón enemigo capturado debe estar justo a nuestro lado (misma fila, columna destino)
            Pieza* adyacente = tab.getPieza(fila, cd);
            if (adyacente != nullptr && adyacente->getSimbolo() == 'P' && adyacente->getColor() != color) {
                return true;
            }
        }
    }

    return false;
}