// Автор: Калашников А.Н.
#pragma once
#include <stdexcept>
#include <iostream>
#include "..\..\DSA-1\classDynamicArray\dynArray.h"


using namespace std;

/**
 * Шаблонный класс для реализации минимальной кучи (min-heap).
 * Хранение осуществляется в объекте DynamicArray<T>.
 * Значение в каждом узле <= значений его потомков.
 */
template <typename T>
class Heap {
private:
    DynamicArray<T> data;  /// Динамический массив для хранения элементов кучи

    /**
     *  Просеивание вверх (восстановление свойства кучи при вставке).
     *  O(log n)
     */
    void bubble_up(size_t index) {
        while (index > 0) { // пока не дошли до корня
            size_t parent = (index - 1) / 2; // выразили формулу для нахождения индекса потомка
            if (data[index] < data[parent]) {  // если вставленный узел меньше по значению, чем его предок
                swap(data[index], data[parent]); // меняем их местами
                index = parent; // перезаписываем индекс вставленного узла
            }
            else {
                break;
            }
        }
    }

    /**
     *  Просеивание вниз (восстановление свойства кучи при удалении).
     *  O(log n)
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
    /// Конструктор по умолчанию
    Heap(size_t initial_capacity = 16) : data(initial_capacity) {}

   /**
        * Конструктор с параметрами
        * @param arr — объект DynamicArray<T>
        *  O(n)
        */
        Heap(const DynamicArray<T>&arr) : data(arr) {
        // Построение кучи за O(n)
        for (int i = (data.size()) / 2 - 1; i >= 0; --i) {
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
     *  Вставка элемента в кучу
     *  O(log n)
     */
    void insert(const T& value) {
        data.push_back(value);
        bubble_up(data.size() - 1);
    }

    /**
     *  Возвращает минимальный элемент (корень кучи)
     *  O(1)
     */
    const T& get_min() const {
        if (empty()) throw runtime_error("Куча пуста!");
        return data[0];
    }

    /**
     *  Удаление минимального элемента (корня кучи)
     *  O(log n)
     */
    void extract_min() {
        if (empty()) {
            cout << "Куча пуста!";
            return;
        }
        if (data.size() == 1) { // если куча состоит из одного корня
            data.pop_back(); // удаляем корень
            return; // завершаем работу метода
        }
        data[0] = data[data.size() - 1]; // ставим на место корня значение самого правого листа
        data.pop_back(); // удаляем сам лист
        trickle_down(0); // меняем корень на потомка с минимальным значением 
    }

    /**
 *  Поиск элемента в куче
 * @param value значение для поиска
 * @return индекс найденного элемента или -1, если элемент не найден
 *  O(n)
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
  *  Печатает кучу в виде дерева по уровням, с отступами
  * Элементы выровнены по центру
  *  O(n)
  */
    void print_tree() const {
        size_t n = data.size();
        if (empty()) {
            cout << "Куча пуста!\n";
            return;
        }

        // вычисляем количество уровней в дереве
        size_t levels = 0;
        for (size_t cnt = n; cnt > 0; cnt /= 2) levels++;

        size_t max_width = static_cast<size_t>(pow(2, levels)); // ширина строки (условная)

        size_t index = 0;
        for (size_t level = 0; level < levels; ++level) {
            size_t nodes_on_level = static_cast<size_t>(pow(2, level));  // сколько узлов на этом уровне
            size_t space_between = max_width / nodes_on_level; // расстояние между узлами

            // отступ перед первым элементом на уровне
            cout << string(space_between / 2, ' '); // отступ будет состоять из space_between / 2 пробелов

            for (size_t i = 0; i < nodes_on_level && index < n; ++i, ++index) {
                cout << data[index];
                // пробелы после элемента
                if (i != nodes_on_level - 1) {
                    cout << string(space_between - 1, ' ');
                }
            }
            cout << "\n\n"; 
        }
    }

    /**
     *  Печать значений кучи, хранящихся в динамическом массиве
     *  O(n)
     */
    void print() const {
        for (size_t i = 0; i < data.size(); i++)
            cout << data[i] << " ";
        cout << "\n";
    }


};

/**
 * Функция сортировки кучей (heap sort)
 * 1. Строит min-heap из массива.
 * 2. Извлекает минимальный элемент по одному, помещая его в конец массива.
 * 3. После завершения массив будет отсортирован по возрастанию.
 * O(n log n)
 */
template <typename T>
void heapSort(DynamicArray<T>& arr) {
    size_t n = arr.size();
    if (n <= 1) return; // уже отсортировано

    // построение min-heap 
    Heap<T> heap(arr);
    heap.print_tree();
    // извлекаем элементы по одному 
    for (size_t i = 0; i < n; ++i) {
        arr[i] = heap.get_min(); // минимальный элемент на текущей итерации
        heap.extract_min();      // удаляем его из кучи
    }
}

void test_heap_sort();
void test_insert();
void test_get_min();
void test_extract_min();
void test_find();
void test_size_and_empty();
void test_constructor_from_array();
void test_print();
void test_print_tree();