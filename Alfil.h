#ifndef AJEDREZ_ALFIL_H
#define AJEDREZ_ALFIL_H

#include "Pieza.h"
#include "Tablero.h"

class Alfil : public Pieza {
public:
    // Constructor: recibe color, símbolo y posición inicial
    Alfil(char color, int fila, int col);

    // Destructor
    ~Alfil();

    // Implementación del movimiento válido
    bool movimientoValido(Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_ALFIL_H
