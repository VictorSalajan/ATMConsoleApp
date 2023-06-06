#ifndef LAB5_COLLECTION_H
#define LAB5_COLLECTION_H


#include <iostream>
 #include "List.h"
#include "Pair.h"
#include <cassert>
using namespace std;


template <typename T, typename U = Pair<T>>
class Collection {
private:
    List<T, U> list;
public:
    Collection();
    ~Collection();
    Collection(const Collection<T, U>& c);
    void add(T elem);
    T update(int i, T elem);
    void insertAt(int i, T elem);
    bool remove(T elem);
    bool search(T elem);
    int size() const;
    T getAt(int position) const;
    int getPos(T elem);
    int getFreqAt(int i) const;
    int getSum();
    void setFreqAt(int new_freq, int pos);
    string toString();
    Collection<T, U> operator+= (T value);
    T operator[] (int i) const;
};

template <typename T, typename U>
Collection<T, U>::Collection() {
    this->list = List<T, U>();
}

template <typename T, typename U>
Collection<T, U>::~Collection() = default;

template <typename T, typename U>
Collection<T, U>::Collection(const Collection<T, U>& c) {
    for (int i=0; i<c.size(); i++) {
        this->add(c[i]);
        int freq = c.getFreqAt(i);
        this->setFreqAt(freq, i);
    }
}

template <typename T, typename U>
void Collection<T, U>::add(T elem) {
    int position = this->getPos(elem);

    if (position != -1)
        this->setFreqAt(this->getFreqAt(position) + 1, position);
    else {
        this->list.push_back(elem);
        int posNewElem = this->getPos(elem);
        this->setFreqAt(1, posNewElem);
    }
}

template <typename T, typename U>
T Collection<T, U>::update(int i, T elem) {
    return this->list.update(i, elem);
}

template <typename T, typename U>
void Collection<T, U>::insertAt(int i, T elem) {
    if (!this->search(elem)) {
        this->list.insertAt(i, elem);
        return;
    }
    int oldFreq = this->getFreqAt(i);
    this->setFreqAt(oldFreq + 1, i);        // freq++ if elem already in Collection
}

template <typename T, typename U>
bool Collection<T, U>::remove(T elem) {
    if (!this->search(elem))
        return false;

    int position = this->getPos(elem);
    if (this->getFreqAt(position) > 1)
        this->setFreqAt(this->getFreqAt(position) - 1, position);
    else
        this->list.delete_at(position);

    return true;
}

template <typename T, typename U>
bool Collection<T, U>::search(T elem) {
    if (this->list.search(elem) == -1)
        return false;
    return true;
}

template <typename T, typename U>
int Collection<T, U>::getPos(T elem) {
    return this->list.search(elem);
}

template <typename T, typename U>
int Collection<T, U>::size() const {
    return this->list.size();
}

template <typename T, typename U>
T Collection<T, U>::getAt(int position) const {
    return this->list.get_at(position);
}

template <typename T, typename U>
int Collection<T, U>::getFreqAt(int i) const {
    return this->list.getPairAt(i).getFrequency();
}

template <typename T, typename U>
int Collection<T, U>::getSum() {
    int sum = 0;
    for (int i=0; i<this->size(); i++)
        sum += ((*this)[i] * this->getFreqAt(i));
    return sum;
}

template <typename T, typename U>
void Collection<T, U>::setFreqAt(int new_freq, int pos) {
    T elem = this->list.get_at(pos);
    U pair(elem, new_freq);
    this->list.setPairAt(pos, pair);
}

template <typename T, typename U>
Collection<T, U> Collection<T, U>::operator+= (T value) {
    this->add(value);
    return *this;
}

template <typename T, typename U>
T Collection<T, U>::operator[] (int i) const {
    assert (0 <= i && i < this->size());
    return this->getAt(i);
}

template <typename T, typename U>
string Collection<T, U>::toString() {
    string collection;
    for (int i=0; i<this->size(); i++) {
        string bill = to_string((*this)[i]);
        string count = to_string(this->getFreqAt(i));
        if (i == this->size() - 1)
            collection += bill + " " + count;
        else
            collection += bill + " " + count + " ";
        cout << bill << "$ * " << count << " count" << endl;
    }
    cout<<endl;
    return collection;
}

#endif
