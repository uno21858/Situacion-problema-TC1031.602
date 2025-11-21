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


class MyHashTable{
    private:
    ListaFechaHora* table;
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