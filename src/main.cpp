#include <iostream>
#include "../include/resources.h"
using namespace std;

int main() {
    Resources s;
    int opcion;
    bool estasJugando = true;
    

    cout << "=== Simulador de Viaje Espacial ===" << endl;
    
    while(estasJugando && s.dia<=10){
    
     	cout << "\n=== Dia #"<< s.dia << "==="<< endl;
	    cout << "Combustible: " << s.combustible << endl;
	    cout << "Oxigeno: " << s.oxigeno << endl;
	    cout << "Suministros: " << s.suministros << endl;
	    cout << "Integridad: " << s.integridad << "%" << endl;
	    
	    cout << "\nQue deseas hacer" << endl;
        cout << "1) Explorar un planeta cercano." << endl;
        cout << "2) Reparar la nave." << endl;
        cout << "3) Enviar senales." << endl;
        cout << "4. Rendirse" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        
        switch(opcion){
        	case 1:
        		cout << "Explorando un planeta cercano... (-15 combustible)" <<endl;
                s.combustible -=15;
        		break;
        	case 2:
        		cout << "Intentas reparar la nave... (-10 suministros, +5% integridad)\n";
                s.suministros -= 10;
                s.integridad += 5;
                if (s.integridad > 100) s.integridad = 100;
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
		
		if (s.combustible <=0 || s.integridad <= 0 || s.oxigeno <=0) {
			cout << "\n Game Over: Se acabo todo, sin recursos/ nave destruida";
			break;
		}
		
		// Avanzamos un dia
		s.dia ++;
	
	}
	
	if (s.dia > 10)
		cout << "\nFelicidades, llegaste a tu destino despues de 10 dias.\n";
		
	cout << "Fin del juego.\n";
    return 0;
}
