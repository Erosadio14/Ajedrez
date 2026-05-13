#include <iostream>
using namespace std;
#include "tablero.h"
#include "constantes.h"
#include "piezas_avanzadas.h"
#include "utilidades.h"
#include "piezas_basicas.h"


// Flags para validar el enroque:
bool reyBlancoMovido   = false;
bool reyNegroMovido    = false;
bool torreBlancoA_Mov  = false;
bool torreBlancoH_Mov  = false;
bool torreNegroA_Mov   = false;
bool torreNegroH_Mov   = false;
// fin de los flags

// Reiniciar flags al iniciar partida
void reiniciarFlags() {
    reyBlancoMovido   = false;
    reyNegroMovido    = false;
    torreBlancoA_Mov  = false;
    torreBlancoH_Mov  = false;
    torreNegroA_Mov   = false;
    torreNegroH_Mov   = false;
}

bool parsearCasilla(const string& entrada, int& fila, int& col) {
    if (entrada.size() < 2) return false;
    char buf[4];
    buf[0] = toupper((unsigned char)entrada[0]);
    buf[1] = entrada[1];
    buf[2] = '\0';
    if (buf[0] < 'A' || buf[0] > 'H') return false;
    if (buf[1] < '1' || buf[1] > '8') return false;
    lexCasilla(buf, &fila, &col);
    return true;
}

// ── Actualizar flag si una torre fue movida
void actualizarFlagTorre(int fo, int co) {
    if (fo == 0 && co == 0) torreBlancoA_Mov = true;
    if (fo == 0 && co == 7) torreBlancoH_Mov = true;
    if (fo == 7 && co == 0) torreNegroA_Mov  = true;
    if (fo == 7 && co == 7) torreNegroH_Mov  = true;
}

// ── Detectar y ejecutar enroque
bool manejarEnroque(char tab[8][8], int fo, int co, int fd, int cd, int turno) {
    char pieza = tab[fo][co];
    if (turno == TURNO_BLANCAS && pieza == REY_B && fo == 0 && co == 4) {
        if (fd == 0 && cd == 6) return intentarEnroque(tab, 'B', true);
        if (fd == 0 && cd == 2) return intentarEnroque(tab, 'B', false);
    }
    if (turno == TURNO_NEGRAS && pieza == REY_N && fo == 7 && co == 4) {
        if (fd == 7 && cd == 6) return intentarEnroque(tab, 'N', true);
        if (fd == 7 && cd == 2) return intentarEnroque(tab, 'N', false);
    }
    return false;
}

//MENU
void mostrarInstrucciones() {

    int opcion;

    do {

        cout << "======= INSTRUCCIONES =======" << endl;
        cout << "- Las blancas se mueven primero." << endl;
        cout << "- El juego termina cuando un rey es capturado o un jugador se rinde." << endl;

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

//
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

//LOGICA DE MOVIMIENTO

void moverTurno(char tablero[8][8], int turno, bool& juegoActivo,
                const string& jugador1, const string& jugador2) {

    string entradaOrigen, entradaDestino;
    int fo, co, fd, cd;

    cout << "Casilla de ORIGEN  (ej. E2): ";
    cin >> entradaOrigen;

    if (!parsearCasilla(entradaOrigen, fo, co)) {
        cout << "\n***** Movimiento NO VALIDO : formato invalido (use ej. E2) *****\n" << endl;
        return;
    }

    if (!validarRango(fo, co)) {
        cout << "\n***** Movimiento NO VALIDO : casilla fuera de rango *****\n" << endl;
        return;
    }

    char piezaOrigen = tablero[fo][co];

    if (piezaOrigen == VACIA) {
        cout << "\n***** Movimiento NO VALIDO : no hay pieza en la casilla de origen *****\n" << endl;
        return;
    }

    if (turno == TURNO_BLANCAS && piezaOrigen >= 'a' && piezaOrigen <= 'z') {
        cout << "\n***** Movimiento NO VALIDO : solo puedes mover piezas BLANCAS *****\n" << endl;
        return;
    }

    if (turno == TURNO_NEGRAS && piezaOrigen >= 'A' && piezaOrigen <= 'Z') {
        cout << "\n***** Movimiento NO VALIDO : solo puedes mover piezas NEGRAS *****\n" << endl;
        return;
    }

    cout << "Casilla de DESTINO (ej. E4): ";
    cin >> entradaDestino;

    if (!parsearCasilla(entradaDestino, fd, cd)) {
        cout << "\n***** Movimiento NO VALIDO : formato invalido (use ej. E4) *****\n" << endl;
        return;
    }

    if (!validarRango(fd, cd)) {
        cout << "\n***** Movimiento NO VALIDO : casilla fuera de rango *****\n" << endl;
        return;
    }

    if (fo == fd && co == cd) {
        cout << "\n***** Movimiento NO VALIDO : debes mover a una casilla diferente *****\n" << endl;
        return;
    }

    // Verificar enroque
    if (manejarEnroque(tablero, fo, co, fd, cd, turno)) {
        cout << "\nEnroque realizado." << endl;
        return;
    }

    // Validar movimiento segun la pieza
    if (!esMovimientoValido(tablero, fo, co, fd, cd, turno)) {
        cout << "\n***** Movimiento NO VALIDO : movimiento no permitido para esta pieza *****\n" << endl;
        return;
    }

    // Guardar pieza capturada
    char piezaCapturada = tablero[fd][cd];

    // Actualizar flag si se mueve una torre
    actualizarFlagTorre(fo, co);

    // Aplicar movimiento
    moverPieza(tablero, fo, co, fd, cd);
    cout << "\nMovimiento VALIDO." << endl;

    // Verificar coronacion del peon
    char piezaMovida = tablero[fd][cd];
    if (piezaMovida == PEON_B && fd == 7) coronarPeon(tablero, fd, cd);
    if (piezaMovida == PEON_N && fd == 0) coronarPeon(tablero, fd, cd);

    // Verificar fin de juego por captura de rey
    if (piezaCapturada == REY_B) {
        imprimirTablero(tablero);
        cout << "~~~ REY BLANCO ELIMINADO ~~~" << endl;
        cout << "~~~~~ GANADOR: " << jugador2 << " (PIEZAS NEGRAS) ~~~~~" << endl;
        cout << "~~~~~ FIN DEL JUEGO ~~~~~\n" << endl;
        juegoActivo = false;
    } else if (piezaCapturada == REY_N) {
        imprimirTablero(tablero);
        cout << "~~~ REY NEGRO ELIMINADO ~~~" << endl;
        cout << "~~~~~ GANADOR: " << jugador1 << " (PIEZAS BLANCAS) ~~~~~" << endl;
        cout << "~~~~~ FIN DEL JUEGO ~~~~~\n" << endl;
        juegoActivo = false;
    }
}

void jugar() {
    char tablero[8][8];
    string jugador1;
    string jugador2;

    int turno = TURNO_BLANCAS;
    bool juegoActivo = true;

    reiniciarFlags();
    inicializarTablero(tablero);

    cout << "Jugador 1 (Blancas) : " << endl;
    cin >> jugador1;
    cout << "Jugador 2 (Negras) : " << endl;
    cin >> jugador2;
    cout << "Comienza el juego! " << endl;

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
        } else {
            moverTurno(tablero,turno, juegoActivo, jugador1,jugador2);
            if (juegoActivo) {
                turno = (turno ==TURNO_BLANCAS) ? TURNO_NEGRAS : TURNO_BLANCAS;
            }
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