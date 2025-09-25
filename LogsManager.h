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



    // Traduce meses y ordena por fecha con el traductor DN------
    static void genArchivoOrdenado(const string& archivoEntrada, int numEquipo); // una función dentro de LogsManager

    static vector<LogManager> buscarPorFecha(const vector<LogManager>& logs, const string& mes, int dia);
    static vector<LogManager> buscarPorRangoFecha(const vector<LogManager>& logs,
                                                   const string& mesInicio, int diaInicio,
                                                   const string& mesFin, int diaFin);


    // funciones de búsqueda  extra (osea ahorita no se necedutan pero a futuro si)

    static vector<LogManager> cargarLogs(const string& archivo);            // Carga un archivo de bitácora a memoria
    static vector<LogManager> buscarPorIP(const vector<LogManager>& logs, const string& ip);
    static vector<LogManager> buscarPorPuerto(const vector<LogManager>& logs, int puerto);
    static vector<LogManager> buscarPorMensaje(const vector<LogManager>& logs, const string& palabraClave);
    static void mostrarResultados(const vector<LogManager>& resultados);

    //D1
    static void guardarResultados(const vector<LogManager>& resultados, int numeroBusqueda, int numeroEquipo);

};

#endif // SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H