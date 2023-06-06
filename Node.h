#ifndef LAB5_NODE_H
#define LAB5_NODE_H

template <class T, class U>
class List;

template <class T, class U>
class Node {
private:
    U info;
    Node<T, U>* prev;
    Node<T, U>* next;
public:
    Node(U info, Node<T, U>* prev, Node<T, U>* next) : info(info), prev(prev), next(next) {}
    Node(U info) : info(info) { prev = nullptr; next = nullptr; }
    ~Node() = default;
    friend class List<T, U>;
};

#endif
