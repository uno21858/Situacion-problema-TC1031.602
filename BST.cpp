//
// Created by Erick on 09/11/25.
//

#include "BST.h"
using namespace std;

BST::BST() {
    raiz = nullptr;
}

BST::~BST() {
    liberarArbol(raiz);
    raiz = nullptr;
}

void BST::liberarArbol(NodoBST* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
}

void BST::actualizarNodo(NodoBST* nodo, const string& ip) {
    nodo->ips.push_back(ip);
}

NodoBST* BST::buscar(int frecuencia) {
    if (raiz == nullptr) {
        return nullptr;
    }

    NodoBST* actual = raiz;

    while (actual != nullptr) {
        if (frecuencia == actual->frecuencia) {
            return actual;
        }

        if (frecuencia < actual->frecuencia) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }

    return nullptr;
}

void BST::crearNodo(int frecuencia, const string& ip) {
    if (raiz == nullptr) {
        raiz = new NodoBST(frecuencia, ip);
        return;
    }

    NodoBST* actual = raiz;
    bool insertado = false;

    while (!insertado) {
        if (frecuencia < actual->frecuencia) {
            if (actual->izq == nullptr) {
                actual->izq = new NodoBST(frecuencia, ip);
                insertado = true;
            } else {
                actual = actual->izq;
            }
        } else {
            if (actual->der == nullptr) {
                actual->der = new NodoBST(frecuencia, ip);
                insertado = true;
            } else {
                actual = actual->der;
            }
        }
    }
}

void BST::recorridoInversoAux(NodoBST* nodo, vector<ResultadoTop>& resultado, int& contador, int N) {
    if (nodo == nullptr || contador >= N) {
        return;
    }

    recorridoInversoAux(nodo->der, resultado, contador, N);

    if (contador >= N) {
        return;
    }

    for (const string& ip : nodo->ips) {
        if (contador >= N) break;
        resultado.push_back({ip, nodo->frecuencia});
        contador++;
    }

    recorridoInversoAux(nodo->izq, resultado, contador, N);
}

vector<ResultadoTop> BST::obtenerTopN(int N) {
    vector<ResultadoTop> resultado;
    if (raiz == nullptr || N <= 0) {
        return resultado;
    }

    int contador = 0;
    recorridoInversoAux(raiz, resultado, contador, N);
    return resultado;
}