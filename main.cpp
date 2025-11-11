//
// Created by Erick on 18/09/25.
//

// main.cpp
#include "LogsManager.h"
#include "BST.h"
#include <iostream>
#include <vector>

/*
 *github https://github.com/uno21858/Situacion-problema-TC1031.602/tree/BST
 */


int main() {
    const int NUMERO_EQUIPO = 4;
    int contadorBusquedas = 0;

    // 1. Car gar logs del archivo
    cout << "Cargando logs desde bitacora2.txt..." << endl;
    MyLinkedList<LogManager> logsOrdenados = LogManager::cargarLogs("bitacora2.txt");
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

    // pueden borrar mis comentarios mas tarde si quieren, es mi guía por mientras
    // aqui se implementan los logs ordenados por BST
    cout << "Construyendo BST para analisis de frecuencias..." << endl;

    BST bst;

    if (logsOrdenados.length() > 0) {
        string ipActual = logsOrdenados.getAt(0).getIP(); 
        int frecuencia = 1; // para empezar 

        for (int i = 1; i < logsOrdenados.length(); ++i) {
            string ip = logsOrdenados.getAt(i).getIP(); // 
            if (ip == ipActual) {
                ++frecuencia; // misma IP, incrementar frecuencia
            } else {
                // prueba para ver que se insertan bien
                cout << "Insertando IP: " << ipActual
                 << " con frecuencia: " << frecuencia << endl;
                // borrar después si es necesario

                NodoBST* nodo = bst.buscar(frecuencia); 
                if (nodo != nullptr) {
                    bst.actualizarNodo(nodo, ipActual);
                } else {
                    bst.crearNodo(frecuencia, ipActual);
                }
                ipActual = ip; // awui se cambia de ip, se reinicia
                frecuencia = 1;
            }
        }
        cout << "Insertando IP: " << ipActual
         << " con frecuencia: " << frecuencia << endl;

        NodoBST* nodo = bst.buscar(frecuencia);
        if (nodo != nullptr) {
            bst.actualizarNodo(nodo, ipActual);
        } else {
            bst.crearNodo(frecuencia, ipActual);
        }
    }

    cout << "\nTop 5 IPs con mas accesos." << endl;

    const int TOP_N = 5;


    vector<ResultadoTop> topIPs = bst.obtenerTopN(TOP_N);

    cout << "\n=== Top " << TOP_N << " IPs con mas accesos ===" << endl;
    for (const ResultadoTop& resultado : topIPs) {
        cout << resultado.ip << "\n" << endl;
        cout << resultado.frecuencia << "\n" << endl;
    }

    cout << "Programa finalizado." << endl;

cout << "Programa finalizado." << endl;
    return 0;
}
