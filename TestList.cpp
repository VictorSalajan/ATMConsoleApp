#include "TestList.h"
#include "List.h"
#include <cassert>

template <typename T, typename U>
void TestList<T, U>::testAll() {
    test_push_back();
    test_get_at();
    test_search();
    test_update();
    test_insertAt();
    test_delete_at();
}

template <typename T, typename U>
void TestList<T, U>::test_push_back() {
    List<T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(4);
    assert(newList.size() == 4);
}

template <typename T, typename U>
void TestList<T, U>::test_get_at() {
    List<T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(4);
    assert(newList.get_at(0) == 1);
    assert(newList.get_at(1) == 2);
    assert(newList.get_at(2) == 3);
    assert(newList.get_at(3) == 4);
}

template <typename T, typename U>
void TestList<T, U>::test_update() {
    List<T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(4);
    newList.update(0, 10);
    newList.update(1, 20);
    newList.update(2, 30);
    newList.update(3, 40);
    assert(newList.get_at(0) == 10);
    assert(newList.get_at(1) == 20);
    assert(newList.get_at(2) == 30);
    assert(newList.get_at(3) == 40);
}

template <typename T, typename U>
void TestList<T, U>::test_search() {
    List<T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(3);
    newList.push_back(4);
    assert(newList.search(0) == -1);
    assert(newList.search(1) == 0);
    assert(newList.search(2) == 1);
    assert(newList.search(3) == 2);
}

template <typename T, typename U>
void TestList<T, U>::test_insertAt() {
    List<T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(3);
    newList.push_back(4);
    newList.insertAt(2, 4);             // insert middle
    assert(newList.search(2) == 1);
    assert(newList.search(4) == 2);
    assert(newList.search(3) == 3);
    newList.insertAt(0, 5);             // insert start
    assert(newList.search(5) == 0);
    assert(newList.search(1) == 1);
    newList.insertAt(6, 7);             // insert end
    assert(newList.get_at(6) == 4);
    assert(newList.search(7) == 7);     // if elem inserted at the end => its new pos = size()-1
}

template <typename T, typename U>
void TestList<T, U>::test_delete_at(){
    List <T, U> newList;
    newList.push_back(1);
    newList.push_back(2);
    newList.push_back(3);
    newList.push_back(4);
    assert(newList.delete_at(2)==3);
    assert(newList.size() == 3);
    assert(newList.get_at(2)==4);
    assert(newList.search(3)==-1);
    newList.delete_at(2);
    assert(newList.search(4) == -1);
    assert(newList.size() == 2);
    assert(newList.get_at(0) == 1);
    assert(newList.get_at(1) == 2);
    newList.delete_at(0);
    assert(newList.size() == 1);
    assert(newList.search(1) == -1);
    assert(newList.search(2) == 0);
}
