// �����: ���������� �.�.
#pragma once
#include <stdexcept>
#include <iostream>
using namespace std;

/// ����� ��� ������� ������ DynamicArray
void runTests();

/// ����� ������������ ������ �� ��������� ���� T
template <typename T>
class DynamicArray {

private:
    // ��������� �� ����������� ���������� ������ ��������� ���� T
    T* _data;
    // ������� ���������� ��������� � �������
    size_t _size;
    //  ������� ����������������� ������ ��� �������
    size_t _capacity;

public:
    /**
     * ����������� ������ DynamicArray.
     * �������� ������������ ������ ��� ������� ��������� ���� T.
     * @param capacity ��������� ����������������� ������ ��� �������. �� ��������� ����� 10.
     */
    DynamicArray(size_t capacity = 10)
    {
        _size = 0;
        _capacity = capacity;
        _data = new T[_capacity];
    }

    /// ���������� 
    ~DynamicArray() {
        delete[] _data;
    }

    /// ����������� �����������, other - ���������� ������
    DynamicArray(const DynamicArray& other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        // ����������� �������� �����������
        for (size_t i = 0; i < _size; ++i)
            _data[i] = other._data[i];
    }

    /// �������� ������������ ������������, other - ���������� ������, ���������� ������ �� ������� �������� ������
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            // ����������� ������ ������
            delete[] _data;
            // �������� ������� � �������� ����� ������
            _capacity = other._capacity;
            _size = other._size;
            _data = new T[_capacity];
            // ����������� �������� �����������
            for (size_t i = 0; i < _size; ++i)
                _data[i] = other._data[i];
        }
        return *this;
    }

    /// ����������� �����������, other - rvalue ������ �� ������������ ������
    DynamicArray(DynamicArray&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    /// �������� ������������ ������������, other - rvalue ������ �� ������������ ������, ���������� ������ �� ������� �������� ������
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            // ����������� ������ ������
            delete[] _data;
            // ��������� ������ �� ������� �������
            _data = other._data;
            _size = other._size;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    /// ��������� ������ �������� newCapacity
    void reserve(size_t newCapacity) {
        if (newCapacity < _size)
            newCapacity = _size;  // ������ ��������� ���� �������� �������

        T* newData = new T[newCapacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
        _capacity = newCapacity;
    }

    /// ��������� ������ ������� �������� ������, �� ��������� ��� ������ 
    void clear() {
        // ���� ����� ��� nullptr � ������ ��� �������, ������ �� ������
        if (_data) {
            delete[] _data;
            _data = nullptr;
        }
        _size = 0;
        _capacity = 1;
        _data = new T[_capacity];
    }

    /// ���������� �������� value � ����� ������� 
    void push_back(const T& value) {
        if (_size == _capacity) { // ���� ������ ��������
            reserve(_capacity * 2); // ��������������� ������ ������������� ����� � 2 ����
        }                           // ����� �� �������� �������� ������ ��� �������� ������� ���������� ��������
        _data[_size++] = value;
    }

    /// �������� ���������� �������� �������
    void pop_back() {
        if (_size == 0)
            throw underflow_error("������ ����");
        --_size;
        // ���� ������ ����� 1/4 ���������� ������
        if (_size > 0 && _size < _capacity / 4) {
            reserve(_capacity / 2); // ��������������� ������ ����������� ����� � 2 ����
        }
    }

    /// ������ �� �������
    T& operator[](size_t index) {
        if (index >= _size)
            throw out_of_range("������ ��� ���������");
        return _data[index];
    }

    /// ����������� ������ �� �������
    const T& operator[](size_t index) const {
        if (index >= _size)
            throw out_of_range("������ ��� ���������");
        return _data[index];
    }

    /// ���������� ������� ���-�� ��������� �������
    size_t size() const {
        return _size;
    }

    /// ���������� ������� ������ ���������� ��� ������ ������
    size_t capacity() const {
        return _capacity;
    }


};