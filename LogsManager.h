//
// Created by Erick on 19/09/25.
//



#ifndef SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H
#define SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H

#include <string>
#include <vector>
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

    static vector<LogManager> cargarLogs(const string& archivo);
    static vector<LogManager> buscarPorIP(const vector<LogManager>& logs, const string& ip);
    static void guardarResultados(const vector<LogManager>& resultados, int numeroBusqueda, int numeroEquipo);

};

#endif // SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H