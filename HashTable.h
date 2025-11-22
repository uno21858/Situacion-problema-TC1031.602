#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include "MyLinkedList.h"
#include <string>
#include <vector>

using namespace std;

struct FechaHora {
    string mes;
    int dia;
    string hora;
    int puerto;
    string mensaje;

    // Comparador para orden cronológico
    bool operator<(const FechaHora& otra) const;
};

using ListaFechaHora = MyLinkedList<FechaHora>;

// Estructura para almacenar IP + sus fechas (manejo de colisiones)
struct HashEntry {
    string ip;
    ListaFechaHora fechas;
};

// Función auxiliar para insertar fecha en orden cronológico
void insertarOrdenado(ListaFechaHora& lista, const FechaHora& nuevaFecha);

class MyHashTable{
    private:
    MyLinkedList<HashEntry>* table;  // Array de listas de pares (IP, fechas)
    int size;
    int sizeA;
    int getPos(const string& key);
    void rehashing();
    int hashFunction(const string& key);


    public:
        MyHashTable();
        ~MyHashTable();
        void put(const string& ip, const FechaHora& fechaHora);
        ListaFechaHora* get(const string& key);
        bool isEmpty();
        int getSize();
};

#endif // MYHASHTABLE_H