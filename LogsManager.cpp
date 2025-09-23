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
//cout << "Linea " << contador++ << ": " << linea.substr(0,5); LO PUSE COMENTADO PARA VER MEJOR LA CONSOLA DN------

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


//Convertir todo a lowercase para evitar problemas con mayúsculas DN-----
string convertirAMinusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

// Array con nombres de meses en minúsculas puse todos pero creo que solo se ocupan como 4 pero pues aja DN----------
const string NOMBRES_MESES[13] = {
    "", "jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};

// Convertir los meses de string a número: Ene→1, Feb→2, etc. DN -------
int convertirMesANumero(const string& nombreMes) {
    string nombreMesMinusculas = convertirAMinusculas(nombreMes);
    for (int numeroMes = 1; numeroMes <= 12; ++numeroMes) {
        if (nombreMesMinusculas == NOMBRES_MESES[numeroMes]) {
            return numeroMes;
        }
    }
    return 0;
}

//comparar por fecha DN------
bool operator<(const LogManager& logIzquierdo, const LogManager& logDerecho) {
    int mesLogIzq = convertirMesANumero(logIzquierdo.getMes());
    int mesLogDer = convertirMesANumero(logDerecho.getMes());

    if (mesLogIzq != mesLogDer) return mesLogIzq < mesLogDer;// Primero ve el mes
    if (logIzquierdo.getDia() != logDerecho.getDia()) return logIzquierdo.getDia() < logDerecho.getDia(); // luego ve el dia
    return logIzquierdo.getHora() < logDerecho.getHora(); // al final la hora
}

// Fusion para usar merge sort DN-------
void fusionarRegistros(vector<LogManager>& registros, int inicio, int medio, int fin) {
    int tamanoIzquierda = medio - inicio + 1;
    int tamanoDerecha = fin - medio;

    vector<LogManager> subarregloIzquierdo(tamanoIzquierda);
    vector<LogManager> subarregloDerecho(tamanoDerecha);

    for (int i = 0; i < tamanoIzquierda; ++i) {
        subarregloIzquierdo[i] = registros[inicio + i];
    }
    for (int j = 0; j < tamanoDerecha; ++j) {
        subarregloDerecho[j] = registros[medio + 1 + j];
    }

    int indiceIzquierdo = 0, indiceDerecho = 0, indicePrincipal = inicio;

    while (indiceIzquierdo < tamanoIzquierda && indiceDerecho < tamanoDerecha) {
        if (subarregloIzquierdo[indiceIzquierdo] < subarregloDerecho[indiceDerecho]) {
            registros[indicePrincipal] = subarregloIzquierdo[indiceIzquierdo];
            ++indiceIzquierdo;
        } else {
            registros[indicePrincipal] = subarregloDerecho[indiceDerecho];
            ++indiceDerecho;
        }
        ++indicePrincipal;
    }

    while (indiceIzquierdo < tamanoIzquierda) {
        registros[indicePrincipal] = subarregloIzquierdo[indiceIzquierdo];
        ++indiceIzquierdo;
        ++indicePrincipal;
    }

    while (indiceDerecho < tamanoDerecha) {
        registros[indicePrincipal] = subarregloDerecho[indiceDerecho];
        ++indiceDerecho;
        ++indicePrincipal;
    }
}

// Merge Sort pero interativo mi compu no lo aguanto recursivo https://interviewkickstart.com/blogs/learn/iterative-merge-sort de ahi lo saque DN-------
void ordenarRegistrosPorFecha(vector<LogManager>& registros, int inicio, int fin) {
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

//  lee ordena y guarda con el traductor DN------
void LogManager::traductor(const string& rutaArchivoEntrada, int numeroEquipo) {
    ifstream archivoEntrada(rutaArchivoEntrada);
    if (!archivoEntrada.is_open()) {
        cout << "pusiste la ruta mal otra vez " << rutaArchivoEntrada << endl;
        return;
    }

    vector<LogManager> registrosBitacora;
    string lineaLeida;

    //cout << "ordenando " << endl; nomas era para vwer si servia igual lo dejo para futuras pruebas DN------------
    while (getline(archivoEntrada, lineaLeida)) {
        if (!lineaLeida.empty()) {
            LogManager registroActual(lineaLeida);
            registrosBitacora.push_back(registroActual);
        }
    }
    archivoEntrada.close(); //se cierra el boitacora.txt

   // cout << "Ordenando por fecha " << registrosBitacora.size() << endl; iagual esta es provicional se deja para futuras pruebas DN----------------
    ordenarRegistrosPorFecha(registrosBitacora, 0, registrosBitacora.size() - 1);

    string nombreArchivoSalida = "bitacoraOrdenada" + to_string(numeroEquipo) + ".txt";
    ofstream archivoSalida(nombreArchivoSalida);

    if (!archivoSalida.is_open()) {
        cout << "algo hiciste mal " << nombreArchivoSalida << endl;
        return;
    }

    for (const auto& registro : registrosBitacora) { //igual que el del vectores del erick pero para el orden
        archivoSalida << registro.getMes() << " "
                      << registro.getDia() << " "
                      << registro.getHora() << " "
                      << registro.getIP() << ":"
                      << registro.getPuerto() << " "
                      << registro.getMensaje() << endl;
    }

    archivoSalida.close();
    cout << "Todo bien c: " << nombreArchivoSalida << endl; //Se termina y se guarda
}