
#pragma once

using namespace std;

template <typename T>
class stack {
private:
    DoublyLinkedList<T> list; // Внутренний двусвязный список для хранения элементов

public:
    /// Конструктор по умолчанию
    stack() = default;

    /// Деструктор по умолчанию (очистка списка происходит автоматически)
    ~stack() = default;

    /// Конструктор копирования
    stack(const stack& other) {
        list = other.list;
    }

    /// Оператор присваивания копированием
    stack& operator=(const stack& other) {
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    /// Конструктор перемещения
    stack(stack&& other) noexcept {
        list = move(other.list);
    }

    /// Оператор присваивания перемещением
    stack& operator=(stack&& other) noexcept {
        if (this != &other) {
            list = move(other.list);
        }
        return *this;
    }

    /// Добавление элемента на вершину стека (O(1))
    void push(const T& value) {
        list.insert_front(value);
    }

    /// Удаление элемента с вершины стека (O(1))
    T pop() {
        if (isEmpty()) {
            throw underflow_error("Стек пуст");
        }
        T value = peek(); // Получаем значение вершины
        list.remove_front(); // Удаляем элемент
        return value; // Возвращаем значение
    }

    /// Доступ к элементу на вершине стека (O(1))
    T& peek() {
        return list.at(0);
    }

    /// Константный доступ к элементу на вершине стека (O(1))
    const T& peek() const {
        return list.at(0);
    }

    /// Проверка на пустоту стека (O(1))
    bool isEmpty() const {
        return list.size() == 0;
    }

    /// Размер стека (O(1))
    size_t size() const {
        return list.size();
    }

    /// Очистка стека (O(n))
    void clear() {
        list.clear();
    }
};

void test();