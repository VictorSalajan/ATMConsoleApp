#ifndef LAB5_LIST_H
#define LAB5_LIST_H

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T, typename U>
class List {
private:
    Node<T, U>* first;
public:
    /// Constructor Implicit
    List ();

    /// destructor
    ~List();

    /// \return dimensiunea listei
    int size() const;

    /// adaugare element la sfarsit
    /// \param e - elementul adaugat
    void push_back(T e);

    /// Returneaza elementul de pe pozitia i
    /// \param i - pozitia unui elem in lista , 0 <= i < size()
    /// \return  elementul de pe pozitia i
    /// \raise   exceptie daca i nu e valid
    T get_at(int i) const;

    U getPairAt(int pos) const;

    void setPairAt(int pos, U pair);

    /// Modifica elementul de pe pozitia i si returneaza vechea valoare
    /// Arunca exceptie daca pozitia i nu este valida
    /// \param i - pozitia unui element in lista, 0 <= i < size()
    /// \param e - noul element
    /// \return - vechiul element de pe pozitia i
    T update(int i, T e);

    /// Insereaza element pe o pozitie i
    /// Arunca exceptie daca pozitia i nu este valida
    /// \param i - pozitia unui element in lista, 0 <= i < size()
    /// \param e - elementul de inserat
    void insertAt(int i, T e);

    /// Sterge element de pe o pozitie i si returneaza elementul sters
    /// Arunca exceptie daca pozitia i nu este valida
    /// \param i - pozitia unui element in lista, 0 <= i < size()
    /// \return - vechiul element de pe pozitia i
    T delete_at(int i);

    /// Sterge elementul de pe prima pozitie si returneaza elementul sters
    /// \return - vechiul element de pe prima pozitie
    T delete_at_first_pos();

    /// Sterge elementul de pe ultima pozitie si returneaza elementul sters
    /// \param i - indicele ultimei pozitii din lista
    /// \return - vechiul element de pe ultima pozitie
    T delete_last_pos(int i);

    /// Cauta element si returneaza prima pozitie pe care apare (sau -1)
    /// \param e - elementul cautat
    /// \return - pozitia elementului cautat, sau -1 daca acesta nu exista
    int search(T e)  const;

    /// Verifica daca o pozitie din lista este valida
    /// Arunca exceptie daca pozitia nu este valida
    /// \param pos - pozitia unui element in lista, 0 <= pos < size()
    void isPosValid(int pos) const;

    /// Returneaza obiectul Node de la pozitia i
    /// Arunca exceptie daca pozitia nu este valida
    /// \param i - pozitia unui element in lista, 0 <= pos < size()
    /// \return - obiectul de tip Node de pe pozitia i
    Node<T, U>* getNodeAtPos(int i) const;
};

template <class T, class U>
List<T, U>::List() {
    this->first = nullptr;
}

template <class T, class U>
List<T, U>::~List() = default;

template <class T, class U>
void List<T, U>::push_back(T e) {
    U pair(e, 1);
    Node<T, U>* newNode = new Node<T, U>(pair, nullptr, nullptr);
    if (first == nullptr) {
        first = newNode;
        return;
    }
    Node<T, U>* last = first;
    while (last->next != nullptr)
        last = last->next;
    last->next = newNode;
    newNode->prev = last;
}

template <class T, class U>
int List<T, U>::size() const {
    int contor = 0;
    Node<T, U>* last = first;
    while (last != nullptr) {
        contor++;
        last = last->next;
    }
    return contor;
}

template <class T, class U>
void List<T, U>::isPosValid(int pos) const {
    if (pos < 0 || pos >= this->size())
        throw invalid_argument("pozitia nu este valida");
}

template <class T, class U>
T List<T, U>::get_at(int i) const {
    this->isPosValid(i);
    U pair = this->getPairAt(i);
    return pair.getElement();
}

template<typename T, typename U>
U List<T, U>::getPairAt(int pos) const {
    this->isPosValid(pos);
    Node<T, U>* node = this->getNodeAtPos(pos);
    if (node != nullptr)
        return node->info;
    return U(0, 0);
}

template<typename T, typename U>
void List<T, U>::setPairAt(int pos, U pair) {
    this->isPosValid(pos);
    Node<T, U>* node = this->getNodeAtPos(pos);
    node->info = pair;
}

template<class T, class U>
Node<T, U>* List<T, U>::getNodeAtPos(int i) const {
    this->isPosValid(i);
    Node<T, U>* crt = first;
    int pos = 0;
    while (pos < i) {
        crt = crt->next;
        pos++;
    }
    return crt;
}

template <class T, class U>
int List<T, U>::search(T elem) const {
    Node<T, U>* crt = first;
    int pos = 0;
    while(crt != nullptr) {
        if (elem == crt->info.getElement())
            return pos;
        pos++;
        crt = crt->next;
    }
    return -1;
}

template <class T, class U>
T List<T, U>::update(int i, T e) {
    this->isPosValid(i);
    Node<T, U>* toUpdate = this->getNodeAtPos(i);
    T oldElem = toUpdate->info.getElement();
    int freq = this->getNodeAtPos(i)->info.getFrequency();
    U pair(e, freq);
    toUpdate->info = pair;
    return oldElem;
}

template<class T, class U>
void List<T, U>::insertAt(int i, T e) {
    this->isPosValid(i);
    if (i == 0) {
        U pair(e, 1);
        Node<T, U>* newNode = new Node<T, U>(pair, nullptr, nullptr);
        if (first != nullptr) {
            first->prev = newNode;
            newNode->next = first;
        }
        first = newNode;                // is List is empty
        return;
    }
    if (i == size() - 1) {              // insert at last pos <=> push_back
        this->push_back(e);
        return;
    }
    Node<T, U>* crt = this->getNodeAtPos(i-1);
    U pair(e, 1);
    Node<T, U>* newNode = new Node<T, U>(pair, crt, crt->next);
    crt->next->prev = newNode;
    crt->next = newNode;
}

template<class T, class U>
T List<T, U>::delete_at_first_pos() {
    Node<T, U>* firstElem = first;
    T oldElem;
    oldElem = firstElem->info.getElement();
    if (first == nullptr)
        return 0;
    first = first->next;
    first->prev = nullptr;
    delete firstElem;
    return oldElem;
}

template<class T, class U>
T List<T, U>::delete_last_pos(int i) {
    Node<T, U>* toDelete;
    T oldElem;
    Node<T, U>* crt = this->getNodeAtPos(i-1);

    toDelete = crt->next;
    oldElem = toDelete->info.getElement();
    crt->next = nullptr;

    delete toDelete;
    return oldElem;
}

template <class T, class U>
T List<T, U>::delete_at(int i) {
    this->isPosValid(i);
    Node<T, U>* toDelete;
    Node<T, U>* replaceRemoved;
    T oldElem;

    if (i == 0 && first != nullptr)
        return this->delete_at_first_pos();

    if (i == this->size() - 1)
        return this->delete_last_pos(i);

    Node<T, U>* crt = this->getNodeAtPos(i-1);

    toDelete = crt->next;
    oldElem = toDelete->info.getElement();
    replaceRemoved = toDelete->next;
    crt->next = replaceRemoved;
    replaceRemoved->prev = crt;

    delete toDelete;
    return oldElem;
}

#endif
