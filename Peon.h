#ifndef PEON_H
#define PEON_H

#include "Pieza.h"
#include "Tablero.h"

class Peon : public Pieza {
public:

    Peon(char color, int fila, int col);

    // Destructor
    virtual ~Peon();

    Pieza* clonar() const override;

    // Validación del movimiento: maneja avance simple, doble y capturas
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // PEON_H