#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>      // Para sleep_for (pausas de tiempo)
#include <chrono>      // Para sleep_for (pausas de tiempo)
#include "../include/resources.h"
//#include "../include/actions.h"
using namespace std;

// Declaración de funciones principales del juego
void explorar();
void eventosAleatorios();
void repararNave ();
void modoHacker();

int combustible = 30;
int oxigeno = 50;
int suministros = 40;
int integridad = 100; // 0 a 100 %
int dia = 1;

// Limpia la pantalla (solo Windows)
// Borra la consola para mostrar solo la información relevante del turno actual.
void limpiarPantalla() {
    system("cls");
}

// Animación de carga simple con puntos
// Simula que el programa está "procesando" algo, mostrando puntos uno a uno con pausas.
// El parámetro 'ms' indica el tiempo total de la animación en milisegundos.
void animacionCarga(int ms = 1200) {
    cout << "Procesando";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush(); // Muestra el punto inmediatamente
        this_thread::sleep_for(chrono::milliseconds(ms / 3)); // Pausa entre cada punto
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int opcion;
    bool estasJugando = true;
    string nombreCapitan;

    // --- Inicio del juego ---
    limpiarPantalla(); // Limpia pantalla antes de mostrar el menú inicial
    cout << "=== Simulador de Viaje Espacial ===" << endl;
    cout << "Hola, bienvenido al juego, ingresa tu nombre capitan: ";
    cin >> nombreCapitan;

    // --- Ciclo principal del juego ---
    while (estasJugando && dia <= 10) {
        bool hackerActivado = false; //usamos la bandera para ver lo de modo hacker
        limpiarPantalla(); // Limpia pantalla al inicio de cada día
        cout << "\n========================================" << endl;
        cout << "      === Simulador de Viaje Espacial ===" << endl;
        cout << "========================================\n" << endl;
        cout << "\nHola Capitan " << nombreCapitan << endl;

        // Mostramos los valores iniciales
        cout << "\n=== Dia #" << dia << "===" << endl;
        cout << "Combustible: " << combustible << endl;
        cout << "Oxigeno: "     << oxigeno     << endl;
        cout << "Suministros: " << suministros << endl;
        cout << "Integridad: "  << integridad  << "%" << endl;

        // Preguntamos que accion desea realizar
        cout << "\nQue deseas hacer" << endl;
        cout << "1) Explorar un planeta cercano." << endl;
        cout << "2) Reparar la nave." << endl;
        cout << "3) Enviar senales." << endl;
        cout << "4) Rendirse" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        animacionCarga(3000); // Animación de carga tras elegir opción

        switch(opcion){
            case 1:
                explorar();
                this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa tras explorar
                break;
            case 2:
                repararNave();
                this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa tras reparar
                break;
            case 3:
                cout << "Enviando senales al espacio...\n";
                this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa tras enviar señales
                break;
            case 4:
                cout << "Te has rendido. Fin del viaje.\n";
                estasJugando = false;
                break;
            case 99:
                modoHacker();
                this_thread::sleep_for(chrono::milliseconds(3000));
                limpiarPantalla();
                hackerActivado = true;
                break;
            default:
                cout << "Opcion invalida.\n";
                this_thread::sleep_for(chrono::milliseconds(3000));
        }

        if (!estasJugando) {
            break;
        }

        // Solo ejecuta eventos y avanza el día si NO fue modo hacker
        if (!hackerActivado) {
            eventosAleatorios();
            this_thread::sleep_for(chrono::milliseconds(3000));

            if (combustible <= 0 || integridad <= 0 || oxigeno <= 0 || suministros <= 0) {
                cout << "\nGAME OVER: Te has quedado sin recursos o la nave fue destruida.\n";
                break;
            }

            dia++; // Solo avanza el día si no fue modo hacker
        }
    }

    if (dia > 10)
        cout << "\nFelicidades, llegaste a tu destino despues de 10 dias.\n";

    cout << "Fin del juego.\n";
    return 0;
}

void explorar() {
    cout << "\nExplorando planeta cercano..." << endl;
    this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa para simular exploración
    combustible -= 15;

    int evento = rand() % 100;
    if (evento < 60) {
        int oxigenoEncontrado = 20 + rand() % 21; // 20-40
        oxigeno += oxigenoEncontrado;
        cout << "Encontraste " << oxigenoEncontrado << " unidades de oxígeno." << endl;
    } else if (evento < 85) {
        int combustibleEncontrado = 10 + rand() % 21; // 10-30
        combustible += combustibleEncontrado;
        cout << "Encontraste " << combustibleEncontrado << " unidades de combustible." << endl;
    } else if (evento < 95) {
        int suministrosEncontrados = 30 + rand() % 71; // 30-100
        suministros += suministrosEncontrados;
        cout << "Encontraste " << suministrosEncontrados << " unidades de suministros." << endl;
    } else if (evento < 98) {
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Tormenta electrica: -" << dano << "% de integridad de la nave." << endl;
    } else {
        int dano = 10 + rand() % 11; // 10-20
        integridad -= dano;
        cout << "Aterrizaje forzado: -" << dano << "% de integridad de la nave." << endl;
    }

    if (integridad > 100) integridad = 100;
    if (integridad < 0) integridad = 0;

    cout << "La exploracion ha terminado por hoy.\n";
}

