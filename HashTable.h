#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H
#include "MyLinkedList.h" 
#include <string>

using namespace std;

class MyHashTable{
    private:
        MyLinkedList<string>* table;
        int size;
        int sizeA;
        int getPos(string key);
        void rehashing();

    public:
        MyHashTable();
        ~MyHashTable();
        void put(const string& key);
        MyLinkedList<string>* get(string key);
        bool isEmpty();
        int hashFunction(const string& key);
        void loadFromFile(const string& filename);
};

#endif // MYHASHTABLE_H