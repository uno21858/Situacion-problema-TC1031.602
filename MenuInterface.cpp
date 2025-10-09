//
// Created by Erick on 18/09/25.
//
/*
 * MEjor lo simplifique. pues es mas facil asi de leer y ps weno.
 * Si me pase un poco la version pasada
 */

#include "MenuInterface.h"
#include "LogsManager.h"
#include <iostream>
using namespace std;

MenuInterface::MenuInterface() {
    logsOrdenados = LogManager::cargarLogs("bitacora.txt");
    cout << "Logs cargados: " << logsOrdenados.length() << " registros" << endl;
    LogManager::ordenarPorIP(logsOrdenados);

    LogManager::guardarLogsOrdenadosIP(logsOrdenados, NUMERO_EQUIPO);
    cout << "Listo\n" << endl;
}

void MenuInterface::ejecutar() {
    char respuesta = 's';

     do {
        string ipInicio, ipFin;

        cout << "Ingrese IP inicial: ";
        cin >> ipInicio;
        cout << "Ingrese IP final: ";
        cin >> ipFin;

        MyLinkedList<LogManager> resultados = LogManager::buscarRangoIP(logsOrdenados, ipInicio, ipFin);

        cout << "\n=== Resultados (" << resultados.length() << " registros) ===" << endl;

        contadorBusquedas++;
        LogManager::guardarResultados(resultados, contadorBusquedas, NUMERO_EQUIPO);

        cout << "\nDesea realizar otra busqueda? (s/n): ";
        cin >> respuesta;
    } while (respuesta == 's' || respuesta == 'S');

    cout << "Adios :3" << endl;
}