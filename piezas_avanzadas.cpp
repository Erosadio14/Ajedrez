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

// Intento del enroque

bool intentarEnroque(char tab[8][8], char color, bool corto) {

    if (color == 'B') {

        // Verificar que el rey blanco no se ha movido
        if (reyBlancoMovido) return false;

        // Verificar que el rey sigue en su lugar
        if (tab[0][4] != REY_B) return false;

        if (corto) {
            // Verificar que la torre H no se ha movido
            if (torreBlancoH_Mov) return false;

            // Verificar que la torre H sigue en su lugar
            if (tab[0][7] != TORRE_B) return false;

            // Verificar que las casillas F1 y G1 estan vacias
            if (!caminoLibreRecto(tab, 0, 4, 0, 7)) return false;

            // Enroque valido: mover rey y torre
            tab[0][6] = REY_B;
            tab[0][4] = VACIA;
            tab[0][5] = TORRE_B;
            tab[0][7] = VACIA;

            // Actualizar flags
            reyBlancoMovido  = true;
            torreBlancoH_Mov = true;

            return true;
        }
        else {
            // Verificar que la torre A no se ha movido
            if (torreBlancoA_Mov) return false;

            // Verificar que la torre A sigue en su lugar
            if (tab[0][0] != TORRE_B) return false;

            // Verificar que las casillas B1, C1 y D1 estan vacias
            if (!caminoLibreRecto(tab, 0, 4, 0, 0)) return false;

            // Enroque valido: mover rey y torre
            tab[0][2] = REY_B;
            tab[0][4] = VACIA;
            tab[0][3] = TORRE_B;
            tab[0][0] = VACIA;

            // Actualizar flags
            reyBlancoMovido  = true;
            torreBlancoA_Mov = true;

            return true;
        }
    }
    else {

        // Verificar que el rey negro no se ha movido
        if (reyNegroMovido) return false;

        // Verificar que el rey sigue en su lugar
        if (tab[7][4] != REY_N) return false;

        if (corto) {
            // Verificar que la torre H no se ha movido
            if (torreNegroH_Mov) return false;

            // Verificar que la torre H sigue en su lugar
            if (tab[7][7] != TORRE_N) return false;

            // Verificar que las casillas F8 y G8 estan vacias
            if (!caminoLibreRecto(tab, 7, 4, 7, 7)) return false;

            // Enroque valido: mover rey y torre
            tab[7][6] = REY_N;
            tab[7][4] = VACIA;
            tab[7][5] = TORRE_N;
            tab[7][7] = VACIA;

            // Actualizar flags
            reyNegroMovido  = true;
            torreNegroH_Mov = true;

            return true;
        }
        else {
            // Verificar que la torre A no se ha movido
            if (torreNegroA_Mov) return false;

            // Verificar que la torre A sigue en su lugar
            if (tab[7][0] != TORRE_N) return false;

            // Verificar que las casillas B8, C8 y D8 estan vacias
            if (!caminoLibreRecto(tab, 7, 4, 7, 0)) return false;

            // Enroque valido: mover rey y torre
            tab[7][2] = REY_N;
            tab[7][4] = VACIA;
            tab[7][3] = TORRE_N;
            tab[7][0] = VACIA;

            // Actualizar flags
            reyNegroMovido  = true;
            torreNegroA_Mov = true;

            return true;
        }
    }
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
    return validarTorre(tab, fo, co, fd, cd) || validarAlfil(tab, fo, co, fd, cd);
}

//Coordinador general para evitar llamar a todas las funciones de manera individual en el main

bool esMovimientoValido(char tab[8][8], int fo, int co, int fd, int cd, int turno) {

    // Paso 1: verificar que la casilla origen no este vacia
    if (tab[fo][co] == VACIA) return false;

    // Paso 2: verificar que la pieza sea del color del turno actual
    char pieza = tab[fo][co];

    if (turno == TURNO_BLANCAS && pieza >= 'a' && pieza <= 'z') return false;
    if (turno == TURNO_NEGRAS  && pieza >= 'A' && pieza <= 'Z') return false;

    // Paso 3: delegar al validador correspondiente segun la pieza
    switch(pieza) {

        case REY_B:
        case REY_N:
            return validarRey(tab, fo, co, fd, cd);

        case CABALLO_B:
        case CABALLO_N:
            return validarCaballo(tab, fo, co, fd, cd);

        case DAMA_B:
        case DAMA_N:
            return validarDama(tab, fo, co, fd, cd);

        case TORRE_B:
        case TORRE_N:
            return validarTorre(tab, fo, co, fd, cd);

        case ALFIL_B:
        case ALFIL_N:
            return validarAlfil(tab, fo, co, fd, cd);

        case PEON_B:
        case PEON_N:
            return validarPeon(tab, fo, co, fd, cd, turno);

        default:
            return false;
    }
}
