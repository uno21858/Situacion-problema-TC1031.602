//
// Created by Erick on 18/09/25.
// main.cpp

#include "LogsManager.h"
#include "HashTable.h"
#include "BST.h"
#include <iostream>
#include <vector>

/*
 *github https://github.com/uno21858/Situacion-problema-TC1031.602/tree/BST
 */


int main() {
    const int NUMERO_EQUIPO = 4;
    int contadorBusquedas = 0;

    // 1. Cargar logs del archivo
    cout << "Cargando logs desde bitacora3.txt..." << endl;
    MyLinkedList<LogManager> logsOrdenados = LogManager::cargarLogs("bitacora3.txt");
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


    // MyHashTable ---------------------
    cout << "\nConstruyendo tabla hash para resumen de IPs..." <<endl; //------------------
    MyHashTable tablaIPs;//------------------
    //------------------
    MyNodoLL<LogManager>* current = logsOrdenados.head; //------------------
    while (current != nullptr) { //------------------
        const LogManager& log = current->data; //------------------
        std::string ip_sin_puerto = log.getIPSinPuerto(); // getter de LogManager //------------------
        //------------------
        FechaHora fh; //------------------
        fh.mes = log.getMes(); //------------------
        fh.dia = log.getDia(); //------------------
        fh.hora = log.getHora(); //------------------
        //------------------
        //  MyHashTable para agregar el registro //------------------
        tablaIPs.put(ip_sin_puerto, fh); //------------------
        //------------------
        current = current->next; //------------------
    } //------------------
    std::cout << "Tabla hash construida." << std::endl; //------------------
    // ------------------


    // ---------------------
    std::cout << "\n--- Consulta de informacion por IP ---" << std::endl; //------------------
    int consultarOtraIP = 1; //------------------
    while (consultarOtraIP == 1) { //------------------
        std::string ip_a_buscar; //------------------
        std::cout << "Ingrese la IP (sin puerto) a consultar: "; //------------------
        std::cin >> ip_a_buscar; //------------------
        //------------------
        //MyHashTable para buscar------------------
        ListaFechaHora* fechas_hora_lista = tablaIPs.get(ip_a_buscar); //------------------
        //------------------
        if (fechas_hora_lista != nullptr) { //------------------
            //------------------
            std::cout << ip_a_buscar << std::endl;//IP------------------
            MyNodoLL<FechaHora>* current_fh = fechas_hora_lista->head; //------------------
            while (current_fh != nullptr) { //------------------
                const FechaHora& fh = current_fh->data; //------------------
                // Imprime mes, dia, hora (como pide el ejemplo de salida) //------------------
                std::cout << fh.mes << " " << fh.dia << " " << fh.hora << std::endl; //------------------
                current_fh = current_fh->next; //------------------
            } //------------------
        } else { //------------------
            // un mensaje o dejarlo vacio //------------------
            std::cout << "IP " << ip_a_buscar << " no encontrada en la bitacora." << std::endl; //------------------
        } //------------------
        //------------------
        std::cout << "\n¿Desea consultar otra IP? (1 para si, 0 para no): "; //------------------
        std::cin >> consultarOtraIP; //------------------
    } //------------------
    //------------------

cout << "Programa finalizado." << endl;
    return 0;
}
