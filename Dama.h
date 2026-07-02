// Proteger contra errores de “definición múltiple”
#ifndef AJEDREZ_DAMA_H
#define AJEDREZ_DAMA_H
// Permitir que la dama use esas clases
#include "Pieza.h"
#include "Tablero.h"

class Dama : public Pieza {
public:
    // Constructor: recibe color y posición inicial
    Dama(char color, int fila, int col);

    // Destructor
    ~Dama();

    // Definir cómo se mueve la dama en ajedrez
    bool movimientoValido(Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_DAMA_H
