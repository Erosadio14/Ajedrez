#include "Partida.h"
#include "Peon.h"
#include "Torre.h"
#include "Alfil.h"
#include "Dama.h"
#include "Rey.h"
#include "Caballo.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// ── Constructor / Destructor
Partida::Partida() {
    reiniciarEstado();
}

Partida::~Partida() {
}

// ── Reiniciar estado
void Partida::reiniciarEstado() {
    turno          = TURNO_BLANCAS;
    numMovimientos = 0;
    contador50     = 0;
    numPosiciones  = 0;

    huboDobleAvance = false;
    ultimaPeonFila  = -1;
    ultimaPeonCol   = -1;

    reyBlancoMovido  = false;
    reyNegroMovido   = false;
    torreBlancoA_Mov = false;
    torreBlancoH_Mov = false;
    torreNegroA_Mov  = false;
    torreNegroH_Mov  = false;
}

// ── Color actual como char
char Partida::colorActual() const {
    return (turno == TURNO_BLANCAS) ? 'B' : 'N';
}

// ── Inicializar piezas en el tablero ─────────────────────────────────────────
void Partida::inicializarPiezas() {
    tablero.limpiar();

    // Blancas fila 0
    tablero.setPieza(0, 0, new Torre   ('B', 0, 0));
    tablero.setPieza(0, 1, new Caballo ('B', 0, 1));
    tablero.setPieza(0, 2, new Alfil   ('B', 0, 2));
    tablero.setPieza(0, 3, new Dama    ('B', 0, 3));
    tablero.setPieza(0, 4, new Rey     ('B', 0, 4));
    tablero.setPieza(0, 5, new Alfil   ('B', 0, 5));
    tablero.setPieza(0, 6, new Caballo ('B', 0, 6));
    tablero.setPieza(0, 7, new Torre   ('B', 0, 7));

    // Peones blancos fila 1
    for (int c = 0; c < 8; c++)
        tablero.setPieza(1, c, new Peon('B', 1, c));

    // Negras fila 7
    tablero.setPieza(7, 0, new Torre   ('N', 7, 0));
    tablero.setPieza(7, 1, new Caballo ('N', 7, 1));
    tablero.setPieza(7, 2, new Alfil   ('N', 7, 2));
    tablero.setPieza(7, 3, new Dama    ('N', 7, 3));
    tablero.setPieza(7, 4, new Rey     ('N', 7, 4));
    tablero.setPieza(7, 5, new Alfil   ('N', 7, 5));
    tablero.setPieza(7, 6, new Caballo ('N', 7, 6));
    tablero.setPieza(7, 7, new Torre   ('N', 7, 7));

    // Peones negros fila 6
    for (int c = 0; c < 8; c++)
        tablero.setPieza(6, c, new Peon('N', 6, c));
}

// ── Verificar si movimiento deja al rey propio en jaque ──────────────────────
bool Partida::dejaPropioReyEnJaque(int fo, int co, int fd, int cd) const{
    Tablero* copia = tablero.clonar();
    copia->mover(fo, co, fd, cd);
    bool enJaque = copia->estaEnJaque(colorActual());
    delete copia;
    return enJaque;
}

// ── Registrar movimiento en historial ────────────────────────────────────────
void Partida::registrarMovimiento(int fo, int co, int fd, int cd) {
    if (numMovimientos >= MAX_HISTORIAL) return;

    Pieza* p = tablero.getPieza(fo, co);
    if (p == nullptr) return;

    string mov = p->getSimbolo2L() + " ";
    mov += coordAString(fo, co);
    mov += "->";
    mov += coordAString(fd, cd);

    historial[numMovimientos] = mov;
    numMovimientos++;
}

// ── Mostrar historial ─────────────────────────────────────────────────────────
void Partida::mostrarHistorial() const {
    cout << "--- Historial (ultimos movimientos) ---" << endl;
    int inicio = (numMovimientos > 6) ? numMovimientos - 6 : 0;
    for (int i = inicio; i < numMovimientos; i += 2) {
        int num = i / 2 + 1;
        cout << num << ". " << historial[i];
        if (i + 1 < numMovimientos)
            cout << "   " << historial[i + 1];
        cout << endl;
    }
    cout << "---------------------------------------" << endl;
}

