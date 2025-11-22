#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <cstddef>

using namespace std;

// los datos se toman de bitacora3.txt
MyHashTable::MyHashTable() {
    this->sizeA = 11; // tamaño inicial de la tabla hash
    this->size = 0; // número de elementos en la tabla hash
    this->table = new ListaIPEntry[sizeA];  // Array de listas de IPEntry
}

MyHashTable::~MyHashTable() {
    for (int i = 0; i < sizeA; i++) {
    }
    delete[] table; // liberar memoria del arreglo de listas enlazadas
}


void MyHashTable::put(const string& ip, const FechaHora& fechaHora) {
    int pos = getPos(ip);

    // Buscar si la IP ya existe en esta posición (manejar colisiones)
    MyNodoLL<IPEntry>* current = table[pos].head;
    while (current != nullptr) {
        if (current->data.ip == ip) {
            // IP encontrada, agregar la fecha a su lista
            current->data.fechas.insertLast(fechaHora);
            this->size++;
            return;
        }
        current = current->next;
    }

    // IP no encontrada, crear nueva entrada
    IPEntry nuevaEntrada;
    nuevaEntrada.ip = ip;
    nuevaEntrada.fechas.insertLast(fechaHora);
    table[pos].insertLast(nuevaEntrada);
    this->size++;
} 

// la lista de FechaHora asociadas a una IP
ListaFechaHora* MyHashTable::get(const string& key) {
    int pos = getPos(key);

    // Buscar la IP específica en esta posición
    MyNodoLL<IPEntry>* current = table[pos].head;
    while (current != nullptr) {
        if (current->data.ip == key) {
            // IP encontrada, devolver su lista de fechas
            return &(current->data.fechas);
        }
        current = current->next;
    }

    // IP no encontrada
    return nullptr;
}

bool MyHashTable::isEmpty() {
    return this -> size == 0; // si la tabla está vacía
}


int MyHashTable::getSize() { 
    return this->size; 
} 

// Función hash simple basada en la IP 
int MyHashTable::hashFunction(const string& key) { 
    unsigned int hash = 0; 
    for (char c : key) { 
        hash = hash * 31 + c; // FNV-1a es más robusto, pero este es simple 
    } 
    return hash % sizeA; 
}

// Obtiene la posición en el arreglo para una clave (usa la función hash) 
int MyHashTable::getPos(const string& key) { 
    return hashFunction(key); 
}

// Placeholder para rehashing (puedes implementarlo si lo necesitas) 
void MyHashTable::rehashing() { 
    // Implementación futura si se desea manejar tablas dinámicas 
    // Por ahora, asumimos que el tamaño inicial es suficiente o que no se llena demasiado 
}