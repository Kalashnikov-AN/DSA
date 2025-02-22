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

