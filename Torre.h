#ifndef AJEDREZ_TORRE_H
#define AJEDREZ_TORRE_H

#include "Pieza.h"
#include "Tablero.h"

class Torre : public Pieza {
public:
    // Constructor: recibe color y posición inicial
    Torre(char color, int fila, int col);

    // Destructor
    ~Torre();

    Pieza* clonar() const override;

    // Implementación del movimiento válido
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_TORRE_H
