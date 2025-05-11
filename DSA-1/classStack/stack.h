#pragma once
#include "C:\Users\huuma\Documents\DSA\DSA-1\doublyLinkedList\list.h"
using namespace std;
// Автор: Калашников А.Н.

/// Класс стека элементов типа T
template <typename T>
class stack {
private:
    DoublyLinkedList<T> list; // Внутренний двусвязный список для хранения элементов

public:
    /// Конструктор по умолчанию
    stack() = default;

    /// Деструктор по умолчанию 
    ~stack() = default;

    /// Конструктор копирования, other - копируемый объект
    stack(const stack& other) = default;

    /// Оператор присваивания копированием, other - копируемый объект, возвращает ссылку на измённый исходный объект
    stack& operator=(const stack& other) = default;

    /// Конструктор перемещения, other - rvalue ссылка на перемещаемый объект
    stack(stack&& other) noexcept = default;

    /// Оператор присваивания перемещением, other - rvalue ссылка на перемещаемый объект, возвращает ссылку на измённый исходный объект
    stack& operator=(stack&& other) noexcept = default;


    /// Добавление элемента value на вершину стека 
    void push(const T value) {
        list.insert_front(value);
    }

    /// Удаленяет элемент с вершины стека и возвращает его после удаления 
    T pop() {
        if (isEmpty()) {
            throw underflow_error("Стек пуст");
        }
        T value = peek(); // Получаем значение вершины
        list.remove_front(); // Удаляем элемент
        return value; // Возвращаем значение
    }

    /// Доступ к элементу на вершине стека 
    T peek() {
        return list.at(0);
    }

    /// Константный доступ к элементу на вершине стека 
    const T peek() const {
        return list.at(0);
    }

    /// Проверка на пустоту стека 
    bool isEmpty() const {
        return list.size() == 0;
    }

    /// Возвращает размер стека 
    size_t size() const {
        return list.size();
    }

    /// Очистка стека 
    void clear() {
        list.clear();
    }
};

/// Тесты для класса стека
void test();