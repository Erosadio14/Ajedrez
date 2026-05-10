#include "piezas_basicas.h"
#include "utilidades.h"
#include "constantes.h"
#include <iostream>
#include <cmath>
using namespace std;


// Verifica que no haya piezas bloqueando el camino recto
bool caminoLibreRecto(char tab[8][8], int fo, int co, int fd, int cd) {
    // Movimiento vertical
    if (co == cd) {
        int paso = (fd > fo) ? 1 : -1;
        for (int f = fo + paso; f != fd; f += paso) {
            if (tab[f][co] != VACIA) return false;
        }
    }
    // Movimiento horizontal
    else if (fo == fd) {
        int paso = (cd > co) ? 1 : -1;
        for (int c = co + paso; c != cd; c += paso) {
            if (tab[fo][c] != VACIA) return false;
        }
    }
    return true;
}

// Verifica que no haya piezas bloqueando el camino diagonal
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

// ─────────────────────────────────────────
// PEÓN
// ─────────────────────────────────────────

bool validarPeon(char tab[8][8], int fo, int co, int fd, int cd, int turno) {
    char destino = tab[fd][cd];

    if (turno == TURNO_BLANCAS) {
        // Blancas suben: fila aumenta (índice sube)
        // Avance simple: una casilla adelante, columna igual, destino vacío
        if (cd == co && fd == fo + 1 && destino == VACIA)
            return true;

        // Avance doble: solo desde fila inicial (índice 1 = fila 2 del tablero)
        if (cd == co && fo == 1 && fd == fo + 2
            && tab[fo + 1][co] == VACIA && destino == VACIA)
            return true;

        // Captura diagonal: avanza una fila, una columna a los lados
        // El destino debe ser una pieza negra (minúscula)
        if (fd == fo + 1 && (cd == co + 1 || cd == co - 1)
            && destino != VACIA && esCasillaNegra(fd, cd))
            return true;
    }
    else {
        // Negras bajan: fila disminuye (índice baja)
        // Avance simple
        if (cd == co && fd == fo - 1 && destino == VACIA)
            return true;

        // Avance doble: solo desde fila inicial negras (índice 6 = fila 7)
        if (cd == co && fo == 6 && fd == fo - 2
            && tab[fo - 1][co] == VACIA && destino == VACIA)
            return true;

        // Captura diagonal: destino debe ser pieza blanca (mayúscula)
        if (fd == fo - 1 && (cd == co + 1 || cd == co - 1)
            && destino != VACIA && esCasillaBlanca(fd, cd))
            return true;
    }

    return false;
}

void coronarPeon(char tab[8][8], int fila, int col) {
    int opcion;
    bool esBlanco = (fila == 7); // blancas llegan a índice 7 (fila 8)

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
        default: break; // se queda como peón
    }
}

// ─────────────────────────────────────────
// TORRE
// ─────────────────────────────────────────

bool validarTorre(char tab[8][8], int fo, int co, int fd, int cd) {
    // Solo movimiento recto (misma fila O misma columna)
    if (fo != fd && co != cd) return false;

    // No puede capturar pieza propia
    if (esCasillaBlanca(fo, co) && esCasillaBlanca(fd, cd)) return false;
    if (esCasillaNegra(fo, co)  && esCasillaNegra(fd, cd))  return false;

    // Camino debe estar libre
    return caminoLibreRecto(tab, fo, co, fd, cd);
}

// ─────────────────────────────────────────
// ALFIL
// ─────────────────────────────────────────

bool validarAlfil(char tab[8][8], int fo, int co, int fd, int cd) {
    int dF = abs(fd - fo);
    int dC = abs(cd - co);

    // Solo movimiento diagonal (diferencia filas = diferencia columnas)
    if (dF != dC || dF == 0) return false;

    // No puede capturar pieza propia
    if (esCasillaBlanca(fo, co) && esCasillaBlanca(fd, cd)) return false;
    if (esCasillaNegra(fo, co)  && esCasillaNegra(fd, cd))  return false;

    // Camino diagonal debe estar libre
    return caminoLibreDiag(tab, fo, co, fd, cd);
}