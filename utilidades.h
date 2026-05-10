#ifndef AJEDREZ_UTILIDADES_H
#define AJEDREZ_UTILIDADES_H

void lexCasilla(const char* casilla, int* fila, int* col);
void moverPieza(char tablero[8][8], int f1, int c1, int f2, int c2);
bool esCasillaBlanca(int fila, int col);
bool esCasillaNegra(int fila, int col);
bool validarRango(int fila, int col);
void mensajeError(const char* texto);

#endif //AJEDREZ_UTILIDADES_H
