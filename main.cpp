//
// Created by Erick on 18/09/25.
//

// main.cpp
#include "LogsManager.h"
#include <iostream>

/*
 *github https://github.com/uno21858/Situacion-problema-TC1031.602/tree/Linked_Lists
 */


int main() {
    const int NUMERO_EQUIPO = 4;
    int contadorBusquedas = 0;

    // 1. Car gar logs del archivo
    cout << "Cargando logs desde bitacora.txt..." << endl;
    MyLinkedList<LogManager> logsOrdenados = LogManager::cargarLogs("bitacora.txt");
    cout << "Logs cargados: " << logsOrdenados.length() << " registros" << endl;

    // 2. Ordenar por IP
    cout << "Ordenando logs por IP..." << endl;
    LogManager::ordenarPorIP(logsOrdenados);

    // 3. Guardar archivo ordenado
    LogManager::guardarLogsOrdenadosIP(logsOrdenados, NUMERO_EQUIPO);
    cout << "Listo\n" << endl;

    // 4. Ciclo de búsquedas
    char respuesta = 's';
    while (respuesta == 's' || respuesta == 'S') {
        string ipInicio, ipFin;

        // Solicitar IPs
        cout << "Ingrese IP inicial: ";
        cin >> ipInicio;
        cout << "Ingrese IP final: ";
        cin >> ipFin;

        // Buscar rango
        MyLinkedList<LogManager> resultados = LogManager::buscarRangoIP(logsOrdenados, ipInicio, ipFin);

        // Guardar resultados
        contadorBusquedas++;
        LogManager::guardarResultados(resultados, contadorBusquedas, NUMERO_EQUIPO);

        cout << "\nResultados guardados (" << resultados.length() << " registros)" << endl;

        // Preguntar si continuar
        cout << "\nDesea realizar otra busqueda? (s/n): ";
        cin >> respuesta;
        cout << endl;
    }

    cout << "Programa finalizado." << endl;
    return 0;
}