#include <iostream>
using namespace std;
#include "tablero.h"
#include "constantes.h"
#include "piezas_avanzadas.h"


// Flags para validar el enroque:
bool reyBlancoMovido   = false;
bool reyNegroMovido    = false;
bool torreBlancoA_Mov  = false;
bool torreBlancoH_Mov  = false;
bool torreNegroA_Mov   = false;
bool torreNegroH_Mov   = false;
// fin de los flags

void mostrarInstrucciones() {

    int opcion;

    do {

        cout << "======= INSTRUCCIONES =======" << endl;
        cout << "- Las blancas se mueven primero." << endl;
        cout << "- El juego termina cuando un rey es capturado o un jugador se rinde. hola" << endl;

        cout << endl;
        cout << "1. Volver al menu" << endl;
        cout << "2. Salir del juego" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                break;

            case 2:
                cout << "Gracias por jugar." << endl;
                exit(0);
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                cout << endl;

        }

    } while(opcion != 1);
}
void mostrarIntegrantes() {

    cout << "======== INTEGRANTES ======" << endl;
    cout << "Integrante 1-blancas : " << endl;
    cout << "Integrante 2-blancas : " << endl;
    cout << "Integrante 1-negras : " << endl;
    cout << "Integrante 2-negras : " << endl;

}
void mostrarConsideraciones() {
    cout << "======== CONSIDERACIONES ======" << endl;
}
void jugar() {
    char tablero[8][8];
    string jugador1;
    string jugador2;

    int turno = TURNO_BLANCAS;
    bool juegoActivo = true;

    inicializarTablero(tablero);

    cout << "Jugador 1 (Blancas) : " << endl;
    cin >> jugador1;
    cout << "Jugador 2 (Negras) : " << endl;
    cin >> jugador2;

    while (juegoActivo) {
        imprimirTablero(tablero);
        int opcion;
        string nombreTurno = (turno == TURNO_BLANCAS) ? jugador1 : jugador2;
        string colorTurno  = (turno == TURNO_BLANCAS) ? "BLANCAS" : "NEGRAS";

        cout << "Turno de " << nombreTurno << " - " << colorTurno << endl;
        cout <<"1. Mover pieza" << endl;
        cout <<"2. Rendirse" << endl;
        do {
            cout << "Seleccione una opcion: ";
            cin >> opcion;
        }while (opcion < 1 || opcion > 2);

        if (opcion == 2) {
            string ganador= (turno == TURNO_BLANCAS) ? jugador2 : jugador1;
            string colorGanador = (turno == TURNO_BLANCAS) ? "NEGRAS" : "BLANCAS";
            cout << nombreTurno << " se rindio." << endl;
            cout << "GANADOR: " << ganador << "-(PIEZAS " << colorGanador << ")" << endl;
            cout << "------ FIN DEL JUEGO ------" << endl;
            cout << endl;
            juegoActivo = false;
        }

    }

}



int main() {

    int opcion;

    cout << "============================================" << endl;
    cout << "         EL GAMBITO DE UTEC" << endl;
    cout << "       Ajedrez en C++ - Terminal" << endl;
    cout << "    CS1112 Programacion II - 2026-I" << endl;
    cout << "============================================" << endl;

    do {

        cout << "====== MENU PRINCIPAL ======" << endl;
        cout << "  0. Instrucciones" << endl;
        cout << "  1. Integrantes" << endl;
        cout << "  2. Consideraciones" << endl;
        cout << "  3. Jugar" << endl;
        cout << "  4. Salir" << endl;
        cout << "============================" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 0:
                mostrarInstrucciones();
                break;

            case 1:
                mostrarIntegrantes();
                break;

            case 2:
                mostrarConsideraciones();
                break;

            case 3:
                jugar();
                break;

            case 4:
                cout << "¡Hasta la proxima! Gracias por jugar El Gambito de UTEC." << endl;
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }

    } while(opcion != 4);

    return 0;
}