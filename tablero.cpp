#include <iostream>
#include "tablero.h"
#include "constantes.h"

using namespace std;


void inicializarTablero(char tab[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tab[i][j] = VACIA;
        }
    }
    //PIEZAS BLANCAS
    tab[0][0] = TORRE_B;
    tab[0][1] = CABALLO_B;
    tab[0][2] = ALFIL_B;
    tab[0][3] = DAMA_B;
    tab[0][4] = REY_B;
    tab[0][5] = ALFIL_B;
    tab[0][6] = CABALLO_B;
    tab[0][7] = TORRE_B;

    for(int j = 0; j < 8; j++) {

        tab[1][j] = PEON_B;
    }

    //PIEZAS NEGRAS
    tab[7][0] = TORRE_N;
    tab[7][1] = CABALLO_N;
    tab[7][2] = ALFIL_N;
    tab[7][3] = DAMA_N;
    tab[7][4] = REY_N;
    tab[7][5] = ALFIL_N;
    tab[7][6] = CABALLO_N;
    tab[7][7] = TORRE_N;

    for(int j = 0; j < 8; j++) {

        tab[6][j] = PEON_N;
    }

}

void imprimirTablero(char tab[8][8]) {
    cout << endl;

    cout << "    A   B   C   D   E   F   G   H" << endl;

    for(int i = 7; i >= 0; i--) {

        cout << " " << i + 1 << " ";

        for(int j = 0; j < 8; j++) {

            char pieza = tab[i][j];

            switch(pieza) {

                // Blancas

                case PEON_B:
                    cout << "[PB]";
                    break;

                case TORRE_B:
                    cout << "[TB]";
                    break;

                case CABALLO_B:
                    cout << "[CB]";
                    break;

                case ALFIL_B:
                    cout << "[AB]";
                    break;

                case DAMA_B:
                    cout << "[DB]";
                    break;

                case REY_B:
                    cout << "[RB]";
                    break;

                // Negras

                case PEON_N:
                    cout << "[PN]";
                    break;

                case TORRE_N:
                    cout << "[TN]";
                    break;

                case CABALLO_N:
                    cout << "[CN]";
                    break;

                case ALFIL_N:
                    cout << "[AN]";
                    break;

                case DAMA_N:
                    cout << "[DN]";
                    break;

                case REY_N:
                    cout << "[RN]";
                    break;



                default:
                    cout << "[  ]";
            }
        }

        cout << endl;
    }

    cout << endl;
}