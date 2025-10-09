//
// Created by Erick on 19/09/25.
//



#ifndef SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H
#define SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H

#include <string>
#include "MyLinkedList.h"
using namespace std;

class LogManager {
private:
    string mes;
    int dia;
    string hora;
    string ip;
    int puerto;
    string mensaje;

public:
    LogManager() = default; // por defecto DN-------

    LogManager(const string& linea);

    // Poner los getter pa que saquen la info de los logs
    string getMes() const {return mes;}
    int getDia() const {return dia;}
    string getHora() const {return hora;}
    string getIP() const {return ip;}
    int getPuerto() const {return puerto;}
    string getMensaje() const {return mensaje;}

    // Comparar IPs jerárquicamente (###.###.###.###:puerto)
    bool compararPorIP(const LogManager& otro) const;

    static MyLinkedList<LogManager> cargarLogs(const string& archivo);
    static void guardarResultados(const MyLinkedList<LogManager>& resultados, int numeroBusqueda, int numeroEquipo);

    // Funciones para ordenamiento por IP usando lista enlazada
    static void ordenarPorIP(MyLinkedList<LogManager>& logs);
    static void guardarLogsOrdenadosIP(const MyLinkedList<LogManager>& logs, int numeroEquipo);
    static MyLinkedList<LogManager> buscarRangoIP(const MyLinkedList<LogManager>& logs, const string& ipInicio, const string& ipFin);

};

#endif // SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H