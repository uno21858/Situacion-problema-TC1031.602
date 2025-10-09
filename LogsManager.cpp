//
// Created by Erick on 19/09/25.
//

#include "LogsManager.h"

#include <fstream> //https://www.w3schools.com/cpp/ref_fstream_fstream.asp
#include <iostream>
#include <sstream> // https://www.geeksforgeeks.org/cpp/stringstream-c-applications/


using namespace std;

// O(1)
LogManager::LogManager(const string &linea) {
    stringstream ss(linea);
    ss>>mes>>dia>>hora;

    string ip_puerto;
    ss >> ip_puerto;

    size_t pos = ip_puerto.find(':');
    if (pos != string::npos) {
        ip = ip_puerto.substr(0, pos);
        puerto = stoi(ip_puerto.substr(pos + 1));
    } else {
        ip = ip_puerto;
        puerto = 0;
    }

    getline(ss, mensaje);
    if (!mensaje.empty() && mensaje[0] == ' ') {
        mensaje = mensaje.substr(1);
    }
}

// O(1) - Comparar IPs con jerarquia
// https://www.geeksforgeeks.org/c/scanf-and-fscanf-in-c/
bool LogManager::compararPorIP(const LogManager &otro) const {
    int octeto1, octeto2, octeto3, octeto4;
    int otroOcteto1, otroOcteto2, otroOcteto3, otroOcteto4;

    sscanf(ip.c_str(), "%d.%d.%d.%d", &octeto1, &octeto2, &octeto3, &octeto4);
    sscanf(otro.ip.c_str(), "%d.%d.%d.%d", &otroOcteto1, &otroOcteto2, &otroOcteto3, &otroOcteto4);

    if (octeto1 != otroOcteto1) return octeto1 < otroOcteto1;
    if (octeto2 != otroOcteto2) return octeto2 < otroOcteto2;
    if (octeto3 != otroOcteto3) return octeto3 < otroOcteto3;
    if (octeto4 != otroOcteto4) return octeto4 < otroOcteto4;

    return puerto < otro.puerto;
}


// Cargar logs desde un archivo usando linked list
// https://www.geeksforgeeks.org/data-structures/linked-list/
MyLinkedList<LogManager> LogManager::cargarLogs(const string &archivo) {
    MyLinkedList<LogManager> logs;
    ifstream entrada(archivo);
    if (!entrada.is_open()) {
        cout << "No se pudo abrir el archivo " << archivo << endl;
        return logs;
    }

    string linea;
    while (getline(entrada, linea)) {
        if (!linea.empty()) {
            LogManager log(linea);
            logs.insertLast(log);
        }
    }
    entrada.close();
    return logs;
}

// O(n) - Merge Sort
// https://www.programiz.com/dsa/merge-sort
void fusionarRegistros(MyLinkedList<LogManager>& registros, int inicio, int medio, int fin) {
    int tamanoIzquierda = medio - inicio + 1;
    int tamanoDerecha = fin - medio;

    MyLinkedList<LogManager> subarregloIzquierdo;
    MyLinkedList<LogManager> subarregloDerecho;

    // Copiar datos a las listas temporales
    MyNodoLL<LogManager>* current = registros.head;
    for (int i = 0; i < inicio; i++) {
        current = current->next;
    }

    for (int i = 0; i < tamanoIzquierda; ++i) {
        subarregloIzquierdo.insertLast(current->data);
        current = current->next;
    }
    for (int j = 0; j < tamanoDerecha; ++j) {
        subarregloDerecho.insertLast(current->data);
        current = current->next;
    }

    int indiceIzquierdo = 0, indiceDerecho = 0, indicePrincipal = inicio;

    current = registros.head;
    for (int i = 0; i < inicio; i++) {
        current = current->next;
    }

    while (indiceIzquierdo < tamanoIzquierda && indiceDerecho < tamanoDerecha) {
        if (subarregloIzquierdo.getAt(indiceIzquierdo).compararPorIP(subarregloDerecho.getAt(indiceDerecho))) {
            current->data = subarregloIzquierdo.getAt(indiceIzquierdo);
            ++indiceIzquierdo;
        } else {
            current->data = subarregloDerecho.getAt(indiceDerecho);
            ++indiceDerecho;
        }
        current = current->next;
        ++indicePrincipal;
    }

    while (indiceIzquierdo < tamanoIzquierda) {
        current->data = subarregloIzquierdo.getAt(indiceIzquierdo);
        ++indiceIzquierdo;
        current = current->next;
        ++indicePrincipal;
    }

    while (indiceDerecho < tamanoDerecha) {
        current->data = subarregloDerecho.getAt(indiceDerecho);
        ++indiceDerecho;
        current = current->next;
        ++indicePrincipal;
    }
}


