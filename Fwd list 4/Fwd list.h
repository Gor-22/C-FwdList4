#pragma once
#include <stdexcept>
#include <initializer_list>
#include <iostream>

template <class T>
class ForwardList {
public:
    ForwardList(std::size_t size = 0);
    ForwardList(std::size_t size, T filler);
    ForwardList(std::size_t size, const T& filler);
    bool empty();
    T& front();
    void push_front(T value);
    void push_front(const T& value);
    void pop_front();
    ~ForwardList() noexcept;

private:
    struct Node {
        T value;
        Node* next;
        Node() : value(T()), next(nullptr) {}
        Node(const T& value, Node* next = nullptr) : value(value), next(next) {}
    };

    Node* head = nullptr;
    std::size_t size;

    void clean();
};

// Конструктор по умолчанию
template<class T>
ForwardList<T>::ForwardList(std::size_t size) : size(size) {
    Node** current = &head;
    for (std::size_t i = 0; i < size; ++i) {
        *current = new Node();
        current = &((*current)->next);
    }
}

// Параметрический конструктор
template<class T>
ForwardList<T>::ForwardList(std::size_t size, T filler) : size(size) {
    Node** current = &head;
    for (std::size_t i = 0; i < size; ++i) {
        *current = new Node();
        (*current)->value = filler;
        current = &((*current)->next);
    }
}

// Параметрический конструктор с константным параметром
template<class T>
ForwardList<T>::ForwardList(std::size_t size, const T& filler) : size(size) {
    Node** current = &head;
    for (std::size_t i = 0; i < size; ++i) {
        *current = new Node();
        (*current)->value = filler;
        current = &((*current)->next);
    }
}

// Метод для проверки пустоты списка
template<class T>
bool ForwardList<T>::empty() {
    return size == 0;
}

// Метод для доступа к первому элементу
template<class T>
T& ForwardList<T>::front() {
    return head->value;
}

// Метод для добавления элемента в начало списка
template<class T>
void ForwardList<T>::push_front(T value) {
    Node* newNode = new Node();
    newNode->value = value;
    newNode->next = head;
    head = newNode;
    size++;
}

// Метод для добавления элемента в начало списка с константным параметром
template<class T>
void ForwardList<T>::push_front(const T& value) {
    Node* newNode = new Node(value, head);
    head = newNode;
    size++;
}

// Метод для удаления первого элемента
template<class T>
void ForwardList<T>::pop_front() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    size--;
}

// Метод для очистки списка
template<class T>
void ForwardList<T>::clean() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// Деструктор
template<class T>
ForwardList<T>::~ForwardList() noexcept {
    clean();
    size = 0;
}
