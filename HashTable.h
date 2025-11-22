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
};

using ListaFechaHora = MyLinkedList<FechaHora>;

// Estructura para manejar colisiones: guarda IP + sus fechas
struct IPEntry {
    string ip;
    ListaFechaHora fechas;
};

using ListaIPEntry = MyLinkedList<IPEntry>;


class MyHashTable{
    private:
    ListaIPEntry* table;  // Ahora cada posición tiene una lista de IPEntry
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
       // MyLinkedList<string>* get(string key);
        bool isEmpty();
        int getSize();
      //  int hashFunction(const string& key);
       // void loadFromFile(const string& filename);
};

#endif // MYHASHTABLE_H