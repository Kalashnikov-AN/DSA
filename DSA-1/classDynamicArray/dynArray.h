// Автор: Калашников А.Н.
#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

/// Тесты для методов класса DynamicArray
void runTests();

void test_push_pop_front();

void test_insert_at();

void test_remove_at();

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

    /// Выполняет полную очистку хранимых данных, но оставляет сам объект 
    void clear() {
        // Если буфер уже nullptr — значит уже очищено, ничего не делаем
        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
        _size = 0;
        _capacity = 1;
        _data = new T[_capacity];
    }

    /// Добавление элемента value в конец массива 
    void push_back(const T& value) {
        if (_size == _capacity) { // Если массив заполнен
            reserve(_capacity * 2); // Резервированная память увеличивается сразу в 2 раза
        }                           // чтобы не пришлось выделять память при создании каждого следующего элемента
        _data[_size++] = value;
    }

    /// Удаление последнего элемента массива
    void pop_back() {
        if (_size == 0)
            throw underflow_error("Массив пуст");
        --_size;
        // Если занято менее 1/4 выделенной памяти
        if (_size > 0 && _size < _capacity / 4) {
            reserve(_capacity / 2); // Резервированная память уменьшается сразу в 2 раза
        }
    }

    /**
    * Добавление элемента в начало
    * @param value значение для вставки
    */
    void push_front(const T& value) {
        if (_size == _capacity) reserve(_capacity * 2);
        // сдвинуть вправо
        for (size_t i = _size; i > 0; --i)
            _data[i] = _data[i - 1];
        _data[0] = value;
        ++_size;
    }

    /**
      Удаление элемента из начала
     */
    void pop_front() {
        if (_size == 0) throw underflow_error("Array is empty");
        // сдвинуть влево
        for (size_t i = 1; i < _size; ++i)
            _data[i - 1] = _data[i];
        --_size;
        if (_size > 0 && _size < _capacity / 4) reserve(_capacity / 2);
    }

    /**
     * Вставка элемента по индексу 
     * @param index позиция (0..size)
     * @param value значение для вставки
     * @throw out_of_range если индекс > size
     */
    void insert_at(size_t index, const T& value) {
        if (index > _size) throw out_of_range("Index out of range");
        if (index == 0) return push_front(value);
        if (index == _size) return push_back(value);
        if (_size == _capacity) reserve(_capacity * 2);
        // сдвинуть часть массива
        for (size_t i = _size; i > index; --i)
            _data[i] = _data[i - 1];
        _data[index] = value;
        ++_size;
    }

    /**
     *  Удаление элемента по индексу 
     * @param index позиция (0..size-1)
     * @throw out_of_range если индекс >= size
     */
    void remove_at(size_t index) {
        if (index >= _size) throw out_of_range("Index out of range");
        if (index == 0) return pop_front();
        if (index == _size - 1) return pop_back();
        // сдвинуть оставшуюся часть
        for (size_t i = index + 1; i < _size; ++i)
            _data[i - 1] = _data[i];
        --_size;
        if (_size > 0 && _size < _capacity / 4) reserve(_capacity / 2);
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