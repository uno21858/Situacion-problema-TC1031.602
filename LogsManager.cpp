//
// Created by Erick on 19/09/25.
//

#include "LogsManager.h"

#include <fstream> //https://www.w3schools.com/cpp/ref_fstream_fstream.asp
#include <iostream>
#include <sstream> // https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
using namespace std;


LogManager::LogManager(const string &linea) {

    stringstream ss(linea);
    ss>>mes>>dia>>hora;

    string ip_puerto;
    ss >> ip_puerto;

    // Para separar la ip yu el puerto
    size_t pos = ip_puerto.find(':');
    ip = ip_puerto.substr(0, pos);
    puerto = stoi(ip_puerto.substr(pos + 1));

    // Tod el mensaje del error del log
    getline(ss, mensaje);
    if (!mensaje.empty() && mensaje[0] == ' ') {
        mensaje = mensaje.substr(1); // Quita el espacio inicial
    }
}

void LogManager::generarArchivoVectorizado(const string &archivoOriginal, const string &archivoSalida) {
    ifstream entrada(archivoOriginal);
    // Debugg: borrar despues
    if (!entrada.is_open()) {
        cout<< "No se puedo abrir el archivo " << archivoOriginal<< endl;
        return;
    }


    ofstream salida(archivoSalida);
    // Debug: borrar despues
    if (!salida.is_open()) {
        cout << "No se pudo crear el archivo " << archivoSalida << endl;
        return;
    }

    string linea;

    cout << "Haciendo los logs a vector" << endl;

    int contador {0};

    while (getline(entrada, linea)) { // lee linea por linae
        if (!linea.empty()) {
cout << "Linea " << contador++ << ": " << linea.substr(0,5);

            LogManager log(linea);

            salida << log.getMes() << " "
                   << log.getDia() << " "
                   << log.getHora() << " "
                   << log.getIP() << " "
                   << log.getPuerto() << " "
                   << log.getMensaje() << std::endl;
        }
    }
    cout << "Se creo el archivo vectorizado: " << archivoSalida << endl;
}


void LogManager::mostrar() {
    cout << mes<<" " << dia << " " << hora << " " << ip << " " << puerto << " " << mensaje << endl;
}

