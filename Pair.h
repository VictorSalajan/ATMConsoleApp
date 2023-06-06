#ifndef LAB5_PAIR_H
#define LAB5_PAIR_H

template <typename T>
class Pair {
private:
    T element;
    int frequency;
public:
    Pair();
    Pair(T el, int freq);
    Pair(const Pair<T>& p);
    ~Pair ();
    T getElement() const;
    int getFrequency();
    void setElement(T el);
    void setFrequency(int freq);
};

template <typename T>
Pair<T>::Pair() {
    this->element = 0;
    this->frequency = 0;
}

template <typename T>
Pair<T>::Pair(T el, int freq) {
    this->element = el;
    this->frequency = freq;
}

template <typename T>
Pair<T>::Pair(const Pair &p) {
    this->element = p.element;
    this->frequency = p.frequency;
}

template <typename T>
Pair<T>::~Pair() = default;

template <typename T>
T Pair<T>::getElement() const {
    return this->element;
}

template <typename T>
int Pair<T>::getFrequency() {
    return this->frequency;
}

template <typename T>
void Pair<T>::setElement(T el) {
    this->element = el;
}

template <typename T>
void Pair<T>::setFrequency(int freq) {
    this->frequency = freq;
}

#endif
