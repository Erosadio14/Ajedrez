#include "piezas_basicas.h"
#include "utilidades.h"
#include "constantes.h"
#include <iostream>
#include <cmath>
using namespace std;


bool caminoLibreRecto(char tab[8][8], int fo, int co, int fd, int cd) {
    if (co == cd) {
        int paso = (fd > fo) ? 1 : -1;
        for (int f = fo + paso; f != fd; f += paso) {
            if (tab[f][co] != VACIA) return false;
        }
    }
    else if (fo == fd) {
        int paso = (cd > co) ? 1 : -1;
        for (int c = co + paso; c != cd; c += paso) {
            if (tab[fo][c] != VACIA) return false;
        }
    }
    return true;
}

bool caminoLibreDiag(char tab[8][8], int fo, int co, int fd, int cd) {
    int pasoF = (fd > fo) ? 1 : -1;
    int pasoC = (cd > co) ? 1 : -1;
    int f = fo + pasoF;
    int c = co + pasoC;
    while (f != fd && c != cd) {
        if (tab[f][c] != VACIA) return false;
        f += pasoF;
        c += pasoC;
    }
    return true;
}

// PEÓN

bool validarPeon(char tab[8][8], int fo, int co, int fd, int cd, int turno) {
    char destino = tab[fd][cd];

    if (turno == TURNO_BLANCAS) {

        if (cd == co && fd == fo + 1 && destino == VACIA)
            return true;

        if (cd == co && fo == 1 && fd == fo + 2
            && tab[fo + 1][co] == VACIA && destino == VACIA)
            return true;

        if (fd == fo + 1 && (cd == co + 1 || cd == co - 1)
            && destino >= 'a' && destino <= 'z')
            return true;
    }
    else {

        if (cd == co && fd == fo - 1 && destino == VACIA)
            return true;

        if (cd == co && fo == 6 && fd == fo - 2
            && tab[fo - 1][co] == VACIA && destino == VACIA)
            return true;

        if (fd == fo - 1 && (cd == co + 1 || cd == co - 1)
            && destino >= 'A' && destino <= 'Z')
            return true;
    }

    return false;
}

void coronarPeon(char tab[8][8], int fila, int col) {
    int opcion;
    bool esBlanco = (fila == 7);

    cout << "\n~~~~~ CORONAR PEON ~~~~~" << endl;
    cout << "Seleccione la nueva pieza:" << endl;
    cout << "0.- Ninguna (Peon)" << endl;
    cout << "1.- Reina" << endl;
    cout << "2.- Torre" << endl;
    cout << "3.- Alfil" << endl;
    cout << "4.- Caballo" << endl;
    cout << "Su eleccion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: tab[fila][col] = esBlanco ? DAMA_B    : DAMA_N;    break;
        case 2: tab[fila][col] = esBlanco ? TORRE_B   : TORRE_N;   break;
        case 3: tab[fila][col] = esBlanco ? ALFIL_B   : ALFIL_N;   break;
        case 4: tab[fila][col] = esBlanco ? CABALLO_B : CABALLO_N; break;
        default: break;
    }
}

// TORRE

bool validarTorre(char tab[8][8], int fo, int co, int fd, int cd) {

    if (fo != fd && co != cd) return false;

    char origen  = tab[fo][co];
    char destino = tab[fd][cd];

    if (destino != VACIA) {
        if (origen >= 'A' && origen <= 'Z' && destino >= 'A' && destino <= 'Z') return false;
        if (origen >= 'a' && origen <= 'z' && destino >= 'a' && destino <= 'z') return false;
    }

    return caminoLibreRecto(tab, fo, co, fd, cd);
}

// ALFIL

bool validarAlfil(char tab[8][8], int fo, int co, int fd, int cd) {
    int dF = abs(fd - fo);
    int dC = abs(cd - co);

    if (dF != dC || dF == 0) return false;

    char origen  = tab[fo][co];
    char destino = tab[fd][cd];

    if (destino != VACIA) {
        if (origen >= 'A' && origen <= 'Z' && destino >= 'A' && destino <= 'Z') return false;
        if (origen >= 'a' && origen <= 'z' && destino >= 'a' && destino <= 'z') return false;
    }

    return caminoLibreDiag(tab, fo, co, fd, cd);
}