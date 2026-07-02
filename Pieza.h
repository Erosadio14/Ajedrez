#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>
using namespace std;

class Tablero;

class Pieza {
protected:
    char color;
    char simbolo;
    int fila;
    int col;

public:
    // Constructor y destructor
    Pieza(char color, char simbolo, int fila, int col);
    virtual ~Pieza();

    // Metodo puro virtual: cada subclase define su movimiento
    virtual bool movimientoValido(const Tablero& tab, int fd, int cd) const = 0;
    virtual Pieza* clonar() const = 0;

    // Getters
    char getColor()   const;
    char getSimbolo() const;
    int  getFila()    const;
    int  getCol()     const;

    // Helpers de color
    bool esBlanca() const;
    bool esNegra()  const;

    // Representacion visual de 2 letras: "PB", "TN", etc.
    // Virtual para que subclases puedan sobreescribirlo si es necesario
    virtual string getSimbolo2L() const;

    // Actualizar posicion cuando la pieza se mueve
    void setPosicion(int nuevaFila, int nuevaCol);

    // Sobrecarga de operator<< para imprimir la pieza
    friend ostream& operator<<(ostream& os, const Pieza& p);
};

#endif // PIEZA_H