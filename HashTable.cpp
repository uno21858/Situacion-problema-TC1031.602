#include "HashTable.h"
#include <iostream>
using namespace std;

// los datos se toman de bitacora3.txt
MyHashTable::MyHashTable() {
    this->sizeA = 97; // tamaño inicial de la tabla hash
    this->size = 0; // número de elementos en la tabla hash
    this->table = new MyLinkedList<string>[sizeA]; // arreglo de listas enlazadas
}

MyHashTable::~MyHashTable() {
    for (int i = 0; i < sizeA; i++) { // para i de 0 a sizeA
        while (!table[i].isEmpty()) { // mientras la lista enlazada en la posición i no esté vacía
            table[i].removeFirst(); // eliminar el primer elemento de la lista enlazada en la posición i
        }
    }
    delete[] table; // liberar memoria del arreglo de listas enlazadas
}

bool MyHashTable::isEmpty() {
    return this -> size == 0; // si la tabla está vacía
}
