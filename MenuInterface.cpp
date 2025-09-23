//
// Created by Erick on 18/09/25.
//

#include "MenuInterface.h"
#include <iostream>
using namespace std;

//TODO: terminar las funciones de estos
MenuInterface::MenuInterface() {
}
// destructor
MenuInterface::~MenuInterface() {

}




// Funcion que solamente me muestra las opciones de busqueda de los logs
void MenuInterface::mostrarOpciones() {

    cout<<"\n============== Selecciona la manera en la que se seleccionaran los logs ============== "<< endl;
    cout << "1. Buscar por IP" << endl;
    cout << "2. Buscar por puerto" << endl;
    cout << "3. Buscar por fecha" << endl;
    cout << "4. Buscar por mensaje" << endl;
    cout << "5. Salir" << endl;
}

// Lee las opciones del menu.
int MenuInterface::leerOpcion(int min, int max) {
    int opcion{0};

    do {
        try {
            cout << "Selecciona una opcion (" << min << " al " << max << "): ";
            cin >> opcion;

            // ver si es texto o numero
            if (cin.fail()) {
                throw invalid_argument("Entrada no válida");
            }

            // Verificar rango
            if (opcion < min || opcion > max) {
                cout << "Error: Opcion fuera de rango. Intenta de nuevo." << endl;
                continue;
            }

            return opcion;

        } catch (const invalid_argument& e) {
            cout << "Error: Debes introducir un numero valido" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (true);
}


//TODO: mandarlo a la opcion de la busqueda de los logs.
void MenuInterface::hacerBusqueda(int opcion) {
    switch (opcion) {
        case 1 : cout<< "Busqueda de IP (Debug)"<<endl;
            break;
        case 2 : cout << "Buscar por puerto (debug)" <<endl;
            break;
        case 3 : cout<<"buscar por fecha (debug)" << endl;
            break;
        case 4 : cout <<"Buscar por mensaje (debug" << endl;
            break;
        default: cout << "Adio (debug)" << endl;
            break;
    }
}


// FLujo de como se debde de ejecutar lo de la interfaz del menu
void MenuInterface::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        opcion = leerOpcion(1,5);
        hacerBusqueda(opcion);

    } while (opcion != 5);
}