#ifndef AJEDREZ_PIEZAS_BASICAS_H
#define AJEDREZ_PIEZAS_BASICAS_H

#include "constantes.h"

// Peón
bool validarPeon(char tablero[8][8], int fo, int co, int fd, int cd, int turno);
void coronarPeon(char tablero[8][8], int fila, int col);

// Torre
bool validarTorre(char tablero[8][8], int fo, int co, int fd, int cd);

// Alfil
bool validarAlfil(char tablero[8][8], int fo, int co, int fd, int cd);

#endif //AJEDREZ_PIEZAS_BASICAS_H holaadjfoefef
