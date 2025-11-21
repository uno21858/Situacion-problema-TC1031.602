#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <cstddef>

using namespace std;

// los datos se toman de bitacora3.txt
MyHashTable::MyHashTable() {
    this->sizeA = 11; // tamaño inicial de la tabla hash
    this->size = 0; // número de elementos en la tabla hash
    this->table = new ListaFechaHora[sizeA]; //-----------
}

MyHashTable::~MyHashTable() {
    for (int i = 0; i < sizeA; i++) {//------------------
    }
    delete[] table; // liberar memoria del arreglo de listas enlazadas
}

//------------------
void MyHashTable::put(const string& ip, const FechaHora& fechaHora) { //------------------
    int pos = getPos(ip); //------------------

    // Agregar la nueva FechaHora a la lista en la posición calculada //------------------
    table[pos].insertLast(fechaHora); //------------------
    this->size++; // Incrementar el contador total de entradas (IP-FechaHora) //------------------
}//------------------

// la lista de FechaHora asociadas a una IP //------------------
ListaFechaHora* MyHashTable::get(const string& key) { //------------------
    int pos = getPos(key); //------------------
    // Si la lista en table[pos] está vacía, significa que la IP no se encontró //------------------
    if (table[pos].isEmpty()) { //------------------
        return nullptr; // Indicar que no se encontró la IP //------------------
    }
    return &(table[pos]); // Devolver la dirección de la lista encontrada //------------------
}//------------------

bool MyHashTable::isEmpty() {
    return this -> size == 0; // si la tabla está vacía
}


int MyHashTable::getSize() { //------------------
    return this->size; //------------------
}//------------------

// Función hash simple basada en la IP //------------------
int MyHashTable::hashFunction(const string& key) { //------------------
    unsigned int hash = 0; //------------------
    for (char c : key) { //------------------
        hash = hash * 31 + c; // FNV-1a es más robusto, pero este es simple //------------------
    } //------------------
    return hash % sizeA; //------------------
}//------------------

// Obtiene la posición en el arreglo para una clave (usa la función hash) //------------------
int MyHashTable::getPos(const string& key) { //------------------
    return hashFunction(key); //------------------
}//------------------

// Placeholder para rehashing (puedes implementarlo si lo necesitas) //------------------
void MyHashTable::rehashing() { //------------------
    // Implementación futura si se desea manejar tablas dinámicas //------------------
    // Por ahora, asumimos que el tamaño inicial es suficiente o que no se llena demasiado //------------------
}//------------------