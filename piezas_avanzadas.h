#ifndef AJEDREZ_PIEZAS_AVANZADAS_H
#define AJEDREZ_PIEZAS_AVANZADAS_H
#include "constantes.h"

// Flags necesarios para cumplir enroque
extern bool reyBlancoMovido;
extern bool reyNegroMovido;
extern bool torreBlancoA_Mov;
extern bool torreBlancoH_Mov;
extern bool torreNegroA_Mov;
extern bool torreNegroH_Mov;

// Movimientos de piezas
bool validarRey (char tab[8][8], int fo, int co, int fd, int cd);
bool validarCaballo (char tab[8][8], int fo, int co, int fd, int cd);
bool validarDama (char tab[8][8], int fo, int co, int fd, int cd);

// Intentar enroque
bool intentarEnroquer (char tab[8][8], char color, bool corto);

// Coordinador general
bool esMovimientoValido(char tab[8][8], int fo, int co, int fd, int cd, int turno);


#endif //AJEDREZ_PIEZAS_AVANZADAS_H