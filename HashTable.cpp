// HashTable.cpp
#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <cstddef>
#include <map>

using namespace std;

// Función auxiliar para convertir mes a número
int mesANumero(const string& mes) {
    switch(mes[0]) {
        case 'J':
            if (mes == "Jan") return 1;
            else if (mes == "Jun") return 6;
            else if (mes == "Jul") return 7;
            break;
        case 'F':
            return 2; // Feb
        case 'M':
            if (mes == "Mar") return 3;
            else return 5; // May
        case 'A':
            if (mes == "Apr") return 4;
            else return 8; // Aug
        case 'S':
            return 9; // Sep
        case 'O':
            return 10; // Oct
        case 'N':
            return 11; // Nov
        case 'D':
            return 12; // Dec
    }
    return 0;
}

// Función para comparar dos FechaHora
// Retorna true si fh1 es menor que fh2 (orden cronológico)
bool compararFechaHora(const FechaHora& fh1, const FechaHora& fh2) {
    int mes1 = mesANumero(fh1.mes);
    int mes2 = mesANumero(fh2.mes);

    if (mes1 != mes2) return mes1 < mes2;
    if (fh1.dia != fh2.dia) return fh1.dia < fh2.dia;
    return fh1.hora < fh2.hora;
}

// los datos se toman de bitacora3.txt
MyHashTable::MyHashTable() {
    this->sizeA = 11; // tamaño inicial de la tabla hash
    this->size = 0;   // número de IPs únicas
    this->table = new MyLinkedList<HashEntry>[sizeA];
}

// Destructor - O(n)
MyHashTable::~MyHashTable() {
    delete[] table;
}

// Función hash usando std::hash - O(1)
int MyHashTable::hashFunction(const string& key) {
    size_t hashC = hash<string>{}(key);
    int hashCode = static_cast<int>(hashC);
    return abs(hashCode) % this->sizeA;
}

// Obtiene la posición en el arreglo - O(1)
int MyHashTable::getPos(const string& key) {
    return hashFunction(key);
}

// Inserta o agrega fecha a una IP - O(n) donde n = número de fechas de esa IP
void MyHashTable::put(const string& ip, const FechaHora& fechaHora) {
    int pos = getPos(ip);

    // Buscar si la IP ya existe en la lista de ese bucket
    MyNodoLL<HashEntry>* current = table[pos].head;
    while (current != nullptr) {
        if (current->data.ip == ip) {
            // IP encontrada, insertar la fecha en orden cronológico
            // Buscar la posición correcta para insertar
            if (current->data.fechas.isEmpty() ||
                compararFechaHora(fechaHora, current->data.fechas.first())) {
                // Insertar al inicio
                current->data.fechas.insertFirst(fechaHora);
            } else if (!compararFechaHora(fechaHora, current->data.fechas.last())) {
                // Insertar al final
                current->data.fechas.insertLast(fechaHora);
            } else {
                // Buscar posición en medio
                int posicion = 0;
                MyNodoLL<FechaHora>* currentFecha = current->data.fechas.head;
                while (currentFecha != nullptr) {
                    if (compararFechaHora(fechaHora, currentFecha->data)) {
                        current->data.fechas.insertAt(posicion, fechaHora);
                        this->size++;
                        return;
                    }
                    posicion++;
                    currentFecha = currentFecha->next;
                }
            }
            this->size++;
            return;
        }
        current = current->next;
    }

    // IP no existe, crear nueva entrada
    HashEntry nuevaEntrada;
    nuevaEntrada.ip = ip;
    nuevaEntrada.fechas.insertLast(fechaHora);

    table[pos].insertLast(nuevaEntrada);
    this->size++;

    // Verificar factor de carga
    if ((double)this->size / this->sizeA > 0.75) {
        rehashing();
    }
}

// Busca y retorna la lista de fechas de una IP - O(m) donde m = elementos en el bucket
ListaFechaHora* MyHashTable::get(const string& key) {
    int pos = getPos(key);

    // Buscar la IP en la lista de ese bucket
    MyNodoLL<HashEntry>* current = table[pos].head;
    while (current != nullptr) {
        if (current->data.ip == key) {
            return &(current->data.fechas);
        }
        current = current->next;
    }

    return nullptr; // IP no encontrada
}

// Verifica si la tabla está vacía - O(1)
bool MyHashTable::isEmpty() {
    return this->size == 0;
}

// Retorna el número de IPs únicas - O(1)
int MyHashTable::getSize() {
    return this->size;
}

// Rehashing - O(n) donde n = total de elementos
void MyHashTable::rehashing() {
    // Guardar tabla vieja
    MyLinkedList<HashEntry>* oldTable = this->table;
    int oldSizeA = this->sizeA;

    // Crear nueva tabla
    this->sizeA = oldSizeA * 2 + 1;
    this->table = new MyLinkedList<HashEntry>[this->sizeA];
    this->size = 0;

    // Reinsertar todos los elementos
    for (int i = 0; i < oldSizeA; i++) {
        MyNodoLL<HashEntry>* current = oldTable[i].head;
        while (current != nullptr) {
            // Reinsertar cada fecha de cada IP
            MyNodoLL<FechaHora>* currentFecha = current->data.fechas.head;
            while (currentFecha != nullptr) {
                put(current->data.ip, currentFecha->data);
                currentFecha = currentFecha->next;
            }
            current = current->next;
        }
    }

    // Liberar tabla vieja
    delete[] oldTable;
}
