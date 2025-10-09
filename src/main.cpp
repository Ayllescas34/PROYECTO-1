#include <iostream>
#include "../include/resources.h"
using namespace std;

int main() {
    Resources r;

    cout << "=== Simulador de Viaje Espacial ===" << endl;
    cout << "Combustible inicial: " << r.combustible << endl;
    cout << "Oxigeno inicial: " << r.oxigeno << endl;
    cout << "Suministros iniciales: " << r.suministros << endl;
    cout << "Integridad inicial: " << r.integridad << "%" << endl;

    return 0;
}