void eventosAleatorios() {
    // Mostrar recursos antes del consumo
    cout << "\n--- Consumo nocturno de recursos ---" << endl;
    cout << "Recursos antes de la noche:" << endl;
    cout << "Oxigeno: " << oxigeno << ", Suministros: " << suministros << endl;

    this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa antes de consumir recursos

    // Consumo nocturno
    oxigeno -= 20;
    suministros -= 30;

    // Mostrar recursos después del consumo
    cout << "Consumo de recursos: -20 de oxigeno, -30 de suministros" << endl;
    cout << "Recursos después de la noche:" << endl;
    cout << "Oxigeno: " << oxigeno << ", Suministros: " << suministros << endl;

    //evento aleatorio con 15% de probabilidad
    int probabilidad = rand() % 100;

    //condicion para que toque evento en primer dia
    if (dia == 1) {
        probabilidad = 0;
    }

    if (probabilidad < 15) {
        cout << "\nALERTA: EVENTO NOCTURNO" << endl;
        this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa antes del evento

        int tipoevento = rand() % 3;
        if (tipoevento == 0) {
            cout << "Tormenta cosmica" << endl; 
            oxigeno -= 10;
            cout << "Oxigeno reducido en 10 unidades." << endl;
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
                int combustibleGastado = 10 + rand() % 21;
                combustible -= combustibleGastado;
                cout << "Maniobras exitosas! Gastaste " << combustibleGastado << " unidades de combustible" << endl;
            }else {
                int dano = 15 + rand () % 11;
                integridad -= dano;
                cout << "Impacto recibido! La nave sufrio dano de " << dano << "% de dano" << endl;
            }
        }    
    } 
    cout << "\nLa noche ha terminado.\n";
}

void repararNave () {
    cout << "\nIntentas reparar la nave..." << endl;
    this_thread::sleep_for(chrono::milliseconds(3000)); // Pausa para simular reparación

    int porcentajeReparar;
    int suministrosNecesarios;

    if (integridad == 100) {
        cout<<"¡Ups!, todo parece estar en orden. Intentalo nuevamente mas tarde"<<endl;
    } else if (suministros == 0) {
        cout<<"Suministros agotados. No puedes reparar la nave. "<<endl;
    } else {
        do {
            cout<<"Que porcentaje deseas reparar?: "; 
            cin>>porcentajeReparar;

            if (porcentajeReparar < 0 || porcentajeReparar > 100){
                cout <<"¡Error!, el porcentaje a reparar debe estar entre 0 y 100. Intente nuevamente"<<endl;
                continue;
            }

            suministrosNecesarios = porcentajeReparar * 10;

            if (suministrosNecesarios > suministros) {
                cout<<"No tienes suficientes suministros. Necesitas "<<suministrosNecesarios<<" pero solo tienes "<<suministros<<endl;
                continue;
            } 
            break;
        } while(true);

        suministros -= suministrosNecesarios;
        integridad += porcentajeReparar;
        if (integridad > 100) integridad = 100;

        cout<<"Se reparara el "<<porcentajeReparar<<"% de la nave usando "<< suministrosNecesarios<<" unidades de suministros.\n";
        cout<<"Suministros restantes: "<<suministros<<endl;
        cout<<"Integridad actual: " << integridad << "%" << endl;
    }
}


void modoHacker() {
    int valor;
    
    cout << "\n========================================" << endl;
    cout << "=== MODO TRUCOS ACTIVADO (CODIGO 99) ===" << endl;
    cout << "========================================" << endl;
    
    // NOTA: Se evita la limpieza de cin para mantener el estilo "principiante"

    // === Combustible ===
    cout << "Combustible actual: " << combustible << ". Ingresa nuevo valor: ";
    cin >> valor;
    
    if (valor <= 0) {
        cout << "Valor no valido. Combustible se mantiene en: " << combustible << endl;
    } else {
        combustible = valor;
    }
    
    // === Oxígeno ===
    cout << "Oxigeno actual: " << oxigeno << ". Ingresa nuevo valor: ";
    cin >> valor;
    
    if (valor <= 0) {
        cout << "Valor no valido. Oxigeno se mantiene en: " << oxigeno << endl;
    } else {
        oxigeno = valor;
    }

    // === Suministros ===
    cout << "Suministros actuales: " << suministros << ". Ingresa nuevo valor: ";
    cin >> valor;
    
    if (valor <= 0) {
        cout << "Valor no valido. Suministros se mantiene en: " << suministros << endl;
    } else {
        suministros = valor;
    }

    // === Integridad (0 a 100) ===
    // La integridad es un caso especial, sí puede ser 0
    cout << "Integridad actual: " << integridad << "%. Ingresa nuevo valor (0 a 100): ";
    cin >> valor;
    
    if (valor < 0) {
        integridad = 0;
    } else if (valor > 100) {
        integridad = 100;
    } else {
        integridad = valor;
    }
    
    cout << "\n¡Recursos cambiados! ¡Volviendo al juego, Capitan!\n";
    
    // Dejamos la limpieza de errores básica.
    cin.clear();
}