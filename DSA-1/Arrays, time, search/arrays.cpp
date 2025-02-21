#include <iostream>
#include <random>   // библиотека для генерации случайных чисел
#include <cassert>
#include "arrays.h"
using namespace std;

/// Тест функции сортировки массива is_sorted
void test_is_sorted() {
    size_t size = 5;
    int arr_sorted[] = {1, 2, 3, 4, 5};
    int arr_unsorted[] = {1, 3, 2, 4, 5};

    assert(is_sorted(arr_sorted, size) == true);  // Массив отсортирован
    assert(is_sorted(arr_unsorted, size) == false);  // Массив не отсортирован
}