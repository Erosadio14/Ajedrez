#ifndef AJEDREZ_CABALLO_H
#define AJEDREZ_CABALLO_H

#include "Pieza.h"
#include "Tablero.h"

class Caballo : public Pieza {
public:
    // Constructor: recibe color y posición inicial
    Caballo(char color, int fila, int col);

    // Destructor
    ~Caballo();

    // Implementación del movimiento válido
    bool movimientoValido(Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_CABALLO_H
