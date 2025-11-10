//
// Created by Erick on 09/11/25.
//

#include "BST.h"
using namespace std;

BST::BST() {
    raiz = nullptr;
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
    // Si ta vacio el arbol
    if (raiz == nullptr) {
        raiz = new NodoBST(frecuencia, ip);
        return;
    }

    // Buscar un lugar
    NodoBST* actual = raiz;

    while (true) {
        if (frecuencia < actual->frecuencia) {
            if (actual->izq == nullptr) {
                actual->izq = new NodoBST(frecuencia, ip);
                return;
            } else {
                actual = actual->izq;
            }
        } else {
            if (actual->der == nullptr) {
                actual->der = new NodoBST(frecuencia, ip);
                return;
            } else {
                actual = actual->der;
            }
        }
    }
}

