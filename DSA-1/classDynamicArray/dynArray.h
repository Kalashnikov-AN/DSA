#pragma once
#include <stdexcept>
using namespace std;

/// Тесты для методов класса DynamicArray
void runTests();

/// Класс динамический массив из элементов типа T
template <typename T>
class DynamicArray {

private:
    // Указатель на динамически выделенный массив элементов типа T
    T* _data;
    // Текущее количество элементов в массиве
    size_t _size;
    //  Текущая зарезервированная память для массива
    size_t _capacity;

public:
    /**
     * Конструктор класса DynamicArray.
     * Выделяет динамическую память для массива элементов типа T.
     * @param capacity Начальная зарезервированная память для массива. По умолчанию равна 10.
     */
    DynamicArray(size_t capacity = 10)
    {
        _size = 0;
        _capacity = capacity;
        _data = new T[_capacity];
    }

    /// Деструктор 
    ~DynamicArray() {
        delete[] _data;
    }

    /// Конструктор копирования, other - копируемый объект
    DynamicArray(const DynamicArray& other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        // Реализуется глубокое копирование
        for (size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }

    /// Оператор присваивания копированием, other - копируемый объект, возвращает ссылку на измённый исходный объект
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            // Освобождаем старую память
            delete[] _data;
            // Копируем размеры и выделяем новую память
            _capacity = other._capacity;
            _size = other._size;
            _data = new T[_capacity];
            // Реализуется глубокое копирование
            for (size_t i = 0; i < _size; ++i)
                _data[i] = other._data[i];
        }
        return *this;
    }

    /// Конструктор перемещения, other - rvalue ссылка на перемещаемый объект
    DynamicArray(DynamicArray&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    /// Оператор присваивания перемещением, other - rvalue ссылка на перемещаемый объект, возвращает ссылку на измённый исходный объект
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            // Освобождаем старую память
            delete[] _data;
            // Переносим данные из другого объекта
            _data = other._data;
            _size = other._size;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    /// Выделение памяти размером newCapacity
    void reserve(size_t newCapacity) {
        if (newCapacity < _size)
            newCapacity = _size;  // нельзя уменьшить ниже текущего размера

        T* newData = new T[newCapacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
        _capacity = newCapacity;
    }

    /// Добавление элемента value в конец массива 
    void push_back(const T& value) {
        if (_size == _capacity) { // Если массив заполнен, увеличиваем емкость
            reserve(_capacity * 2);
        }
        _data[_size++] = value;
    }

    /// Удаление последнего элемента массива
    void pop_back() {
        if (_size == 0)
            throw underflow_error("Массив пуст");
        --_size;
        // При удалении большого количества элементов можно уменьшать резерв памяти
        if (_size > 0 && _size < _capacity / 4) {
            reserve(_capacity / 2);
        }
    }

    /// Доступ по индексу
    T& operator[](size_t index) {
        if (index >= _size)
            throw out_of_range("Индекс вне диапазона");
        return _data[index];
    }

    /// Константный доступ по индексу
    const T& operator[](size_t index) const {
        if (index >= _size)
            throw out_of_range("Индекс вне диапазона");
        return _data[index];
    }

    /// Возвращает текущее кол-во элементов массива
    size_t size() const {
        return _size;
    }

    /// Возвращает текущий размер выделенной под массив памяти
    size_t capacity() const {
        return _capacity;
    }


};