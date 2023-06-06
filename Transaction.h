#ifndef LAB5_TRANSACTION_H
#define LAB5_TRANSACTION_H

#include "Collection.h"
#include <iostream>
using namespace std;

template <typename T, typename U>
class Transaction {
private:
    int id;
    int sum;
    Collection<T, U> payment;
public:
    Transaction();
    ~Transaction();
    Transaction(const Transaction<T, U>& t);
    int getId();
    int getSum();
    Collection<T, U>& getPayment();
    void setSum(int amount);
    void setId(int newId);
    void add(T bill);
    string toString();
};

template <typename T, typename U>
Transaction<T, U>::Transaction() {
    this->id = 0;
    this->sum = 0;
    this->payment = Collection<T, U>();
}

template <typename T, typename U>
Transaction<T, U>::~Transaction() = default;

template <typename T, typename U>
Transaction<T, U>::Transaction(const Transaction<T, U>& t) {
    this->id = t.id;
    this->sum = t.sum;
    this->payment = t.payment;
}

template <typename T, typename U>
int Transaction<T, U>::getId() {
    return this->id;
}

template <typename T, typename U>
int Transaction<T, U>::getSum() {
    return this->sum;
}

template <typename T, typename U>
Collection<T, U>& Transaction<T, U>::getPayment() {
    return this->payment;
}

template <typename T, typename U>
void Transaction<T, U>::setId(int newId) {
    this->id = newId;
}

template <typename T, typename U>
void Transaction<T, U>::setSum(int amount) {
    this->sum = amount;
}

template <typename T, typename U>
void Transaction<T, U>::add(T bill) {
    this->payment.add(bill);
}

template<typename T, typename U>
string Transaction<T, U>::toString() {
    string id, amount, bills;
    id = to_string(this->getId());
    amount = to_string(this->getSum());
    cout << "Transaction: " << this->getId() << "; Sum: " << this->getSum() << endl;
    bills = this->getPayment().toString();
    return id + " " + amount + " " + bills;
}

#endif
