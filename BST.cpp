//
// Created by Erick on 09/11/25.
//

#include "BST.h"
using namespace std;

// como buscar en un BST, info tomada de https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/
// complejidad O(h) donde h es la altura del arbol
BST::BST() {
    raiz = nullptr;
}

// complejidad O(h) donde h es la altura del arbol
BST::~BST() {
    liberarArbol(raiz);
    raiz = nullptr;
}

// complejidad O(n) donde n es el número de nodos en el árbol
void BST::liberarArbol(NodoBST* nodo) {
    if (nodo == nullptr) {
        return;
    }
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    delete nodo;
}
// Actualizar nodo, info tomada de https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// complejidad O(1)
void BST::actualizarNodo(NodoBST* nodo, const string& ip) {
    nodo->ips.push_back(ip);
}

// Cómo buscar en un BST, info tomada de https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// complejidad O(h) donde h es la altura del arbol
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

// Cómo insertar en un BST, info tomada de https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// complejidad O(h) donde h es la altura del arbol
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

// Recorrido inverso para obtener top N, info tomada de https://www.geeksforgeeks.org/reverse-inorder-traversal-of-binary-tree/
// complejidad O(n) donde n es el número de nodos en el árbol
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

// complejidad O(n) donde n es el número de nodos en el árbol
vector<ResultadoTop> BST::obtenerTopN(int N) {
    vector<ResultadoTop> resultado;
    if (raiz == nullptr || N <= 0) {
        return resultado;
    }

    int contador = 0;
    recorridoInversoAux(raiz, resultado, contador, N);
    return resultado;
}