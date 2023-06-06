#ifndef LAB5_CONSOLE_H
#define LAB5_CONSOLE_H


#include "ATM.h"
#include <iostream>
using namespace std;

template <typename T, typename U>
class Console
{
private:
    ATM<T, U> atm;
public:
    Console();
    ~Console();
    static void print_menu();
    void start_console();
    void displayFunds();
    void displayTransactions();
    void withdrawGreedy();
    void withdrawBacktracking();
    static void chooseAndConfirm(int &payOption, int &confirm);
    static void displayPayOptions(const vector<vector<T>> &solutions);
    void processTransactionBacktrack(int sumRequest, const vector<vector<T>> &solutions);
};

template <typename T, typename U>
Console<T, U>::Console(): atm() {
}

template <typename T, typename U>
Console<T, U>::~Console() = default;

template <typename T, typename U>
void Console<T, U>::print_menu() {
    cout<<"1. Display all banknotes."<<endl;
    cout<<"2. Restock ATM."<<endl;
    cout<<"3. Withdraw money with Greedy."<<endl;
    cout<<"4. Transaction History."<<endl;
    cout<<"5. Withdraw with Backtracking."<<endl;
    cout<<"Choose option ('-1' for exit): ";
}

template <typename T, typename U>
void Console<T, U>::start_console() {
    int option = 0;
    while (true)
    {
        print_menu();
        cin >> option;
        if (option == 1) {
            this->displayFunds();
            continue;
        }
        if (option == 2) {
            this->atm.stockATM();
            continue;
        }
        if (option == 3) {
            this->withdrawGreedy();
            continue;
        }
        if (option == 4) {
            this->displayTransactions();
            continue;
        }
        if (option == 5) {
            this->withdrawBacktracking();
            continue;
        }
        if (option == -1)
            break;
        else
            cout<<"Wrong option! Try again!"<<endl;
    }
}

template <typename T, typename U>
void Console<T, U>::displayFunds() {
    Collection<T, U> collection = this->atm.getFunds();
    collection.toString();
}

template <typename T, typename U>
void Console<T, U>::displayTransactions() {
    for (int i=0; i< this->atm.getTransactionsSize(); i++)
        this->atm.getTransactions().at(i).toString();
}

template <typename T, typename U>
void Console<T, U>::displayPayOptions(const vector<vector<T>>& solutions) {
    for (int i = 0; i < solutions.size(); i++) {
        vector<T> solution = solutions[i];
        cout << "nr " << i + 1 << ": ";
        for (T bill: solution)
            cout << bill << " ";
        cout << endl;
    }
}

template <typename T, typename U>
void Console<T, U>::withdrawGreedy() {
    int sumRequest, sumReceive = 0, confirm = 0; Transaction<T, U> transaction;
    cout<<"Type amount to withdraw: ";    cin >> sumRequest;
    if (this->atm.simulateWithdraw(sumRequest, sumReceive, this->atm.getFunds(), transaction, false)) {
        cout << "Confirm transaction? ('1' sau '0') ";
        cin >> confirm;
        this->atm.executeWithdrawGreedy(sumRequest, this->atm.getFunds(), transaction, confirm);
    }
    else
        cout<<"Transaction failed!"<<endl;
}

template <typename T, typename U>
void Console<T, U>::withdrawBacktracking() {
    vector<vector<T>> solutions; int sumRequest, maxSol;
    cout<<"Type amount to withdraw: "; cin >> sumRequest;
    cout<<"Enter maximum number of solutions: "; cin >> maxSol;

    if (!this->atm.tryWithdrawBacktrack(sumRequest, this->atm.getFunds(), solutions, maxSol)) {
        cout << "Transaction failed!" << endl;
        return;
    }
    Console<T, U>::displayPayOptions(solutions);

    this->processTransactionBacktrack(sumRequest, solutions);
}

template <typename T, typename U>
void Console<T, U>::processTransactionBacktrack(int sumRequest, const vector<vector<T>>& solutions) {
    int payOption, confirm;
    chooseAndConfirm(payOption, confirm);
    bool validOption = true;
    if (!this->atm.processTransactionBacktrack(confirm, sumRequest, payOption, solutions, validOption))
        if (! confirm)
            cout<<"Cancelled by user!"<<endl;
        else if (! validOption)
            cout<<"Option out of range!"<<endl;
}

template <typename T, typename U>
void Console<T, U>::chooseAndConfirm(int& payOption, int& confirm) {
    cout << "Choose payment option: ";    cin >> payOption;
    cout << "You've chosen option " << payOption << ". Confirm transaction? ('1' or '0') ";
    cin >> confirm;
}

#endif