// O(n log n) - Merge Sort iterativo
// https://www.geeksforgeeks.org/dsa/iterative-merge-sort/
void ordenarRegistrosPorIP(MyLinkedList<LogManager>& registros, int inicio, int fin) {
    int n = fin - inicio + 1;

    for (int tamano = 1; tamano < n; tamano *= 2) {
        for (int izquierda = inicio; izquierda <= fin; izquierda += 2 * tamano) {
            int medio = min(izquierda + tamano - 1, fin);
            int derecha = min(izquierda + 2 * tamano - 1, fin);

            if (medio < derecha) {
                fusionarRegistros(registros, izquierda, medio, derecha);
            }
        }
    }
}

void LogManager::ordenarPorIP(MyLinkedList<LogManager> &logs) {
    if (logs.isEmpty() || logs.length() <= 1) return;
    ordenarRegistrosPorIP(logs, 0, logs.length() - 1);
}


void LogManager::guardarLogsOrdenadosIP(const MyLinkedList<LogManager> &logs, int numeroEquipo) {
    string nombreArchivo = "bitacoraOrdenadaIP-Eq" + to_string(numeroEquipo) + ".txt";
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    MyNodoLL<LogManager>* current = logs.head;
    while (current != nullptr) {
        const LogManager& log = current->data;
        archivoSalida << log.getMes() << " "
                      << log.getDia() << " "
                      << log.getHora() << " "
                      << log.getIP() << ":"
                      << log.getPuerto() << " "
                      << log.getMensaje() << endl;
        current = current->next;
    }

    archivoSalida.close();
    cout << "Archivo ordenado por IP guardado: " << nombreArchivo << endl;
}

// O(n) - Buscar rango de IPs en la linked list
// https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
MyLinkedList<LogManager> LogManager::buscarRangoIP(const MyLinkedList<LogManager> &logs, const string &ipInicio, const string &ipFin) {
    MyLinkedList<LogManager> resultados;

    int inicio1 = 0, inicio2 = 0, inicio3 = 0, inicio4 = 0;
    int fin1 = 0, fin2 = 0, fin3 = 0, fin4 = 0;

    sscanf(ipInicio.c_str(), "%d.%d.%d.%d", &inicio1, &inicio2, &inicio3, &inicio4);
    sscanf(ipFin.c_str(), "%d.%d.%d.%d", &fin1, &fin2, &fin3, &fin4);

    if (ipFin.find('.') == string::npos) {
        fin2 = 255;
        fin3 = 255;
        fin4 = 255;
    }

    LogManager ipInicioTemp("Jun 1 00:00:00 " + to_string(inicio1) + "." + to_string(inicio2) + "." + to_string(inicio3) + "." + to_string(inicio4) + ":0 -");
    LogManager ipFinTemp("Jun 1 00:00:00 " + to_string(fin1) + "." + to_string(fin2) + "." + to_string(fin3) + "." + to_string(fin4) + ":0 -");

    MyNodoLL<LogManager>* current = logs.head;

    // Saltar IPs menores al inicio
    while (current != nullptr && current->data.compararPorIP(ipInicioTemp)) {
        current = current->next;
    }

    // Agregar IPs dentro del rango
    while (current != nullptr && (current->data.compararPorIP(ipFinTemp) || !ipFinTemp.compararPorIP(current->data))) {
        resultados.insertLast(current->data);
        current = current->next;
    }

    return resultados;
}

void LogManager::guardarResultados(const MyLinkedList<LogManager> &resultados, int numeroBusqueda, int numeroEquipo) {
    string nombreArchivo = "salida" + to_string(numeroBusqueda) + "-Eq" + to_string(numeroEquipo) + ".txt";
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    MyNodoLL<LogManager>* current = resultados.head;
    while (current != nullptr) {
        const LogManager& resultado = current->data;
        archivoSalida << resultado.getMes() << " "
                      << resultado.getDia() << " "
                      << resultado.getHora() << " "
                      << resultado.getIP() << ":"
                      << resultado.getPuerto() << " "
                      << resultado.getMensaje() << endl;
        current = current->next;
    }

    archivoSalida.close();
    cout << "Resultados guardados en: " << nombreArchivo << " (" << resultados.length() << " registros)" << endl;
}