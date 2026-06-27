#include "Tablero.h"

Tablero::Tablero() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            casillas[i][j] = nullptr;
        }
    }
}

Tablero::~Tablero() {
    limpiar();
}

void Tablero::limpiar() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (casillas[i][j] != nullptr) {
                delete casillas[i][j];
                casillas[i][j] = nullptr;
            }
        }
    }
}

void Tablero::inicializar() {
    limpiar(); 
    // NOTA: Se deja vacía temporalmente para definir el escenario.
}

Pieza* Tablero::getPieza(int fila, int col) const {
    if (fila >= 0 && fila < 8 && col >= 0 && col < 8) {
        return casillas[fila][col];
    }
    return nullptr;
}

void Tablero::setPieza(int fila, int col, Pieza* pieza) {
    if (fila >= 0 && fila < 8 && col >= 0 && col < 8) {
        casillas[fila][col] = pieza;
    }
}

bool Tablero::mover(int filO, int colO, int filD, int colD) {
    if (filO < 0 || filO >= 8 || colO < 0 || colO >= 8 ||
        filD < 0 || filD >= 8 || colD < 0 || colD >= 8) {
        return false;
    }

    Pieza* piezaOrigen = casillas[filO][colO];
    if (piezaOrigen == nullptr) return false;

    if (casillas[filD][colD] != nullptr) {
        delete casillas[filD][colD];
    }

    casillas[filD][colD] = piezaOrigen;
    casillas[filO][colO] = nullptr;
    
    piezaOrigen->setPosicion(filD, colD);
    return true;
}

bool Tablero::estaEnJaque(char color) {
    int filRey = -1, colRey = -1;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Pieza* p = casillas[i][j];
            if (p != nullptr && p->getSimbolo() == 'R' && p->getColor() == color) {
                filRey = i;
                colRey = j;
                break;
            }
        }
        if (filRey != -1) break;
    }

    if (filRey == -1) return false;

    char colorEnemigo = (color == 'B') ? 'N' : 'B';
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Pieza* p = casillas[i][j];
            if (p != nullptr && p->getColor() == colorEnemigo) {
                if (p->movimientoValido(*this, filRey, colRey)) {
                    return true; 
                }
            }
        }
    }
    return false;
}

Tablero* Tablero::clonar() const {
    Tablero* copia = new Tablero();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Temporalmente solo inicializamos la copia como un tablero limpio.
            // se cambiará por: copia->casillas[i][j] = this->casillas[i][j]->clonar();
            copia->casillas[i][j] = nullptr; 
        }
    }
    return copia;
}

std::ostream& operator<<(std::ostream& os, const Tablero& tablero) {
    os << "   a   b   c   d   e   f   g   h\n";
    os << " +---+---+---+---+---+---+---+---+\n";
    for (int i = 0; i < 8; ++i) {
        os << 8 - i << " |"; 
        for (int j = 0; j < 8; ++j) {
            if (tablero.casillas[i][j] == nullptr) {
                os << "   |";
            } else {
                os << " " << tablero.casillas[i][j]->getSimbolo2L() << "|";
            }
        }
        os << " " << 8 - i << "\n";
        os << " +---+---+---+---+---+---+---+---+\n";
    }
    os << "   a   b   c   d   e   f   g   h\n";
    return os;
}

bool Tablero::operator==(const Tablero& otra) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Pieza* p1 = this->casillas[i][j];
            Pieza* p2 = otra.casillas[i][j];

            if ((p1 == nullptr && p2 != nullptr) || (p1 != nullptr && p2 == nullptr)) {
                return false;
            }
            if (p1 != nullptr && p2 != nullptr) {
                if (p1->getSimbolo() != p2->getSimbolo() || p1->getColor() != p2->getColor()) {
                    return false;
                }
            }
        }
    }
    return true;
}