#include "Pieza.h"
#include <string>
using namespace std;

//  CONSTRUCTOR
Pieza::Pieza(char color, char simbolo, int fila, int col)
    : color(color), simbolo(simbolo), fila(fila), col(col) {
}

//  DESTRUCTOR VIRTUAL
Pieza::~Pieza() {
}

//  GETTERS
char Pieza::getColor() const {
    return color;
}

char Pieza::getSimbolo() const {
    return simbolo;
}

int Pieza::getFila() const {
    return fila;
}

int Pieza::getCol() const {
    return col;
}

//  HELPERS DE COLOR
bool Pieza::esBlanca() const {
    return color == 'B';
}

bool Pieza::esNegra() const {
    return color == 'N';
}

string Pieza::getSimbolo2L() const {
    string resultado = "";
    resultado += simbolo;
    resultado += color;
    return resultado;
}

void Pieza::setPosicion(int nuevaFila, int nuevaCol) {
    fila = nuevaFila;
    col  = nuevaCol;
}

ostream& operator<<(ostream& os, const Pieza& p) {
    os << "[" << p.getSimbolo2L() << "]";
    return os;
}