#pragma once
#include "C:\Users\huuma\Documents\DSA\DSA-1\doublyLinkedList\list.h"
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list;

public:
    // Правило пяти
    Queue() = default;
    ~Queue() = default;

    // Конструктор копирования
    Queue(const Queue& other){
        list = other.list;
    } 

    Queue& operator=(const Queue& other) { // Присваивание копированием
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    // Конструктор перемещения
    Queue(Queue&& other) noexcept {
        list = move(other.list);
    } 

    Queue& operator=(Queue&& other) noexcept { // Присваивание перемещением
        if (this != &other) {
            list = move(other.list);
        }
        return *this;
    }

    // Добавление элемента в конец очереди (O(1))
    void enqueue(const T& value) {
        list.insert_back(value);
    }

    // Удаление элемента из начала очереди (O(1))
    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        T value = front();
        list.remove_front();
        return value;
    }

    // Доступ к первому элементу (O(1))
    T& front() {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        return list.at(0);
    }

    // Константный доступ к первому элементу (O(1))
    const T& front() const {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        return list.at(0);
    }

    // Проверка на пустоту (O(1))
    bool isEmpty() const {
        return list.size() == 0;
    }

    // Размер очереди (O(1))
    size_t size() const {
        return list.size();
    }

    // Очистка очереди (O(n))
    void clear() {
        list.clear();
    }
};

void testQueue();