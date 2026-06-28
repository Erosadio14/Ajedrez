#include "Peon.h"
#include <cmath>

//  CONSTRUCTOR
Peon::Peon(char color, int fila, int col)
    : Pieza(color, 'P', fila, col) {
}

//  DESTRUCTOR
Peon::~Peon() {
}

//  CLONAR

Pieza* Peon::clonar() const {
    return new Peon(color, fila, col);
}

//  MOVIMIENTO VÁLIDO

bool Peon::movimientoValido(const Tablero& tab, int fd, int cd) const {
    // 1. Determinar el sentido de avance según el color
    // Blancas (B): suben -> dirección +1, fila inicial es la 1
    // Negras (N): bajan -> dirección -1, fila inicial es la 6
    int direccion = (color == 'B') ? 1 : -1;
    int filaInicial = (color == 'B') ? 1 : 6;

    int df = fd - fila;
    int dc = abs(cd - col);

    // No es válido quedarse en el mismo lugar
    if (df == 0 && dc == 0) return false;

    // ========================================================
    // CASO A: Movimiento vertical hacia adelante (Misma columna: dc == 0)
    // ========================================================
    if (dc == 0) {
        // Avance simple (1 casilla)
        if (df == direccion) {
            return tab.getPieza(fd, cd) == nullptr; // Solo si el destino está vacío
        }

        // Avance doble (2 casillas - solo desde su fila inicial)
        if (fila == filaInicial && df == 2 * direccion) {
            // Tanto la casilla intermedia como el destino deben estar completamente vacíos
            return tab.getPieza(fila + direccion, col) == nullptr &&
                   tab.getPieza(fd, cd) == nullptr;
        }
    }
    // ========================================================
    // CASO B: Captura diagonal tradicional (Se mueve 1 columna a los lados y avanza)
    // ========================================================
    else if (dc == 1 && df == direccion) {
        Pieza* destino = tab.getPieza(fd, cd);

        // Captura normal: hay una pieza en el destino y es del enemigo
        if (destino != nullptr && destino->getColor() != color) {
            return true;
        }

        // ====================================================
        // CASO C: Captura al paso (En Passant) - Geometría inicial
        // ====================================================
        // Un peón blanco solo puede hacer "al paso" si está en la fila 4.
        // Un peón negro solo puede hacerlo si está en la fila 3.
        int filaEnPassant = (color == 'B') ? 4 : 3;
        if (fila == filaEnPassant && destino == nullptr) {
            // El peón enemigo capturado debe estar justo a nuestro lado (misma fila, columna destino)
            Pieza* adyacente = tab.getPieza(fila, cd);
            if (adyacente != nullptr && adyacente->getSimbolo() == 'P' && adyacente->getColor() != color) {
                // Nota: La geometría es correcta, pero para ser 100% legal bajo las normas oficiales,
                // este peón enemigo debe haberse movido un paso doble en el TURNO INMEDIATAMENTE ANTERIOR.
                // Como esta función es 'const' y no tiene historial, aceptamos la geometría aquí
                // y el filtro estricto por turno se procesa en el controlador del juego (Partida).
                return true;
            }
        }
    }

    return false;
}