//
// Created by Erick on 19/09/25.
//

#include "LogsManager.h"

#include <fstream> //https://www.w3schools.com/cpp/ref_fstream_fstream.asp
#include <iostream>
#include <sstream> // https://www.geeksforgeeks.org/cpp/stringstream-c-applications/
#include <algorithm>//https://cplusplus.com/reference/algorithm/ DN------
#include <vector> //DN-------
#include <cctype>//https://cplusplus.com/reference/cctype/ DN------


using namespace std;

// O(1)
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

// Cargar logs desde un archivo 
vector<LogManager> LogManager::cargarLogs(const string &archivo) {
    vector<LogManager> logs;
    ifstream entrada(archivo);
    if (!entrada.is_open()) { // aqui si no existe el archivo
        cout << "No se pudo abrir el archivo " << archivo << endl;
        return logs;
    }

    string linea; // para leer linea por linea
    while (getline(entrada, linea)) {
        if (!linea.empty()) { // evitar lineas vacias
            LogManager log(linea);
            logs.push_back(log);
        }
    }
    entrada.close(); // cerrar el archivo
    return logs;
}


//guarda resultados en archivo salidaN-eq#.txt
//D1
void LogManager::guardarResultados(const vector<LogManager> &resultados, int numeroBusqueda, int numeroEquipo) {
    string nombreArchivo = "salida" + to_string(numeroBusqueda) + "-eq" + to_string(numeroEquipo) + ".txt";

    ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida.is_open()) {
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    // Guardar en formato original (igual que el archivo origen, namas q ps ordenado)
    for (const auto& resultado : resultados) {
        archivoSalida << resultado.getMes() << " "
                      << resultado.getDia() << " "
                      << resultado.getHora() << " "
                      << resultado.getIP() << ":"
                      << resultado.getPuerto() << " "
                      << resultado.getMensaje() << endl;
    }

    archivoSalida.close();
    cout << "Resultados guardados en: " << nombreArchivo << " (" << resultados.size() << " registros)" << endl;
}
