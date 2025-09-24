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
        case 1 : busquedaPorIP(); break;
        case 2 : busquedaPorPuerto(); break;
        case 3 : busquedaPorFecha(); break;
        case 4 : busquedaPorMensaje(); break;
        default: cout << "Adio (debug)" << endl; break;
    }
}


// FLujo de como se debde de ejecutar lo de la interfaz del menu
void MenuInterface::ejecutar() {
    cargarDatos(); // carga datos al iniciar
    int opcion;
    do {
        mostrarOpciones();
        opcion = leerOpcion(1,5);
        hacerBusqueda(opcion);

    } while (opcion != 5);
}

// las funciones nuevas de busqueda manera sencilla, donde se piden los datos y se muestran los resultados
void MenuInterface::cargarDatos() {
    // intentar cargar el archivo por defecto
    logsOrdenados = LogManager::cargarLogs(archivoFuente);
    if (logsOrdenados.empty()) {
        cout << "No se pudieron cargar los logs desde " << archivoFuente << endl;
    } else {
        cout << "Se cargaron " << logsOrdenados.size() << " logs desde "
                << archivoFuente << endl;
    }
}

void MenuInterface::busquedaPorIP() {
    string ip;
    cout << "Introduce la IP a buscar: ";
    cin >> ip;

    vector<LogManager> resultados = LogManager::buscarPorIP(logsOrdenados, ip);
    LogManager::mostrarResultados(resultados);
}

void MenuInterface::busquedaPorPuerto() {
    int puerto;
    cout << "Introduce el puerto a buscar: ";
    cin >> puerto;

    vector<LogManager> resultados = LogManager::buscarPorPuerto(logsOrdenados, puerto);
    LogManager::mostrarResultados(resultados);
}

void MenuInterface::busquedaPorFecha() {
    string mes;
    int dia;
    cout << "Introduce el mes (tres letras, ej. jan, feb): ";
    cin >> mes;
    cout << "Introduce el dia (numero): ";
    cin >> dia;

    vector<LogManager> resultados = LogManager::buscarPorFecha(logsOrdenados, mes, dia);
    LogManager::mostrarResultados(resultados);
}

void MenuInterface::busquedaPorMensaje() {
    string palabraClave;
    cout << "Introduce la palabra clave a buscar en los mensajes: ";
    cin.ignore(); // limpiar el buffer
    getline(cin, palabraClave);

    vector<LogManager> resultados = LogManager::buscarPorMensaje(logsOrdenados, palabraClave);
    LogManager::mostrarResultados(resultados);
}


