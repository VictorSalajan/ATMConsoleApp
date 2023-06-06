#include "TestList.cpp"
#include "Pair.h"
#include "Console.h"

int main() {
    TestList<int, Pair<int>> teste;
    teste.testAll();
    Console<int, Pair<int>> console;
    console.start_console();

    return 0;
}
