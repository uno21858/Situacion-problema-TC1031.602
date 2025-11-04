//
// Created by Erick on 04/11/2025.
//

#ifndef SITUACION_PROBLEMA_TC1031_602_BST_H
#define SITUACION_PROBLEMA_TC1031_602_BST_H

#include <string>
#include <vector>
using namespace std;

// Nodo del BST
class NodoBST {
public:
    int frecuencia;
    vector<string> ips;
    NodoBST* izq;
    NodoBST* der;

    NodoBST(int freq, const string& ip) {
        frecuencia = freq;
        ips.push_back(ip);
        izq = nullptr;
        der = nullptr;
    }
};

// Estructura para retornar resultados
struct ResultadoTop {
    string ip;
    int frecuencia;
};


// Árbol BST
class BST {
private:
    NodoBST* raiz;
    void recorridoInversoAux(NodoBST* nodo, vector<ResultadoTop>& resultado, int& contador, int N);

public:
    BST();
    ~BST();

    NodoBST* buscar(int frecuencia);
    void actualizarNodo(NodoBST* nodo, const string& ip);
    void crearNodo(int frecuencia, const string& ip);
    vector<ResultadoTop> obtenerTopN(int N);
};

#endif //SITUACION_PROBLEMA_TC1031_602_BST_H