#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/resources.h"
//#include "../include/actions.h"
using namespace std;

// Declaracion de la funcion
void explorar();

int combustible = 30;
int oxigeno = 50;
int suministros = 40;
int integridad = 100; // 0 a 100 %
int dia = 1;

int main() {
    srand(time(0));
    int opcion;
    bool estasJugando = true;

    cout << "=== Simulador de Viaje Espacial ===" << endl;

    while(estasJugando && dia <= 10){

        cout << "\n=== Dia #" << dia << "===" << endl;
        cout << "Combustible: " << combustible << endl;
        cout << "Oxigeno: " << oxigeno << endl;
        cout << "Suministros: " << suministros << endl;
        cout << "Integridad: " << integridad << "%" << endl;

        cout << "\nQue deseas hacer" << endl;
        cout << "1) Explorar un planeta cercano." << endl;
        cout << "2) Reparar la nave." << endl;
        cout << "3) Enviar senales." << endl;
        cout << "4. Rendirse" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                explorar();
                break;
            case 2:
                cout << "Intentas reparar la nave... (-10 suministros, +5% integridad)\n";
                suministros -= 10;
                integridad += 5;
                if (integridad > 100) integridad = 100;
                break;
            case 3:
                cout << "Enviando senales al espacio...\n";
                break;
            case 4:
                cout << "Te has rendido. Fin del viaje.\n";
                estasJugando = false;
                break;
            default:
                cout << "Opcion invalida.\n";
        }

        if (combustible <= 0 || integridad <= 0 || oxigeno <= 0) {
            cout << "\nGame Over: Se acabo todo, sin recursos/ nave destruida";
            break;
        }

        // Avanzamos un dia
        dia++;
    }

    if (dia > 10)
        cout << "\nFelicidades, llegaste a tu destino despues de 10 dias.\n";

    cout << "Fin del juego.\n";
    return 0;
}

void explorar() {
    cout << "\nExplorando planeta cercano..." << endl;
    combustible -= 15;

    int evento = rand() % 100;
    if (evento < 60) {
        // Oxígeno (60%)
        int oxigenoEncontrado = 20 + rand() % 21; // 20-40
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxígeno." << endl;
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
        // Tormenta eléctrica (3%)
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Tormenta electrica: -" << dano << "% de integridad de la nave." << endl;
    } else {
        // Aterrizaje forzado (2%)
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Aterrizaje forzado: -" << dano << "% de integridad de la nave." << endl;
    }

    if (integridad > 100) integridad = 100;
    if (integridad < 0) integridad = 0;

    cout << "La exploracion ha terminado por hoy.\n";
}
