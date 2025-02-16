#pragma once
#include <iostream>
#include <random>   // библиотека для генерации случайных чисел
#include <fstream>
using namespace std;

template <typename T>
T* createAndFillArray(size_t size, T min_value, T max_value) {
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value);

    T* array = new T[size];  // Создание массива

    for (size_t i = 0; i < size; ++i) {
        array[i] = distr(gen);  // Заполнение массива случайными числами
    }

    return array;

}

template <typename T>
T* MonotonicallyIncreasingArray(size_t size, T min_value, T max_value) {
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value);
    T* array = new T[size];  // Создание массива
    array[0] = distr(gen);
    for (size_t i = 1; i < size; ++i) {
        array[i] = array[i-1] + distr(gen)/10;
       // cout << array[i] << "\n";
    }
    return array;
}

template <typename T>
void array_to_file(T* array, size_t size, const string filename) {
    ofstream f(filename);
    if (f.is_open()) {
        for (size_t i = 0; i < size; ++i) {
            f << array[i] << " ";
        }
        f.close();
    }
}

template <typename T>
bool is_sorted(T* array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (array[i] < array[i - 1]) {
            return false;  // Если порядок нарушен
        }
    }
    return true;
}

template <typename T>
int sequential_search(T* array, size_t size, T value) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == value) {
            return i;  // Индекс найденного элемента
            cout << "YES\N";
        }
    }
    return -1;  // Если элемент не найден
}