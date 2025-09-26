//
// Created by Erick on 18/09/25.
//

#include "MenuInterface.h"
#include "LogsManager.h"
#include <iostream>
using namespace std;


MenuInterface::MenuInterface() {
    // Borra la basura que se tiene en la terminal
    clearScreen();

    // Cargar los logs ordenados al crear el menu
    logsOrdenados = LogManager::cargarLogs("bitacoraOrdenada3.txt");
    cout << "Logs cargados: " << logsOrdenados.size() << " registros" << endl;

}

// Google Search (Respuesta rapida de la IA del navegador)
void MenuInterface::clearScreen() {
#ifdef _WIN32 // Check if compiling on Windows
    system("cls");
#else // Assume Unix-based system otherwise
    system("clear");
#endif
}



// Funcion que solamente me muestra las opciones de busqueda de los logs D1
void MenuInterface::mostrarOpciones() {
    cout<<"\n============== Selecciona la manera en la que se seleccionaran los logs ============== "<< endl;
    //cout << "1. Buscar por fecha especifica" << endl;
    cout << "1. Buscar por rango de fechas" << endl;
    cout << "2. Salir" << endl;
}


// Lee las opciones del menu. D1
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

// Validadores de Dias y meses D1
int MenuInterface::validarDia(int dia) {
    if (dia >= 1 && dia <= 31) {
        return dia;
    } else {
        cout << "El dia está fuera de rango (1-31)" << endl;
        return -1;
    }
}

// D1
string MenuInterface::validarMes(string mes) {
    // Convertir mes en minuscula pd: por no saber como hacer eso en un code assigment lo saque mal XD
    for (char& c : mes) {
        c = tolower(c);
    }

    const string mesesValidos[] = {"jan", "feb", "mar", "apr", "may", "jun",
                                   "jul", "aug", "sep", "oct", "nov", "dec"};



    for (int i = 0; i < 12; i++) {
        if (mes == mesesValidos[i]) {
            return mes;
        }
    }

    cout << "Mes inválido. Use formato como 'Jan', 'Feb', etc." << endl;
    return "";
}



// Funcion que manda a lo que debe de hacer seggun se haya escogido D1
//TODO: en un futuro. separar por opcion de filtrado. esta nomas es de fechas, pero pa ip puerto y demas ps. hacer un menu del menu

void MenuInterface::hacerBusqueda(int opcion) {
    switch (opcion) {
      /*
        case 1: {
            // Busqueda por fecha especifica
            string mes;
            int dia;

            cout << "\n=== Buscar por fecha especifica ===" << endl;

            // Validar entrada con loop hasta que sea correcta
            do {
                cout << "Ingresa el mes y dia separado por un espacio (ej: Sep 11): ";
                cin >> mes >> dia;

                mes = validarMes(mes);
                if (mes.empty()) {
                    continue;
                }

                dia = validarDia(dia);
                if (dia == -1) {
                    continue;
                }
                break;
            } while (true);

            vector<LogManager> resultados = LogManager::buscarPorFecha(logsOrdenados, mes, dia);

            contadorBusquedas++;
            LogManager::guardarResultados(resultados, contadorBusquedas, NUMERO_EQUIPO);

            //modo interactivo
            cout<<"\nPreciona enter para continuar";
            cin.ignore(10000, '\n');
            cin.get();
            clearScreen();

            break;
        }
    */
        case 1: {
            // Busqueda por rango de fechas
            string mesInicio, mesFin;
            int diaInicio, diaFin;

            cout << "\n=== Buscar por rango de fechas ===" << endl;

            // Validar fecha de inicio
            do {
                cout << "Fecha de inicio:" << endl;
                cout << "Mes y dia de inicio (ej: Sep 11): ";
                cin >> mesInicio >> diaInicio;

                mesInicio = validarMes(mesInicio);
                if (mesInicio.empty()) {
                    continue;
                }

                diaInicio = validarDia(diaInicio);
                if (diaInicio == -1) {
                    continue;
                }

                break;
            } while (true);

            // Validar fecha de fin
            do {
                cout << "Fecha de fin:" << endl;
                cout << "Mes y dia final (ej: Oct 5): ";
                cin >> mesFin >> diaFin;

                mesFin = validarMes(mesFin);
                if (mesFin.empty()) {
                    continue;
                }

                diaFin = validarDia(diaFin);
                if (diaFin == -1) {
                    continue;
                }
                break;

            } while (true);

            vector<LogManager> resultados = LogManager::buscarPorRangoFecha(logsOrdenados, mesInicio, diaInicio, mesFin, diaFin);

            contadorBusquedas++;
            LogManager::guardarResultados(resultados, contadorBusquedas, NUMERO_EQUIPO);

            // modo interacitvo
            // cout<<"\nPreciona enter para continuar";
            // cin.ignore(10000, '\n');
            // cin.get();
            // clearScreen();

            break;
        }
        default:
            cout << "Adios :3" << endl;
            break;
    }
}

/* Swithch original
*void MenuInterface::hacerBusqueda(int opcion) {
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

*/



// FLujo de como se debde de ejecutar lo de la interfaz del menu
void MenuInterface::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        opcion = leerOpcion(1,2);
        hacerBusqueda(opcion);

    } while (opcion != 2);
}