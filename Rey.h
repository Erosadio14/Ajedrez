#ifndef REY_H
#define REY_H

#include "Pieza.h"
#include "Tablero.h"

class Rey : public Pieza {
public:
    // Constructor: recibe el color ('B' o 'N') y la posición inicial.
    // El símbolo 'R' se asignará internamente en el constructor (Rey.cpp).
    Rey(char color, int fila, int col);

    // Destructor virtual
    virtual ~Rey();

    // Clonación polimórfica para las simulaciones del tablero
    Pieza* clonar() const override;

    // Validación geométrica: el Rey solo se mueve 1 casilla en cualquier dirección
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // REY_H