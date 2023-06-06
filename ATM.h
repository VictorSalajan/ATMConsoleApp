#ifndef LAB5_ATM_H
#define LAB5_ATM_H

#include "Collection.h"
#include "Transaction.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

template <typename T, typename U>
class ATM {
private:
    Collection<T, U> funds;
    vector<Transaction<T, U>> transactions;
    string transactionsFile;
    string fundsFile;
public:
    ATM();
    ~ATM();
    Collection<T, U>& getFunds();
    vector<Transaction<T, U>>& getTransactions();
    int getTransactionsSize();
    void stockATM(vector<T> bills = {10, 20, 50, 100, 200, 500});

    bool validateSumRequest(int sumRequest);
    static bool postSimulationValidation(int sumRequest, int sumReceive);

    static void withdrawGreedyAlgo(int& sumRequest, int& sumReceive, Collection<T, U>& collection, Transaction<T, U>& transaction);
    bool simulateWithdraw(int &sumRequest, int &sumReceive, Collection<T, U> &collection, Transaction<T, U> &transaction, bool backtrack);
    void executeWithdrawGreedy(int sumRequest, Collection<T, U> &collection, Transaction<T, U> &transaction, int confirm);

    bool tryWithdrawBacktrack(int sumRequest, Collection<T, U> &collection, vector<vector<T>>& solutions, int maxSol);
    void backtrack(int &start, int &current_sum, int sumRequest, Collection<T, U> &collection, vector<T> solution,
                   vector<vector<T>> &solutions, int maxSol);
    void updateAtmBacktrack(int sumRequest, int payOption, const vector<vector<T>>& solutions);
    bool processTransactionBacktrack(int confirm, int sumRequest, int payOption, const vector<vector<T>>& solutions, bool& validOption);

    void setTransaction(int sumRequest, Transaction<T, U>& transaction);
    void addTransactToATM(Transaction<T, U>& transaction);
    static void addBillsToTransact(Transaction<T, U>& transaction, const vector<T>& bills);
    void removeBillsFromATM(const vector<T> &bills);

    void readBillsFromStream(stringstream& linestream, vector<T> &bills);
    void readTransactionsFile();
    void writeTransactionsFile();
    void readFundsFile();
    void writeFundsFile();
};

template <typename T, typename U>
void ATM<T, U>::readBillsFromStream(stringstream& linestream, vector<T>& bills) {
    string strBill, count;
    while (linestream >> strBill) {
        linestream >> count;
        int bill = stoi(strBill);
        for (int i = 0; i < stoi(count); i++)
            bills.push_back(bill);
    }
}

template <typename T, typename U>
void ATM<T, U>::readTransactionsFile() {
    string line; int id, sum;
    ifstream fin(this->transactionsFile);
    while (getline(fin, line,'\n')) {
        stringstream linestream(line);
        linestream >> id >> sum;
        Transaction<T, U> transaction;
        vector<T> bills;
        transaction.setId(id);
        transaction.setSum(sum);
        this->readBillsFromStream(linestream, bills);
        this->addBillsToTransact(transaction, bills);
        this->addTransactToATM(transaction);
        }
    fin.close();
}

template <typename T, typename U>
void ATM<T, U>::readFundsFile() {
    string line;
    ifstream fin(this->fundsFile);
    while (getline(fin, line,'\n')) {
        stringstream linestream(line);
        vector<T> bills;
        this->readBillsFromStream(linestream, bills);
        this->stockATM(bills);
    }
    fin.close();
}

template <typename T, typename U>
void ATM<T, U>::writeFundsFile() {
    ofstream fout(this->fundsFile);
    Collection<T, U> bills = this->getFunds();
    vector<T> values = {10, 20, 50, 100, 200, 500};
    for (auto value: values)
        if (bills.search(value)) {
            int pos = bills.getPos(value);
            int bill = bills[pos];
            int count = bills.getFreqAt((pos));
            fout << bill << " " << count << endl;
        }
    fout.close();
}

template <typename T, typename U>
void ATM<T, U>::writeTransactionsFile() {
    ofstream fout(this->transactionsFile);
    vector<Transaction<T, U>> allTransactions;
    allTransactions = this->getTransactions();
    for (Transaction<T, U> transaction: allTransactions) {
        fout << transaction.toString() << endl;
    }
    fout.close();
}

template <typename T, typename U>
ATM<T, U>::ATM(): funds() {
    this->transactions = vector<Transaction<T, U>>();
    this->transactionsFile = "transactionsFile.txt";
    this->fundsFile = "fundsFile.txt";
    this->readTransactionsFile();
    this->readFundsFile();
}

template <typename T, typename U>
ATM<T, U>::~ATM() = default;

template <typename T, typename U>
Collection<T, U>& ATM<T, U>::getFunds() {
    return this->funds;
}

template <typename T, typename U>
vector<Transaction<T, U>>& ATM<T, U>::getTransactions() {
    return this->transactions;
}

template <typename T, typename U>
int ATM<T, U>::getTransactionsSize() {
    return (int) this->transactions.size();
}

template <typename T, typename U>
void ATM<T, U>::stockATM(vector<T> bills) {
    sort(bills.begin(), bills.end());
    for (T bill : bills)
        this->funds += bill;
    this->writeFundsFile();
}

