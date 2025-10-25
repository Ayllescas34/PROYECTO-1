#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../include/resources.h"
// #include "../include/actions.h"

using namespace std;

// inicializamos los metodos
void explorar();
void reparar();
void enviarSenales();
void eventosAleatorios();

// ====== Variables globales ======
int combustible = 30;
int oxigeno     = 50;
int suministros = 40;
int integridad  = 100; // 0 a 100 %
int dia         = 1;

int main() {
    srand(time(0));
    int opcion;
    bool estasJugando = true;
    string nombreCapitan;

//iniciamos el juego, pedimos el nombre del capitan
    cout << "=== Simulador de Viaje Espacial ===" << endl;
    cout << "Hola, bienvenido al juego, ingresa tu nombre capitan: ";
    cin >> nombreCapitan;

//validamos que el dia sea hasta 10 ya que en 10gana el juego
    while (estasJugando && dia <= 10) {
        cout << "\nHola Capitan " << nombreCapitan << endl;

//mostramos los valores iniciales
        cout << "\n=== Dia #" << dia << "===" << endl;
        cout << "Combustible: " << combustible << endl;
        cout << "Oxigeno: "     << oxigeno     << endl;
        cout << "Suministros: " << suministros << endl;
        cout << "Integridad: "  << integridad  << "%" << endl;

//preguntamos que accion desea realizar
        cout << "\nQue deseas hacer" << endl;
        cout << "1) Explorar un planeta cercano." << endl;
        cout << "2) Reparar la nave." << endl;
        cout << "3) Enviar senales." << endl;
        cout << "4) Rendirse" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                explorar();
                break;
            case 2:
                reparar();
                break;
            case 3:
                enviarSenales();
                break;
            case 4:
                cout << "Te has rendido. Fin del viaje.\n";
                estasJugando = false;
                break;
            default:
                cout << "Opcion invalida.\n";
        }

        // Evento nocturno 
        eventosAleatorios();

        // Chequeo de fin de juego por recursos
        if (combustible <= 0 || oxigeno <= 0 || suministros <= 0 || integridad <= 0) {
            cout << "\nGame Over: ";
            if (combustible <= 0) cout << "Sin combustible. ";
            if (oxigeno     <= 0) cout << "Sin oxigeno. ";
            if (suministros <= 0) cout << "Sin suministros. ";
            if (integridad  <= 0) cout << "Nave destruida. ";
            cout << endl;
            break;
        }

        // Avanzamos un dia
        dia++;
    }

    if (dia > 10) {
        cout << "\nFelicidades, llegaste a tu destino despues de 10 dias.\n";
    }

    cout << "Fin del juego.\n";
    return 0;
}

// ====== servicios ======

void explorar() {
    cout << "\nExplorando planeta cercano..." << endl;

    combustible -= 15;
    if (combustible < 0) combustible = 0;

    int evento = rand() % 100;
    if (evento < 60) {
        // Oxigeno (60%)
        int oxigenoEncontrado = 20 + rand() % 21; // 20-40
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxigeno." << endl;
    } else if (evento < 85) {
        // Combustible (25%)
        int combustibleEncontrado = 10 + rand() % 21; // 10-30
        combustible += combustibleEncontrado;
        cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;
    } else if (evento < 95) {
        // Suministros (10%)
        int suministrosEncontrados = 30 + rand() % 71; // 30-100
        suministros += suministrosEncontrados;
        cout << "Encontraste " << suministrosEncontrados << " unidades de suministros." << endl;
    } else if (evento < 98) {
        // Tormenta electrica (3%)
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Tormenta electrica: -" << dano << "% de integridad de la nave." << endl;
    } else {
        // Aterrizaje forzado (2%)
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Aterrizaje forzado: -" << dano << "% de integridad de la nave." << endl;
    }

    // Limites
    if (integridad > 100) integridad = 100;
    if (integridad < 0)   integridad = 0;

    cout << "La exploracion ha terminado por hoy.\n";
}

