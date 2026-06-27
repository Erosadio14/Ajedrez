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

// ============================================================
//  GET SIMBOLO 2 LETRAS
//  Construye la representacion visual de la pieza
//  combinando su simbolo y su color
//  Ejemplo: simbolo='P', color='B' → "PB"
//           simbolo='T', color='N' → "TN"
//  Las subclases pueden sobreescribir este metodo
//  si necesitan una representacion diferente
// ============================================================
string Pieza::getSimbolo2L() const {
    string resultado = "";
    resultado += simbolo;           // primera letra: tipo de pieza
    resultado += color;             // segunda letra: color ('B' o 'N')
    return resultado;
}

// ============================================================
//  SET POSICION
//  El tablero llama este metodo cada vez que mueve
//  la pieza para mantener fila y col sincronizados
//  con la posicion real en la matriz del tablero
// ============================================================
void Pieza::setPosicion(int nuevaFila, int nuevaCol) {
    fila = nuevaFila;
    col  = nuevaCol;
}

// ============================================================
//  OPERATOR
//  Imprime la pieza en su formato visual de 4 caracteres
//  Ejemplo: [PB], [TN], [  ]
//  Se usa tanto para imprimir piezas individuales
//  como dentro de imprimirTablero
// ============================================================
ostream& operator<<(ostream& os, const Pieza& p) {
    os << "[" << p.getSimbolo2L() << "]";
    return os;
}