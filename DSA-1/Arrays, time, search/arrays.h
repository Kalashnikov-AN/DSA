// Автор: Калашников А.Н.
#pragma once
#include <iostream>
#include <random>   // библиотека для генерации случайных чисел
#include <fstream>
using namespace std;

/// Возвращает массив типа T* размера size с минимальным значением min_value и максимальным max_value
template <typename T>
T* createAndFillArray(size_t size, T min_value, T max_value) {
    // Объект для доступа к аппаратному или программному источнику случайности
    // нужен для инициализации генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value); // равномерное распределение

    T* array = new T[size];  // Создание массива

    for (size_t i = 0; i < size; ++i) {
        array[i] = distr(gen);  // Заполнение массива случайными числами
    }

    return array;

}

/// Возвращает монотонно возрастающий массив типа T* размера size с минимальным значением min_value 
template <typename T>
T* MonotonicallyIncreasingArray(size_t size, T min_value, T max_value) {
   // Объект для доступа к аппаратному или программному источнику случайности
    // нужен для инициализации генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());  // Генератор случайных чисел
    uniform_int_distribution<> distr(min_value, max_value); // равномерное распределение
    T* array = new T[size];  // Создание массива
    array[0] = distr(gen); // Нулевой элемент создаём случайным образом
    for (size_t i = 1; i < size; ++i) {
        // Заполнение массива случайными числами
        array[i] = array[i-1] + distr(gen)/10; // для монотонного возрастания к каждому следующему элементу прибавляем distr(gen)/10
      
    }
    return array;
}

/// Записывает массив array типа T* размера size в файл filename
template <typename T>
void array_to_file(T* array, size_t size, const string& filename) {
    ofstream f(filename); // Открываем файл на запись
    if (f.is_open()) {
        for (size_t i = 0; i < size; ++i) { 
            f << array[i] << " ";
        }
        f.close();
    }
}

// Возвращает булевое значение, отвечающее на вопрос, отсортирован массив array типа T* размера или нет
template <typename T>
bool is_sorted(T* array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (array[i] < array[i - 1]) { // Если каждый следующий массив меньше предыдущего
            return false;  // Если порядок нарушен
        }
    }
    return true; // Если массив отсортирован
}

/// Если элемент value найден алгоритмом последовательного поиска - возвращает индекс элемента в массиве array типа T* размера size
/// Если не найден - возвращает индекс на 1 больше крайнего индекса массива
template <typename T>
size_t sequential_search(T* array, size_t size, T value) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == value) { // Если элемент массива соответствует искомому
            return i;  // Возвращаем индекс найденного элемента
            
        }
    }
    return size;  // Если элемент не найден, возвращаем индекс на 1 больше последнего
}

/// Шаблонная рекурсивная функция бинарного поиска
/// Возвращает индекс элемента, если он найден, иначе -1
template <typename T>
int binary_search_recursive(T* array, size_t left, size_t right, T value) {
    if (left > right) {
        return -1; // Базовый случай: элемент не найден
    }

    size_t mid = left + (right - left) / 2; // Избегаем переполнения

    if (array[mid] == value) {
        return mid; // Найден элемент
    }
    else if (array[mid] < value) {
        return binary_search_recursive(array, mid + 1, right, value); // Ищем в правой части
    }
    else {
        return binary_search_recursive(array, left, mid - 1, value); // Ищем в левой части
    }
}

/// Тест функции сортировки массива is_sorted
void test_is_sorted();