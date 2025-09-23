//
// Created by Erick on 19/09/25.
//


/*
 *  Lee los logs del txt.
 *  Seguido los vectoriza y crea otro txt con los logs vectorizados
 */

#ifndef SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H
#define SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H

#include <string>
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

    void mostrar();

    // funciopn que convierte el archivo normal al vectorizazdo de igual manera un txt
    static void generarArchivoVectorizado(const string& archivoOriginal, const string& archivoSalida = "logsRawVectorizado.txt");

    // Traduce meses y ordena por fecha con el traductor DN------
    static void traductor(const string& archivoEntrada, int numEquipo); // una función dentro de LogsManager que se llame "traductor".
};

#endif // SITUACION_PROBLEMA_TC1031_602_LOGSMANAGER_H