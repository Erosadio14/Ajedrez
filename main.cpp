#include <iostream>
#include "Partida.h"
using namespace std;

// ── Funciones del menu ───────────────────────────────────────────────────────

void mostrarInstrucciones() {
    cout << "======= INSTRUCCIONES =======" << endl;
    cout << "- Las blancas se mueven primero." << endl;
    cout << "- Ingrese casillas en formato ColFila, ej: E2" << endl;
    cout << "- Columnas: A-H | Filas: 1-8" << endl;
    cout << "- El juego termina por jaque mate, ahogado, tablas o rendicion." << endl;
    cout << endl;
    cout << "1. Volver al menu" << endl;
    cout << "2. Salir del juego" << endl;

    int opcion = -1;
    do {
        cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }
        switch(opcion) {
            case 1: break;
            case 2:
                cout << "Gracias por jugar." << endl;
                exit(0);
            default:
                cout << "======= INSTRUCCIONES =======" << endl;
                cout << "- Las blancas se mueven primero." << endl;
                cout << "- Ingrese casillas en formato ColFila, ej: E2" << endl;
                cout << "- Columnas: A-H | Filas: 1-8" << endl;
                cout << "- El juego termina por jaque mate, ahogado, tablas o rendicion." << endl;
                cout << endl;
                cout << "1. Volver al menu" << endl;
                cout << "2. Salir del juego" << endl;
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 1);
}

void mostrarIntegrantes() {
    cout << "======== INTEGRANTES ======" << endl;
    cout << "Integrante 1: Kihara Mamani" << endl;
    cout << "Integrante 2: Adrian Rosadio" << endl;
    cout << "Integrante 3: Adrian Cespedes" << endl;
    cout << "Integrante 4: Asael Herrera" << endl;
    cout << endl;
}

void mostrarConsideraciones() {
    cout << "======== CONSIDERACIONES ======" << endl;
    cout << "- Enroque con verificacion de jaque implementado." << endl;
    cout << "- Peon al paso implementado." << endl;
    cout << "- Jaque mate como condicion de fin de juego." << endl;
    cout << "- Ahogado (stalemate) implementado." << endl;
    cout << "- Tablas por repeticion de posicion (3 veces)." << endl;
    cout << "- Regla de los 50 movimientos implementada." << endl;
    cout << "- Historial de movimientos visible en pantalla." << endl;
    cout << "- Guardar y cargar partida en archivo .txt." << endl;
    cout << endl;
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    cout << "============================================" << endl;
    cout << "         EL GAMBITO DE UTEC" << endl;
    cout << "       Ajedrez en C++ - Terminal" << endl;
    cout << "    CS1112 Programacion II - 2026-I" << endl;
    cout << "============================================" << endl;

    Partida partida;

    cout << "====== MENU PRINCIPAL ======" << endl;
    cout << "  0. Instrucciones" << endl;
    cout << "  1. Integrantes" << endl;
    cout << "  2. Consideraciones" << endl;
    cout << "  3. Jugar" << endl;
    cout << "  4. Cargar partida" << endl;
    cout << "  5. Salir" << endl;
    cout << "============================" << endl;

    int opcion = -1;
    do {
        cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        } else {
            cin.ignore(1000, '\n');
        }

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
                partida.jugar();
                break;
            case 4:
                if (partida.cargarPartida()) {
                    partida.jugar();
                }
                break;
            case 5:
                cout << "¡Hasta la proxima! Gracias por jugar El Gambito de UTEC." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }

        if (opcion != 5) {
            cout << "====== MENU PRINCIPAL ======" << endl;
            cout << "  0. Instrucciones" << endl;
            cout << "  1. Integrantes" << endl;
            cout << "  2. Consideraciones" << endl;
            cout << "  3. Jugar" << endl;
            cout << "  4. Cargar partida" << endl;
            cout << "  5. Salir" << endl;
            cout << "============================" << endl;
        }

    } while (opcion != 5);

    return 0;
}