void reparar() {
    cout << "\nIntentas reparar la nave..." << endl;

    int porcentaje;
    cout << "Cuanto porcentaje deseas reparar? (0-100): ";
    cin >> porcentaje;

    // Evitar negativos
    if (porcentaje < 0) porcentaje = 0;

    // Costo: 10 suministros por 1%
    int costo = porcentaje * 10;

    // Verificar si hay suficientes suministros
    if (costo > suministros) {
        cout << "No tienes suficientes suministros para reparar ese porcentaje." << endl;
        cout << "Tienes " << suministros << " unidades disponibles." << endl;
    } else {
        // Aplicar costo y reparacion
        suministros -= costo;
        if (suministros < 0) suministros = 0;

        integridad += porcentaje;
        if (integridad > 100) integridad = 100;
        if (integridad < 0)   integridad = 0;

        cout << "Has gastado " << costo << " suministros." << endl;
        cout << "La integridad actual de la nave es de " << integridad << "%." << endl;
    }
}

void enviarSenales() {
    cout << "\nEnviando senales al espacio..." << endl;

    // 50% ayuda, 50% piratas
    int evento = rand() % 2;

    if (evento == 0) {
        // Ayuda
        combustible += 60;
        cout << "Recibiste ayuda de una nave amiga: +60 combustible." << endl;
    } else {
        // Piratas
        integridad -= 15;
        suministros -= 20;

        // Limites para no negativos
        if (integridad  < 0) integridad  = 0;
        if (suministros < 0) suministros = 0;

        cout << "Piratas espaciales! -15% integridad y -20 suministros." << endl;
    }
}

void eventosAleatorios() {
    // Consumo de recursos al final del dia
    oxigeno     -= 20;
    suministros -= 30;
    cout << "Consumo de recursos: -20 de oxigeno, -30 de suministros" << endl;

    // Limitar a 0
    if (oxigeno     < 0) oxigeno     = 0;
    if (suministros < 0) suministros = 0;

    // Probabilidad del 15% de un evento nocturno (forzado en dia 1)
    int probabilidad = rand() % 100;
    if (dia == 1) probabilidad = 0;

    if (probabilidad < 15) {
        cout << "\nALERTA: EVENTO NOCTURNO" << endl;

        int tipoevento = rand() % 3;

        if (tipoevento == 0) {
            // Tormenta cosmica
            cout << "Tormenta cosmica" << endl;
            oxigeno -= 10;
            if (oxigeno < 0) oxigeno = 0;
            cout << "Oxigeno reducido en 10 unidades." << endl;

        } else if (tipoevento == 1) {
            // Encuentro alienigena
            cout << "Encuentro alienigena" << endl;
            int tipoalien = rand() % 2;

            if (tipoalien == 0) {
                combustible += 20;
                cout << "Son amistosos! Recibiste 20 unidades de combustible." << endl;
            } else {
                integridad -= 10;
                if (integridad < 0) integridad = 0;
                cout << "Son hostiles! dano en la nave: -10% de integridad." << endl;
            }

        } else {
            // Meteoritos
            cout << "Meteoritos" << endl;

            int decision = 0;
            while (decision != 1 && decision != 2) {
                cout << "Que deseas hacer?" << endl;
                cout << "1. Maniobrar (perderas combustible)" << endl;
                cout << "2. Recibir el impacto (se danara la nave)" << endl;
                cout << "Elige una opcion: ";
                cin >> decision;

                if (decision != 1 && decision != 2) {
                    cout << "\nOpcion invalida. Selecciona 1 o 2.\n" << endl;
                }
            }

            if (decision == 1) {
                // Maniobrar: gasto entre 10 y 30 combustible
                int combustibleGastado = 10 + rand() % 21;
                combustible -= combustibleGastado;
                if (combustible < 0) combustible = 0;
                cout << "Maniobras exitosas! Gastaste " << combustibleGastado
                     << " unidades de combustible." << endl;
            } else {
                // Impacto: dano entre 15 y 25% a integridad
                int dano = 15 + rand() % 11;
                integridad -= dano;
                if (integridad < 0) integridad = 0;
                cout << "Impacto recibido! La nave sufrio " << dano << "% de dano." << endl;
            }
        }
    }

    // Limites finales 
    if (combustible < 0) combustible = 0;
    if (oxigeno     < 0) oxigeno     = 0;
    if (suministros < 0) suministros = 0;
    if (integridad  < 0) integridad  = 0;

    cout << "\nLa noche ha terminado.\n";
}

