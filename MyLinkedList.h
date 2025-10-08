//
// Created by Erick A01641715 on 25/09/2025.
//
// MyLinkedList.h
#ifndef TEC_MYLINKEDLIST_H
#define TEC_MYLINKEDLIST_H
#include <iostream>
using namespace std;

template<typename T>
struct MyNodoLL {
    T data;
    MyNodoLL *next;

    MyNodoLL(T data, MyNodoLL *next) {
        this->data = data;
        this->next = next;
    }

    MyNodoLL(T data) : MyNodoLL(data, nullptr) {
    }
};

template<typename T>
class MyLinkedList {
public:
    int size;
    MyNodoLL<T> *head;
    MyNodoLL<T> *tail;

    // Complejidad: O(1)
    MyLinkedList() {
        this->head = tail = nullptr;
        this->size = 0;
    }

    // Complejidad: O(n) - Copy constructor
    MyLinkedList(const MyLinkedList &other) {
        this->head = this->tail = nullptr;
        this->size = 0;

        MyNodoLL<T> *current = other.head;
        while (current != nullptr) {
            this->insertLast(current->data);
            current = current->next;
        }
    }

    // Complejidad: O(n) - Copy assignment operator
    MyLinkedList &operator=(const MyLinkedList &other) {
        if (this != &other) {
            while (!isEmpty()) {
                removeFirst();
            }

            MyNodoLL<T> *current = other.head;
            while (current != nullptr) {
                this->insertLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Complejidad: O(n)
    ~MyLinkedList() {
        MyNodoLL<T> *current = this->head;
        while (current != nullptr) {
            MyNodoLL<T> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Complejidad: O(1)
    int length() const {
        return this->size;
    }

    // Complejidad: O(1)
    bool isEmpty() const {
        return this->size == 0;
    }

    // Complejidad: O(1)
    T first() {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede conseguir nada");
        }
        return this->head->data;
    }

    // Complejidad: O(1)
    T last() {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede conseguir nada");
        }
        return this->tail->data;
    }

    // Complejidad: O(n)
    T getAt(int pos) {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede conseguir nada");
        }
        if (pos < 0 || pos >= length()) {
            throw invalid_argument("La posicion " + to_string(pos) + " no existe en la lista");
        }

        MyNodoLL<T> *current = this->head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Complejidad: O(n)
    void setAt(int pos, T data) {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede modificar nada");
        }
        if (pos < 0 || pos >= length()) {
            throw invalid_argument("La posicion " + to_string(pos) + " no existe en la lista");
        }

        MyNodoLL<T> *current = this->head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        current->data = data;
    }

    // Complejidad: O(1)
    void insertFirst(T data) {
        MyNodoLL<T> *nvo = new MyNodoLL<T>(data, this->head);
        this->head = nvo;
        this->size++;
        if (this->size == 1) {
            this->tail = this->head;
        }
    }

    // Complejidad: O(1)
    void insertLast(T data) {
        MyNodoLL<T> *nvo = new MyNodoLL<T>(data, nullptr);
        if (this->isEmpty()) {
            this->head = this->tail = nvo;
        } else {
            this->tail->next = nvo;
            this->tail = nvo;
        }
        this->size++;
    }

    // Complejidad: O(n)
    void insertAt(int pos, T data) {
        if (pos < 0 || pos > length()) {
            throw invalid_argument("La posicion " + to_string(pos) + " no es valida");
        }

        if (pos == 0) {
            insertFirst(data);
            return;
        }
        if (pos == length()) {
            insertLast(data);
            return;
        }

        MyNodoLL<T> *current = this->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        MyNodoLL<T> *nvo = new MyNodoLL<T>(data, current->next);
        current->next = nvo;
        this->size++;
    }

    // Complejidad: O(1)
    void removeFirst() {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede eliminar nada");
        }
        MyNodoLL<T> *temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->size--;

        if (this->size == 0) {
            this->tail = nullptr;
        }
    }

    // Complejidad: O(n)
    void removeLast() {
        if (isEmpty()) {
            throw invalid_argument("La lista esta vacia, no se puede eliminar nada");
        }

        if (this->size == 1) {
            delete this->head;
            this->head = this->tail = nullptr;
            this->size = 0;
            return;
        }

        MyNodoLL<T> *current = this->head;
        while (current->next != this->tail) {
            current = current->next;
        }
        delete this->tail;
        this->tail = current;
        this->tail->next = nullptr;
        this->size--;
    }

    // Complejidad: O(n)
    void removeAt(int pos) {
        if (pos < 0 || pos >= length()) {
            throw invalid_argument("La posicion " + to_string(pos) + " no existe en la lista");
        }

        if (pos == 0) {
            removeFirst();
            return;
        }
        if (pos == length() - 1) {
            removeLast();
            return;
        }

        MyNodoLL<T> *current = this->head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        MyNodoLL<T> *temp = current->next;
        current->next = temp->next;
        delete temp;
        this->size--;
    }

    // Para acceder al nodo en posición específica (usado en merge sort)
    MyNodoLL<T> *getNodoAt(int pos) {
        if (pos < 0 || pos >= length()) {
            return nullptr;
        }
        MyNodoLL<T> *current = this->head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current;
    }
};

#endif //TEC_MYLINKEDLIST_H
