//
// Created by Erick on 19/09/25.
//

#include "LogsManager.h"

#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

// Declaraciones de funciones auxiliares para merge sort
MyNodoLL<LogManager>* obtenerMitad(MyNodoLL<LogManager>* cabeza);
MyNodoLL<LogManager>* mezclarDosListas(MyNodoLL<LogManager>* izquierda, MyNodoLL<LogManager>* derecha);
MyNodoLL<LogManager>* mergeSortRecursivo(MyNodoLL<LogManager>* cabeza);


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


// Encontrar el nodo del medio usando tecnica tortuga conejo
// ME insipire en el Leetcode # 141 142 y otros
MyNodoLL<LogManager>* obtenerMitad(MyNodoLL<LogManager>* cabeza) {
    if (cabeza == nullptr) return nullptr;

    MyNodoLL<LogManager>* lento = cabeza; // tortuga: este solamente avanza 1
    MyNodoLL<LogManager>* rapido = cabeza->next; //conejo: avanza 1 mas q la tortuga


    while (rapido != nullptr && rapido->next != nullptr) {
        lento = lento->next;
        rapido = rapido->next->next;
    }

    return lento;
}

// Mezcla dos listas ordenadas en una sola **Garcias Lepe**
MyNodoLL<LogManager>* mezclarDosListas(MyNodoLL<LogManager>* izquierda,
                                       MyNodoLL<LogManager>* derecha) {
    if (izquierda == nullptr) return derecha;
    if (derecha == nullptr) return izquierda;

    MyNodoLL<LogManager>* resultado = nullptr;

    if (izquierda->data.compararPorIP(derecha->data)) {
        resultado = izquierda;
        resultado->next = mezclarDosListas(izquierda->next, derecha);
    } else {
        resultado = derecha;
        resultado->next = mezclarDosListas(izquierda, derecha->next);
    }

    return resultado;
}

MyNodoLL<LogManager>* mergeSortRecursivo(MyNodoLL<LogManager>* cabeza) {
    if (cabeza == nullptr || cabeza->next == nullptr) {
        return cabeza;
    }

    MyNodoLL<LogManager>* mitad = obtenerMitad(cabeza);
    MyNodoLL<LogManager>* siguienteDeMitad = mitad->next;
    mitad->next = nullptr;

    MyNodoLL<LogManager>* izquierdaOrdenada = mergeSortRecursivo(cabeza);
    MyNodoLL<LogManager>* derechaOrdenada = mergeSortRecursivo(siguienteDeMitad);

    return mezclarDosListas(izquierdaOrdenada, derechaOrdenada);
}


void LogManager::ordenarPorIP(MyLinkedList<LogManager>& logs) {
    if (logs.isEmpty() || logs.length() <= 1) return;

    logs.head = mergeSortRecursivo(logs.head);

    // Actualizar tail
    MyNodoLL<LogManager>* actual = logs.head;
    while (actual->next != nullptr) {
        actual = actual->next;
    }
    logs.tail = actual;
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
    LogManager ipFinTemp("Jun 1 00:00:00 " + to_string(fin1) + "." + to_string(fin2) + "." + to_string(fin3) + "." + to_string(fin4) + ":65535 -");

    MyNodoLL<LogManager>* current = logs.head;

    // Saltar IPs menores al inicio
    while (current != nullptr && current->data.compararPorIP(ipInicioTemp)) {
        current = current->next;
    }

    // Agregar registros mientras estén dentro del rango
    while (current != nullptr && !ipFinTemp.compararPorIP(current->data)) {
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
