#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include "Pieza.h" // Depende únicamente de la abstracción base

class Tablero {
private:
    Pieza* casillas[8][8]; // Matriz polimórfica de punteros

public:
    // Constructor y Destructor
    Tablero();
    ~Tablero();

    // Ciclo de vida y utilitarios
    void inicializar();
    void limpiar();
    bool mover(int filO, int colO, int filD, int colD);

    // Métodos esenciales: El contrato que usarán las piezas para analizar el entorno
    Pieza* getPieza(int fila, int col) const;
    void setPieza(int fila, int col, Pieza* pieza);

    // Lógica para detectar jaques (usa Tablero& modificable debido a Pieza.h)
    bool estaEnJaque(char color);

    // Clonación segura para simulaciones de jugadas futuras
    Tablero* clonar() const;

    // Sobrecarga de operadores solicitados
    friend std::ostream& operator<<(std::ostream& os, const Tablero& tablero);
    bool operator==(const Tablero& otro) const;
};

#endif // TABLERO_H