#include "HashTable.h"
#include <iostream>
#include <sstream>
#include <cstddef>
#include <map>

using namespace std;

// Mapa para convertir mes a número (para comparación cronológica)
static const map<string, int> mesANumero = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
    {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
    {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

// Comparador para ordenar fechas cronológicamente
bool FechaHora::operator<(const FechaHora& otra) const {
    // Comparar por mes
    int miMes = mesANumero.at(this->mes);
    int otroMes = mesANumero.at(otra.mes);
    if (miMes != otroMes) return miMes < otroMes;

    // Si el mes es igual, comparar por día
    if (this->dia != otra.dia) return this->dia < otra.dia;

    // Si día es igual, comparar por hora
    return this->hora < otra.hora;
}

// Constructor - O(1)
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
            // IP encontrada, insertar fecha en orden
            insertarOrdenado(current->data.fechas, fechaHora);
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

// Función auxiliar para insertar fecha en orden cronológico
void insertarOrdenado(ListaFechaHora& lista, const FechaHora& nuevaFecha) {
    // Si la lista está vacía o la nueva fecha va al inicio
    if (lista.isEmpty() || nuevaFecha < lista.head->data) {
        lista.insertFirst(nuevaFecha);
        return;
    }

    // Buscar la posición correcta
    MyNodoLL<FechaHora>* current = lista.head;
    while (current->next != nullptr && current->next->data < nuevaFecha) {
        current = current->next;
    }

    // Insertar después de current
    MyNodoLL<FechaHora>* nuevoNodo = new MyNodoLL<FechaHora>(nuevaFecha);
    nuevoNodo->next = current->next;
    current->next = nuevoNodo;

    // Actualizar tail si es necesario
    if (nuevoNodo->next == nullptr) {
        lista.tail = nuevoNodo;
    }
}
