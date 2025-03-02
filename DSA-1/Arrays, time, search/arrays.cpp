// Автор: Калашников А.Н.
#include <iostream>
#include <random>   // библиотека для генерации случайных чисел
#include <cassert>
#include "arrays.h"
using namespace std;

/// Тест функции сортировки массива is_sorted
void test_is_sorted() {

    // Отсортированные массивы
    int arr_sorted1[] = { 1, 2, 3, 4, 5 }; // Только  положительные элементы
    int arr_sorted2[] = { -5, -3, -1, 0, 2, 4, 6 }; // И положительные, и отрицательные элементы
    int arr_sorted3[] = { 10 }; // Один элемент
    int* arr_sorted4 = nullptr; // Пустой массив
    

    assert(is_sorted(arr_sorted1, 5) == true);
    assert(is_sorted(arr_sorted2, 7) == true);
    assert(is_sorted(arr_sorted3, 1) == true);
    assert(is_sorted(arr_sorted4, 0) == true);

    // Неотсортированные массивы
    int arr_unsorted1[] = { 1, 3, 2, 4, 5 };
    int arr_unsorted2[] = { 5, 4, 3, 2, 1 }; // Обратный порядок
    int arr_unsorted3[] = { 10, 10, 9, 10 }; // Повторяющиеся элементы, но не по порядку
    int arr_unsorted4[] = { -1, -2, -3, 0 }; 

    assert(is_sorted(arr_unsorted1, 5) == false);
    assert(is_sorted(arr_unsorted2, 5) == false);
    assert(is_sorted(arr_unsorted3, 4) == false);
    assert(is_sorted(arr_unsorted4, 4) == false);

    // Массив с одинаковыми элементами
    int arr_same_elements[] = { 5, 5, 5, 5, 5 };
    assert(is_sorted(arr_same_elements, 5) == true);

    // Массив с парой одинаковых соседних элементов
    int arr_with_duplicates[] = { 1, 2, 2, 3, 4 };
    assert(is_sorted(arr_with_duplicates, 5) == true);

}

/// Функция тестирования последовательного поиска
void test_sequential_search() {

    // Массив для тестирования функции
    int arr1[] = { 10, 20, 30, 40, 50 };
    // Размер массива
    size_t size1 = 5;

    // Элемент находится в середине
    assert(sequential_search(arr1, size1, 30) == 2);

    // Элемент в начале
    assert(sequential_search(arr1, size1, 10) == 0);

    // Элемент в конце
    assert(sequential_search(arr1, size1, 50) == 4);

    // Элемента нет в массиве 
    assert(sequential_search(arr1, size1, 5) == size1);

    // Элемента нет в массиве 
    assert(sequential_search(arr1, size1, 60) == size1);

    // Элемента нет в массиве 
    assert(sequential_search(arr1, size1, 35) == size1);

    // Поиск в массиве из одного элемента (найден)
    int arr2[] = { 100 };
    assert(sequential_search(arr2, 1, 100) == 0);

    // Поиск в массиве из одного элемента (не найден)
    assert(sequential_search(arr2, 1, 200) == 1);

}

/// Тест функции бинарного поиска
void test_binary_search() {
    // Массив для тестирования функции
    int sorted_array[] = { 1, 3, 5, 7, 9, 11, 13, 15 };
    // Размер массива
    size_t size_test = 8;
    // Элемент в середине
    assert(binary_search_recursive<int>(sorted_array, 0, size_test -1, 7) == 3);

    // Первый элемент
    assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 1) == 0);

    // Последний элемент
    assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 15) == 7);

    // Отсутствующий элемент
    assert(binary_search_recursive<int>(sorted_array, 0, size_test - 1, 8) == -1);

    // Поиск в массиве из одного элемента
    int one_element_array[] = { 42 };
    assert(binary_search_recursive<int>(one_element_array, 0, 0, 42) == 0);
    assert(binary_search_recursive<int>(one_element_array, 0, 0, 0) == -1);
}

/// Последовательность Шелла (обычная) - шаг уменьшается в 2 раза
size_t shellGap(size_t size, size_t prevGap) {
    return prevGap == 0 ? size / 2 : prevGap / 2;
}
