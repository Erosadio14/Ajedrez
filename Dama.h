#ifndef AJEDREZ_DAMA_H
#define AJEDREZ_DAMA_H

#include "Pieza.h"
#include "Tablero.h"

class Dama : public Pieza {
public:
    // Constructor: recibe color y posición inicial
    Dama(char color, int fila, int col);

    Pieza* clonar() const override;


    // Destructor
    ~Dama();

    // Implementación del movimiento válido
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_DAMA_H
