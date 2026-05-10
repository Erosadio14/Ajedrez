#include  <iostream>
#include "piezas_avanzadas.h"
#include "constantes.h"
#include "utilidades.h"
#include "piezas_basicas.h"
#include <cmath>

using namespace std;

// Validacion del Rey
bool validarRey(char tab[8][8],int fo, int co, int fd, int cd) {

    int difFila = fd -fo;
    int difCol = cd -co;

    // Verificacion de que el rey solo se ha movido 1 casilla de x dirección
    if (difFila < -1 || difFila > 1) return false;
    if (difCol < -1 || difCol > 1) return false;
    if (difFila == 0 && difCol == 0) return false;

    // Verificacion de que no hay piezas amigas en el destino
    char origen = tab[fo][co];
    char destino = tab[fd][cd];

    if (destino == VACIA) return true; // Si no existen piezas es valido

    // Si ambas piezas son mayusculas son del mismo equipo blanco
    if (origen >= 'A' && origen <= 'Z' && destino >= 'A' && destino <= 'Z') return false;

    // si ambas piezas son minusculas son del mismo equipo negras
    if (origen >= 'a' && origen <= 'z' && destino >= 'a' && destino <= 'z') return false;

    return true; //destino tiene pieza rival es captura valida
}

//validacion del caballo
bool validarCaballo(char tab[8][8], int fo, int co, int fd, int cd) {

    int diFila = abs(fd - fo);
    int diCol = abs(cd - co);

    // Verificacion de movimiento en L
    bool esL = (diFila == 2 && diCol == 1) || (diFila == 1 && diCol == 2);
    if (!esL) return false;

    // Verificacion de que no hay piezas amigas en el destino
    char origen = tab[fo][co];
    char destino = tab[fd][cd];

    if (destino == VACIA) return true; // Si no existen piezas es valido

    // Si ambas piezas son mayusculas son del mismo equipo blanco
    if (origen >= 'A' && origen <= 'Z' && destino >= 'A' && destino <= 'Z') return false;

    // si ambas piezas son minusculas son del mismo equipo negras
    if (origen >= 'a' && origen <= 'z' && destino >= 'a' && destino <= 'z') return false;

    return true;
}

//validacion de la dama

bool validarDama(char tab[8][8], int fo, int co, int fd, int cd) {

    //codigo

    return false;
}