// ── Estado del tablero como string 64 chars ───────────────────────────────────
string Partida::estadoTablero() const {
    string estado = "";
    for (int f = 0; f < 8; f++) {
        for (int c = 0; c < 8; c++) {
            Pieza* p = tablero.getPieza(f, c);
            if (p == nullptr) estado += '.';
            else {
                estado += p->getSimbolo();
                estado += p->getColor();
            }
        }
    }
    return estado;
}

// ── Verificar repeticion de posicion ─────────────────────────────────────────
bool Partida::verificarRepeticion() {
    string estado = estadoTablero();
    int count = 0;
    for (int i = 0; i < numPosiciones; i++) {
        if (posiciones[i] == estado) count++;
    }
    if (numPosiciones < MAX_HISTORIAL)
        posiciones[numPosiciones++] = estado;
    return count >= MAX_REPETICIONES - 1;
}

// ── Verificar regla 50 movimientos ───────────────────────────────────────────
bool Partida::verificar50Movimientos() const {
    return contador50 >= MAX_MOVIMIENTOS_SIN_CAPTURA * 2;
}

// ── Verificar si tiene movimientos legales ────────────────────────────────────
bool Partida::tieneMovimientosLegales() {
    char color = colorActual();
    for (int fo = 0; fo < 8; fo++) {
        for (int co = 0; co < 8; co++) {
            Pieza* p = tablero.getPieza(fo, co);
            if (p == nullptr || p->getColor() != color) continue;
            for (int fd = 0; fd < 8; fd++) {
                for (int cd = 0; cd < 8; cd++) {
                    if (fo == fd && co == cd) continue;
                    if (p->movimientoValido(tablero, fd, cd)) {
                        if (!dejaPropioReyEnJaque(fo, co, fd, cd))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

// ── Jaque mate ────────────────────────────────────────────────────────────────
bool Partida::esJaqueMate() {
    return tablero.estaEnJaque(colorActual()) && !tieneMovimientosLegales();
}

// ── Ahogado ───────────────────────────────────────────────────────────────────
bool Partida::esAhogado() {
    return !tablero.estaEnJaque(colorActual()) && !tieneMovimientosLegales();
}

// ── Manejar enroque ───────────────────────────────────────────────────────────
bool Partida::manejarEnroque(int fo, int co, int fd, int cd) {
    Pieza* pieza = tablero.getPieza(fo, co);
    if (pieza == nullptr || pieza->getSimbolo() != 'R') return false;

    char color = colorActual();
    int fila   = (color == 'B') ? 0 : 7;

    if (fo != fila || co != 4) return false;
    if (fd != fila) return false;

    bool corto = (cd == 6);
    bool largo = (cd == 2);
    if (!corto && !largo) return false;

    // Verificar flags
    if (color == 'B') {
        if (reyBlancoMovido) { cout << "\n***** El rey blanco ya se ha movido *****\n"; return false; }
        if (corto && torreBlancoH_Mov) { cout << "\n***** La torre H blanca ya se ha movido *****\n"; return false; }
        if (largo && torreBlancoA_Mov) { cout << "\n***** La torre A blanca ya se ha movido *****\n"; return false; }
    } else {
        if (reyNegroMovido) { cout << "\n***** El rey negro ya se ha movido *****\n"; return false; }
        if (corto && torreNegroH_Mov) { cout << "\n***** La torre H negra ya se ha movido *****\n"; return false; }
        if (largo && torreNegroA_Mov) { cout << "\n***** La torre A negra ya se ha movido *****\n"; return false; }
    }

    // Verificar casillas libres
    if (corto) {
        if (tablero.getPieza(fila, 5) != nullptr || tablero.getPieza(fila, 6) != nullptr) {
            cout << "\n***** Hay piezas entre el rey y la torre *****\n"; return false;
        }
    } else {
        if (tablero.getPieza(fila, 1) != nullptr || tablero.getPieza(fila, 2) != nullptr ||
            tablero.getPieza(fila, 3) != nullptr) {
            cout << "\n***** Hay piezas entre el rey y la torre *****\n"; return false;
        }
    }

    // Verificar jaque en casillas de paso
    if (tablero.estaEnJaque(color)) {
        cout << "\n***** No puedes enrocar estando en jaque *****\n"; return false;
    }

    int colPaso = corto ? 5 : 3;
    tablero.mover(fo, co, fila, colPaso);
    if (tablero.estaEnJaque(color)) {
        tablero.mover(fila, colPaso, fo, co);
        cout << "\n***** El rey pasaria por una casilla atacada *****\n"; return false;
    }
    tablero.mover(fila, colPaso, fo, co);

    // Ejecutar enroque
    int colTorreOrigen  = corto ? 7 : 0;
    int colReyDestino   = corto ? 6 : 2;
    int colTorreDestino = corto ? 5 : 3;

    tablero.mover(fo, co, fila, colReyDestino);
    tablero.mover(fila, colTorreOrigen, fila, colTorreDestino);

    // Actualizar flags
    if (color == 'B') { reyBlancoMovido = true; if (corto) torreBlancoH_Mov = true; else torreBlancoA_Mov = true; }
    else              { reyNegroMovido  = true; if (corto) torreNegroH_Mov  = true; else torreNegroA_Mov  = true; }

    cout << "\nEnroque realizado." << endl;
    return true;
}

// ── Manejar peon al paso ──────────────────────────────────────────────────────
bool Partida::manejarPeonAlPaso(int fo, int co, int fd, int cd) {
    Pieza* pieza = tablero.getPieza(fo, co);
    if (pieza == nullptr || pieza->getSimbolo() != 'P') return false;
    if (!huboDobleAvance) return false;

    int direccion   = (colorActual() == 'B') ? 1 : -1;
    int filaEnPassant = (colorActual() == 'B') ? 4 : 3;

    if (fo != filaEnPassant) return false;
    if (fd != fo + direccion) return false;
    if (abs(cd - co) != 1) return false;
    if (cd != ultimaPeonCol) return false;
    if (tablero.getPieza(fd, cd) != nullptr) return false;

    // Eliminar peon capturado
    delete tablero.getPieza(fo, cd);
    tablero.setPieza(fo, cd, nullptr);

    // Mover peon
    tablero.mover(fo, co, fd, cd);
    cout << "\nPeon al paso realizado." << endl;
    return true;
}

// ── Mostrar estado (tablero + historial) ──────────────────────────────────────
void Partida::mostrarEstado() const {
    cout << tablero;
    if (numMovimientos > 0) mostrarHistorial();
}

// ── Procesar turno
void Partida::procesarTurno() {
    string nombreTurno  = (turno == TURNO_BLANCAS) ? jugador1 : jugador2;
    string colorTurno   = (turno == TURNO_BLANCAS) ? "BLANCAS" : "NEGRAS";
    char   color        = colorActual();

    // Avisar jaque
    if (tablero.estaEnJaque(color)) {
        cout << "\n***** JAQUE al Rey " << colorTurno << "! *****\n" << endl;
    }

    cout << "Turno de " << nombreTurno << " (" << colorTurno << ")" << endl;
    cout << "1. Mover pieza" << endl;
    cout << "0. Rendirse" << endl;

    int opcion = -1;
    do {
        cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }
    } while (opcion < 0 || opcion > 1);

    if (opcion == 0) {
        string ganador      = (turno == TURNO_BLANCAS) ? jugador2 : jugador1;
        string colorGanador = (turno == TURNO_BLANCAS) ? "NEGRAS" : "BLANCAS";
        cout << nombreTurno << " se rindio." << endl;
        cout << "~~~~~ GANADOR: " << ganador << " (PIEZAS " << colorGanador << ") ~~~~~" << endl;
        cout << "~~~~~ FIN DEL JUEGO ~~~~~" << endl;
        turno = -1;
        return;
    }

    // Leer casillas
    string entradaOrigen, entradaDestino;
    int fo, co, fd, cd;

    cout << "Casilla de ORIGEN  (ej. E2): ";
    cin >> entradaOrigen;

    if (!parsearCasilla(entradaOrigen, fo, co)) return;

    Pieza* piezaOrigen = tablero.getPieza(fo, co);

    if (piezaOrigen == nullptr) {
        cout << "\n***** Movimiento NO VALIDO : no hay pieza en la casilla de origen *****\n"; return;
    }
    if (piezaOrigen->getColor() != color) {
        cout << "\n***** Movimiento NO VALIDO : solo puedes mover piezas " << colorTurno << " *****\n"; return;
    }

    cout << "Casilla de DESTINO (ej. E4): ";
    cin >> entradaDestino;

    if (!parsearCasilla(entradaDestino, fd, cd)) return;

    if (fo == fd && co == cd) {
        cout << "\n***** Movimiento NO VALIDO : debes mover a una casilla diferente *****\n"; return;
    }

    // Intentar enroque
    if (manejarEnroque(fo, co, fd, cd)) {
        registrarMovimiento(fo, co, fd, cd);
        contador50++;
        huboDobleAvance = false;
        turno = (turno == TURNO_BLANCAS) ? TURNO_NEGRAS : TURNO_BLANCAS;
        return;
    }

    // Intentar peon al paso
    if (manejarPeonAlPaso(fo, co, fd, cd)) {
        registrarMovimiento(fo, co, fd, cd);
        contador50 = 0;
        huboDobleAvance = false;
        turno = (turno == TURNO_BLANCAS) ? TURNO_NEGRAS : TURNO_BLANCAS;
        return;
    }

    // Validar movimiento normal
    if (!piezaOrigen->movimientoValido(tablero, fd, cd)) {
        cout << "\n***** Movimiento NO VALIDO : movimiento no permitido para esta pieza *****\n"; return;
    }

    // Verificar que no deja al rey propio en jaque
    if (dejaPropioReyEnJaque(fo, co, fd, cd)) {
        cout << "\n***** Movimiento NO VALIDO : dejarias tu propio Rey en jaque *****\n"; return;
    }

    // Guardar info para peon al paso
    bool esPeon   = (piezaOrigen->getSimbolo() == 'P');
    bool esDoble  = esPeon && abs(fd - fo) == 2;
    bool esCaptura = (tablero.getPieza(fd, cd) != nullptr);

    // Registrar antes de mover
    registrarMovimiento(fo, co, fd, cd);

    // Actualizar flags de torre/rey
    if (piezaOrigen->getSimbolo() == 'R') {
        if (color == 'B') reyBlancoMovido = true;
        else              reyNegroMovido  = true;
    }
    if (piezaOrigen->getSimbolo() == 'T') {
        if (fo == 0 && co == 0) torreBlancoA_Mov = true;
        if (fo == 0 && co == 7) torreBlancoH_Mov = true;
        if (fo == 7 && co == 0) torreNegroA_Mov  = true;
        if (fo == 7 && co == 7) torreNegroH_Mov  = true;
    }

    // Aplicar movimiento
    tablero.mover(fo, co, fd, cd);
    cout << "\nMovimiento VALIDO." << endl;

    // Actualizar contador 50
    if (esPeon || esCaptura) contador50 = 0;
    else                     contador50++;

    // Actualizar peon al paso
    huboDobleAvance = esDoble;
    ultimaPeonFila  = esDoble ? fd : -1;
    ultimaPeonCol   = esDoble ? cd : -1;

    // Verificar coronacion
    Pieza* piezaMovida = tablero.getPieza(fd, cd);
    if (piezaMovida != nullptr && piezaMovida->getSimbolo() == 'P') {
        if ((color == 'B' && fd == 7) || (color == 'N' && fd == 0)) {
            cout << "\n~~~~~ CORONAR PEON ~~~~~" << endl;
            cout << "0.- Ninguna (Peon)" << endl;
            cout << "1.- Reina" << endl;
            cout << "2.- Torre" << endl;
            cout << "3.- Alfil" << endl;
            cout << "4.- Caballo" << endl;
            cout << "Su eleccion: ";
            int eleccion;
            cin >> eleccion;
            Pieza* nueva = nullptr;
            switch(eleccion) {
                case 1: nueva = new Dama   (color, fd, cd); break;
                case 2: nueva = new Torre  (color, fd, cd); break;
                case 3: nueva = new Alfil  (color, fd, cd); break;
                case 4: nueva = new Caballo(color, fd, cd); break;
                default: break;
            }
            if (nueva != nullptr) {
                delete tablero.getPieza(fd, cd);
                tablero.setPieza(fd, cd, nueva);
            }
        }
    }

    // Avisar jaque al rival
    char colorRival = (color == 'B') ? 'N' : 'B';
    if (tablero.estaEnJaque(colorRival)) {
        string colorRivalStr = (colorRival == 'B') ? "BLANCO" : "NEGRO";
        cout << "\n***** JAQUE al Rey " << colorRivalStr << "! *****" << endl;
    }

    turno = (turno == TURNO_BLANCAS) ? TURNO_NEGRAS : TURNO_BLANCAS;
}

// ── Iniciar partida
void Partida::iniciar() {
    reiniciarEstado();
    inicializarPiezas();

    cout << "Jugador 1 (Blancas): ";
    cin >> jugador1;
    cout << "Jugador 2 (Negras) : ";
    cin >> jugador2;
    cin.ignore(1000, '\n');

    cout << "\n¡Comienza el juego!" << endl;
}

// ── Loop principal
void Partida::jugar() {
    iniciar();

    while (turno == TURNO_BLANCAS || turno == TURNO_NEGRAS) {
        mostrarEstado();

        // Verificar fin de juego
        if (esJaqueMate()) {
            string ganador      = (turno == TURNO_BLANCAS) ? jugador2 : jugador1;
            string colorGanador = (turno == TURNO_BLANCAS) ? "NEGRAS" : "BLANCAS";
            cout << "~~~ JAQUE MATE ~~~" << endl;
            cout << "~~~~~ GANADOR: " << ganador << " (PIEZAS " << colorGanador << ") ~~~~~" << endl;
            cout << "~~~~~ FIN DEL JUEGO ~~~~~" << endl;
            break;
        }

        if (esAhogado()) {
            cout << "~~~ AHOGADO: ningun movimiento legal ~~~" << endl;
            cout << "~~~~~ RESULTADO: TABLAS ~~~~~" << endl;
            break;
        }

        if (verificarRepeticion()) {
            cout << "~~~ TABLAS por repeticion de posicion (3 veces) ~~~" << endl;
            cout << "~~~~~ RESULTADO: TABLAS ~~~~~" << endl;
            break;
        }

        if (verificar50Movimientos()) {
            cout << "~~~ TABLAS por regla de los 50 movimientos ~~~" << endl;
            cout << "~~~~~ RESULTADO: TABLAS ~~~~~" << endl;
            break;
        }

        procesarTurno();
    }
}

// ── Guardar partida
void Partida::guardarPartida() const {
    ofstream archivo(ARCHIVO_PARTIDA);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo guardar la partida." << endl;
        return;
    }

    archivo << jugador1 << "\n" << jugador2 << "\n";
    archivo << turno << "\n";
    archivo << contador50 << "\n";
    archivo << numMovimientos << "\n";

    for (int i = 0; i < numMovimientos; i++)
        archivo << historial[i] << "\n";

    // Flags de enroque
    archivo << reyBlancoMovido  << "\n";
    archivo << reyNegroMovido   << "\n";
    archivo << torreBlancoA_Mov << "\n";
    archivo << torreBlancoH_Mov << "\n";
    archivo << torreNegroA_Mov  << "\n";
    archivo << torreNegroH_Mov  << "\n";

    // Estado del tablero
    archivo << estadoTablero() << "\n";

    archivo.close();
    cout << "Partida guardada en " << ARCHIVO_PARTIDA << endl;
}

// ── Cargar partida ────────────────────────────────────────────────────────────
bool Partida::cargarPartida() {
    ifstream archivo(ARCHIVO_PARTIDA);
    if (!archivo.is_open()) {
        cout << "Error: no se encontro el archivo " << ARCHIVO_PARTIDA << endl;
        return false;
    }

    reiniciarEstado();
    tablero.limpiar();

    getline(archivo, jugador1);
    getline(archivo, jugador2);
    archivo >> turno >> contador50 >> numMovimientos;
    archivo.ignore();

    for (int i = 0; i < numMovimientos; i++)
        getline(archivo, historial[i]);

    archivo >> reyBlancoMovido >> reyNegroMovido;
    archivo >> torreBlancoA_Mov >> torreBlancoH_Mov;
    archivo >> torreNegroA_Mov  >> torreNegroH_Mov;
    archivo.ignore();

    string estado;
    getline(archivo, estado);
    archivo.close();

    // Reconstruir tablero desde string de 64 chars
    // estado: cada casilla ocupa 2 chars (simbolo + color) o '.' para vacía
    int idx = 0;
    for (int f = 0; f < 8 && idx < (int)estado.size(); f++) {
        for (int c = 0; c < 8 && idx < (int)estado.size(); c++) {
            if (estado[idx] == '.') {
                tablero.setPieza(f, c, nullptr);
                idx++;
            } else {
                char sim   = estado[idx];
                char color = estado[idx + 1];
                idx += 2;
                Pieza* p = nullptr;
                switch(sim) {
                    case 'P': p = new Peon   (color, f, c); break;
                    case 'T': p = new Torre  (color, f, c); break;
                    case 'C': p = new Caballo(color, f, c); break;
                    case 'A': p = new Alfil  (color, f, c); break;
                    case 'D': p = new Dama   (color, f, c); break;
                    case 'R': p = new Rey    (color, f, c); break;
                    default: break;
                }
                tablero.setPieza(f, c, p);
            }
        }
    }

    cout << "Partida cargada correctamente." << endl;
    return true;
}