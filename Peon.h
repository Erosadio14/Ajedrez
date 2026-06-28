#ifndef PEON_H
#define PEON_H

#include "Pieza.h"
#include "Tablero.h"

class Peon : public Pieza {
public:
    // Constructor: Recibe color ('B' o 'N') y posición inicial.
    // El símbolo 'P' se asigna internamente cumpliendo con la regla de mayúsculas.
    Peon(char color, int fila, int col);

    // Destructor
    virtual ~Peon();

    // Clonación polimórfica para simulaciones del tablero
    Pieza* clonar() const override;

    // Validación del movimiento: maneja avance simple, doble y capturas
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // PEON_H