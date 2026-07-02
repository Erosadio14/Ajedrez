//Proteger contra errores de duplicación.
#ifndef AJEDREZ_TORRE_H
#define AJEDREZ_TORRE_H
//Permitir que la torre use esas clases
#include "Pieza.h"
#include "Tablero.h"

class Torre : public Pieza {
public:
    // Constructor: recibe color y posición inicial
    Torre(char color, int fila, int col);

    // Destructor
    ~Torre();

    // Implementación del movimiento válido
    bool movimientoValido(Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_TORRE_H