template <typename T, typename U>
void ATM<T, U>::setTransaction(int sumRequest, Transaction<T, U>& transaction) {
    int newId = this->getTransactionsSize() + 1;
    transaction.setId(newId);
    transaction.setSum(sumRequest);
}

template <typename T, typename U>
void ATM<T, U>::addBillsToTransact(Transaction<T, U>& transaction, const vector<T>& bills) {
    for (T bill: bills)
        transaction.add(bill);
}

template <typename T, typename U>
void ATM<T, U>::addTransactToATM(Transaction<T, U>& transaction) {
    this->getTransactions().push_back(transaction);
}

template <typename T, typename U>
void ATM<T, U>::removeBillsFromATM(const vector<T>& bills) {
    for (T bill: bills)
        this->funds.remove(bill);
}

template <typename T, typename U>
bool ATM<T, U>::validateSumRequest(int sumRequest) {
    if (sumRequest <= 0 || sumRequest > this->getFunds().getSum())
        return false;
    return true;
}

template <typename T, typename U>
bool ATM<T, U>::postSimulationValidation(int sumRequest, int sumReceive) {
    return sumReceive == sumRequest;
}

template <typename T, typename U>
void ATM<T, U>::withdrawGreedyAlgo(int& sumRequest, int& sumReceive, Collection<T, U>& collection, Transaction<T, U>& transaction) {
    int bill; int size = collection.size();

    for (int i=size-1; i>=0; i--) {
        bill = collection[i];
        while (collection.getFreqAt(i) > 0 && (sumReceive + bill <= sumRequest)) {
            sumReceive += bill;
            transaction.add(bill);
            collection.remove(bill);
        }
    }
}

template <typename T, typename U>
bool ATM<T, U>::simulateWithdraw(int &sumRequest, int &sumReceive, Collection<T, U> &collection, Transaction<T, U> &transaction, bool backtrack) {
    Transaction<T, U> copy_transact(transaction);
    Collection<T, U> copy_collection(collection);

    if (!validateSumRequest(sumRequest))
        return false;

    this->withdrawGreedyAlgo(sumRequest, sumReceive, copy_collection, copy_transact);

    if (postSimulationValidation(sumRequest, sumReceive)) {
        this->setTransaction(sumRequest, copy_transact);
        if (! backtrack)
            copy_transact.toString();
        return true;
    }
    return false;
}

template <typename T, typename U>
void ATM<T, U>::executeWithdrawGreedy(int sumRequest, Collection<T, U>& collection, Transaction<T, U>& transaction, int confirm) {
    int sumReceive = 0;
    if (confirm == 1) {
        this->withdrawGreedyAlgo(sumRequest, sumReceive, collection, transaction);
        this->setTransaction(sumRequest, transaction);
        this->addTransactToATM(transaction);
        this->writeTransactionsFile();                      /// SUCCESS => Write to transaction file
        this->writeFundsFile();                             /// + write to funds file
    }
}

template <typename T, typename U>
void ATM<T, U>::backtrack(int& start, int& current_sum, int sumRequest, Collection<T, U>& collection, vector<T> solution, vector<vector<T>>& solutions, int maxSol) {
    if (current_sum == sumRequest) {
        solutions.push_back(solution);
        return;
    }
    if (solutions.size() == maxSol)
        return;
    for (int i=collection.size()-1; i>=start; i--) {
        int bill = collection[i];
        if (current_sum + bill > sumRequest)
            continue;
        if (collection.getFreqAt(i) == 0)
            continue;
        solution.push_back(bill);
        current_sum += bill;
        collection.remove(bill);
        backtrack(i, current_sum, sumRequest, collection, solution, solutions, maxSol);
        solution.pop_back();
        current_sum -= bill;
        collection.add(bill);
    }
}

template <typename T, typename U>
bool ATM<T, U>::tryWithdrawBacktrack(int sumRequest, Collection<T, U>& collection, vector<vector<T>>& solutions, int maxSol) {
    vector<T> solution; Transaction<T, U> transaction;
    int start = 0, current_sum = 0, sumReceive = 0;

    if (!this->simulateWithdraw(sumRequest, sumReceive, collection, transaction, true))
        return false;
    backtrack(start, current_sum, sumRequest, collection, solution, solutions, maxSol);
    return true;
}

template <typename T, typename U>
void ATM<T, U>::updateAtmBacktrack(int sumRequest, int payOption, const vector<vector<T>>& solutions) {
    Transaction<T, U> transaction;
    vector<T> paySolution = solutions[payOption - 1];

    this->addBillsToTransact(transaction, paySolution);
    this->removeBillsFromATM(paySolution);
    this->setTransaction(sumRequest, transaction);
    this->addTransactToATM(transaction);
}

template <typename T, typename U>
bool ATM<T, U>::processTransactionBacktrack(int confirm, int sumRequest, int payOption, const vector<vector<T>>& solutions, bool& validOption) {
    if (payOption > solutions.size()) {
        validOption = false;
        return false;
    }
    if (confirm == 1) {
        this->updateAtmBacktrack(sumRequest, payOption, solutions);
        this->writeTransactionsFile();                      /// SUCCESS => Write to transaction file
        this->writeFundsFile();                             /// + write to funds file
        return true;
    }
    return false;
}

#endif
