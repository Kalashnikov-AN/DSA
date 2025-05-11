#pragma once
#include "C:\Users\huuma\Documents\DSA\DSA-1\doublyLinkedList\list.h"
#include <stdexcept>
using namespace std;
// Автор: Калашников А.Н.

/// Шаблонный класс очередь
template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list; // Внутренний двусвязный список для хранения элементов

public:

    /// Конструктор по умолчанию
    Queue() = default;

    /// Деструктор по умолчанию 
    ~Queue() = default;

    /// Конструктор копирования, other - копируемый объект
    Queue(const Queue& other) = default;

    /// Оператор присваивания копированием, other - копируемый объект, возвращает ссылку на измённый исходный объект
    Queue& operator=(const Queue& other) = default;

    /// Конструктор перемещения, other - rvalue ссылка на перемещаемый объект
    Queue(Queue&& other) noexcept = default;

    /// Оператор присваивания перемещением, other - rvalue ссылка на перемещаемый объект, возвращает ссылку на измённый исходный объект
    Queue& operator=(Queue&& other) noexcept = default;

    /// Добавление элемента value в конец очереди 
    void enqueue(const T value) {
        list.insert_back(value);
    }

    /// Удаляет элемент из начала очереди и возвращает его
    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        T value = front();
        list.remove_front();
        return value;
    }

    /// Возвращает первый элемент из очереди 
    T front() {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        return list.at(0);
    }

    /// Константный доступ к первому элементу 
    const T front() const {
        if (isEmpty()) {
            throw underflow_error("Очередь пуста");
        }
        return list.at(0);
    }

    /// Проверка очереди на пустоту, возвращает true/false
    bool isEmpty() const {
        return list.size() == 0;
    }

    /// Возвращает размер очереди 
    size_t size() const {
        return list.size();
    }

    /// Очистка очереди
    void clear() {
        list.clear();
    }
};

/// Тесты для класса очередь
void testQueue();