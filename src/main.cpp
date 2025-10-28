#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/resources.h"
//#include "../include/actions.h"
using namespace std;

// Declaracion de la funcion
void explorar();
void eventosAleatorios();

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

        if (!estasJugando) {
            break;
        }

        eventosAleatorios();

        if (combustible <= 0 || integridad <= 0 || oxigeno <= 0 || suministros <= 0) {
            cout << "\nGAME OVER: Te has quedado sin recursos o la nave fue destruida.\n";
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

void eventosAleatorios() {
    //consumo de recursos
    oxigeno -= 20;
    suministros -=30;
    cout << "Consumo de recursos: -20 de oxigeno, -30 de suministros" << endl;

    //evento aleatorio con 15% de probabilidad
    int probabilidad = rand() % 100;

    //condicion para qeu toque evento en primer dia
    if (dia == 1) {
        probabilidad = 0;
    }

    if (probabilidad < 15) {
        cout << "\nALERTA: EVENTO NOCTURNO" << endl;

        int tipoevento = rand() % 3;
        //tormenta cosmica
        if (tipoevento == 0) {
            cout << "Tormenta cosmica" << endl; 
            oxigeno -= 10;
            cout << "Oxigeno reducido en 10 unidades." << endl;
        
        //encuentro alienigena    
        } else if (tipoevento == 1) {
            cout << "Encuentro alienigena" << endl;

            int tipoalien = rand() % 2;
            if (tipoalien == 0) {
                combustible += 20;
                cout << "Son amistosos! Recibiste 20 unidades de combustible." << endl;
            } else {
                integridad -=10;
                cout << "Son hostiles! dano en la nave: -10% de integridad" << endl;
            }
         
        //meteoritos       
        } else {
            cout << "Meteoritos" << endl;

            int decision = 0;

            while (decision != 1 && decision !=2) {
                cout << "Que deseas hacer?" << endl;
                cout << "1. Maniobrar (perderas combustible)" << endl;
                cout << "2. Recibir el impacto (se dañara la nave)" << endl;
                cout << "Elige una opcion: ";
                cin >> decision;

                if (decision != 1 && decision != 2) {
                    cout << "\nOpcion invalida. Selecciona 1 o 2.\n" << endl;
                }
            }

            if (decision == 1) {
                //maniobrar, gasto entre 10 y 30
                int combustibleGastado = 10 + rand() % 21;
                combustible -= combustibleGastado;
                cout << "Maniobras exitosas! Gastaste " << combustibleGastado << "unidades de combustible" << endl;
                
            }else {
                //impacto, dano entre 15 y 25
                int dano = 15 + rand () % 11;
                integridad -= dano;
                cout << "Impacto recibido! La nave sufrio dano de " << dano << "% de dano" << endl;
            }

        }    
    } 
    cout << "\nLa noche ha terminado.\n";
}
