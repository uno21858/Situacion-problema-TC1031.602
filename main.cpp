//
// Created by Erick on 18/09/25.
//

// main.cpp
#include "LogsManager.h"
#include "HashTable.h"
#include <iostream>

using namespace std;

/*
 * github https://github.com/uno21858/Situacion-problema-TC1031.602/tree/Hash
 */

int main() {
    // 1. Cargar logs del archivo
    cout << "Cargando logs desde bitacora3.txt..." << endl;
    MyLinkedList<LogManager> logs = LogManager::cargarLogs("bitacora3.txt");
    cout << "Logs cargados: " << logs.length() << " registros\n" << endl;

    // 2. Construir tabla hash para resumen de IPs
    cout << "Construyendo tabla hash para resumen de IPs..." << endl; //------------------
    MyHashTable tablaIPs; //------------------
    //------------------
    MyNodoLL<LogManager>* current = logs.head; //------------------
    while (current != nullptr) { //------------------
        const LogManager& log = current->data; //------------------
        string ip_sin_puerto = log.getIPSinPuerto(); // getter de LogManager //------------------
        //------------------
        // Crear estructura FechaHora //------------------
        FechaHora fh; //------------------
        fh.mes = log.getMes(); //------------------
        fh.dia = log.getDia(); //------------------
        fh.hora = log.getHora(); //------------------
        fh.puerto = log.getPuerto(); //------------------
        fh.mensaje = log.getMensaje(); //------------------
        //------------------
        // Agregar a la tabla hash (se insertará en orden cronológico) //------------------
        tablaIPs.put(ip_sin_puerto, fh); //------------------
        //------------------
        current = current->next; //------------------
    } //------------------
    cout << "Tabla hash construida con " << tablaIPs.getSize() << " IPs unicas.\n" << endl; //------------------
    //------------------

    // 3. Ciclo de consultas //------------------
    cout << "--- Consulta de informacion por IP ---" << endl; //------------------
    int consultarOtraIP = 1; //------------------
    //------------------
    while (consultarOtraIP == 1) { //------------------
        string ip_a_buscar; //------------------
        cout << "Ingrese la IP (sin puerto) a consultar: "; //------------------
        cin >> ip_a_buscar; //------------------
        //------------------
        // Buscar en la tabla hash usando get() //------------------
        ListaFechaHora* fechas_hora_lista = tablaIPs.get(ip_a_buscar); //------------------
        //------------------
        if (fechas_hora_lista != nullptr) { //------------------
            // Imprimir IP //------------------
            cout << ip_a_buscar << endl; //------------------
            //------------------
            // Imprimir fechas en orden cronológico //------------------
            MyNodoLL<FechaHora>* current_fh = fechas_hora_lista->head; //------------------
            while (current_fh != nullptr) { //------------------
                const FechaHora& fh = current_fh->data; //------------------
                // Imprime mes, dia, hora (como pide el ejemplo de salida) //------------------
                cout << fh.mes << " " << fh.dia << " " << fh.hora << endl; //------------------
                current_fh = current_fh->next; //------------------
            } //------------------
        } else { //------------------
            cout << "IP " << ip_a_buscar << " no encontrada en la bitacora." << endl; //------------------
        } //------------------
        //------------------
        cout << "\n¿Desea consultar otra IP? (1 para si, 0 para no): "; //------------------
        cin >> consultarOtraIP; //------------------
        cout << endl; //------------------
    } //------------------
    //------------------

    cout << "Programa finalizado." << endl;
    return 0;
}