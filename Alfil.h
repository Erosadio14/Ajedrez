// Proteger contra errores de duplicación
#ifndef AJEDREZ_ALFIL_H
#define AJEDREZ_ALFIL_H
//Permitir que alfil use esas clases
#include "Pieza.h"
#include "Tablero.h"

class Alfil : public Pieza {
public:
    // Constructor: recibe color, símbolo y posición inicial
    Alfil(char color, int fila, int col);

    Pieza* clonar() const override;

    // Destructor
    ~Alfil();

    // Implementación del movimiento válido
    bool movimientoValido(const Tablero& tab, int fd, int cd) const override;
};

#endif // AJEDREZ_ALFIL_H
