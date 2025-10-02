// Автор: Калашников А.Н.
// Реализация шаблонного класса Heap (минимальная куча)
// Внутреннее хранение: DynamicArray<T>

#pragma once
#include <stdexcept>
#include <iostream>
#include "C:\Users\huuma\Documents\DSA\DSA-1\classDynamicArray\dynArray.h"

using namespace std;

/**
 * @class Heap
 * @brief Шаблонный класс для реализации минимальной кучи (min-heap).
 *
 * Хранение осуществляется в объекте DynamicArray<T>.
 * Свойство min-heap: значение в каждом узле <= значений его потомков.
 */
template <typename T>
class Heap {
private:
    DynamicArray<T> data;  ///< массив для хранения элементов кучи

    /**
     * @brief Просеивание вверх (восстановление свойства кучи при вставке).
     * @complexity O(log n)
     */
    void bubble_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2; // выразили формулу для нахождения индекса потомка
            if (data[index] < data[parent]) { 
                swap(data[index], data[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    /**
     * @brief Просеивание вниз (восстановление свойства кучи при удалении).
     * @complexity O(log n)
     */
    void trickle_down(size_t index) {
        size_t n = data.size();
        while (true) {
            size_t left = 2 * index + 1; // левый потомок текущего узла
            size_t right = 2 * index + 2; // правый потомок текущего узла
            size_t smallest = index; // текущий узел, должен быть наименьшим по значению

            if (left < n && data[left] < data[smallest]) // левый потомок существует и его значение меньше текущего узла
                smallest = left;
            if (right < n && data[right] < data[smallest]) // правый потомок существует и его значение меньше текущего узла
                smallest = right;

            if (smallest != index) { // нашли узел с меньшим значением
                swap(data[index], data[smallest]); // меняем местами
                index = smallest; // новый текущий узел
            }
            else { // если не нашли узел с меньшим значением, значит на месте корня верный узел
                break; // выходим из цикла
            }
        }
    }

public:
    /// Конструктор
    Heap(size_t initial_capacity = 16) : data(initial_capacity) {}

   /**
        *@brief Конструктор из DynamicArray<T>(копия).
        * @param arr — объект DynamicArray<T>
        *
        * @complexity O(n)
        */
        Heap(const DynamicArray<T>&arr) : data(arr) {
        // Построение кучи за O(n)
        for (int i = static_cast<int>(data.size()) / 2 - 1; i >= 0; --i) {
            trickle_down(i);
        }
    }

    /// Проверка, пуста ли куча
    bool empty() const {
        return data.size() == 0;
    }

    /// Количество элементов
    size_t size() const {
        return data.size();
    }

    /**
     * @brief Вставка элемента в кучу
     * @complexity O(log n)
     */
    void insert(const T& value) {
        data.push_back(value);
        bubble_up(data.size() - 1);
    }

    /**
     * @brief Возвращает минимальный элемент (корень кучи)
     * @complexity O(1)
     */
    const T& get_min() const {
        if (empty()) throw runtime_error("Heap is empty");
        return data[0];
    }

    /**
     * @brief Удаление минимального элемента (корня кучи)
     * @complexity O(log n)
     */
    void extract_min() {
        if (empty()) throw runtime_error("Heap is empty");
        if (data.size() == 1) {
            data.pop_back();
            return;
        }
        data[0] = data[data.size() - 1];
        data.pop_back();
        trickle_down(0);
    }

    /**
 * @brief Поиск элемента в куче
 * @param value значение для поиска
 * @return индекс найденного элемента или -1, если элемент не найден
 * @complexity O(n)
 */
    int find(const T& value) const {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == value) {
                return i; // нашли — возвращаем индекс
            }
        }
        return -1; // не нашли
    }


    /**
     * @brief Печать кучи (для отладки)
     * @complexity O(n)
     */
    void print() const {
        for (size_t i = 0; i < data.size(); i++)
            cout << data[i] << " ";
        cout << "\n";
    }
};
