//
// Created by Erick on 18/09/25.
//

#include "MenuInterface.h"
#include "LogsManager.h"
#include <iostream>
using namespace std;


MenuInterface::MenuInterface() {
    clearScreen();
    logsOrdenados = LogManager::cargarLogs("bitacora.txt");
    cout << "Logs cargados: " << logsOrdenados.size() << " registros" << endl;
}

void MenuInterface::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Funcion que solamente me muestra las opciones de busqueda de los logs
void MenuInterface::mostrarOpciones() {
    cout<<"\n============== Menu de busqueda ============== "<< endl;
    cout << "1. Buscar por IP" << endl;
    cout << "2. Salir" << endl;
}

int MenuInterface::leerOpcion(int min, int max) {
    int opcion{0};

    do {
        cout << "Selecciona una opcion (" << min << " al " << max << "): ";
        cin >> opcion;

        if (cin.fail()) {
            cout << "Error: Debes introducir un numero valido" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (opcion < min || opcion > max) {
            cout << "Error: Opcion fuera de rango. Intenta de nuevo." << endl;
            continue;
        }

        return opcion;

    } while (true);
}

void MenuInterface::hacerBusqueda(int opcion) {
    switch (opcion) {
        case 1: {
            string ip;
            cout << "\n=== Buscar por IP ===" << endl;
            cout << "Ingresa la IP a buscar (ej: 172.245.125.21): ";
            cin >> ip;

            vector<LogManager> resultados = LogManager::buscarPorIP(logsOrdenados, ip);

            contadorBusquedas++;
            LogManager::guardarResultados(resultados, contadorBusquedas, NUMERO_EQUIPO);

            break;
        }
        default:
            cout << "Adios :3" << endl;
            break;
    }
}
void MenuInterface::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        opcion = leerOpcion(1,2);
        hacerBusqueda(opcion);

    } while (opcion != 2);
}