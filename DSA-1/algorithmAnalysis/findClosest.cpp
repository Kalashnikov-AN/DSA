// Автор: Калашников А.Н.
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

/// Возвращает элемент массива arr размера n, наиболее близкий к заданному числу x.
/// Если в массиве несколько элементов с одинаковой минимальной разницей, возвращается первый найденный.
float findClosestElement(const float* arr, size_t n, float x) {
    // Инициализируем ближайший элемент первым элементом массива.
    float closest = arr[0];
    float minDiff = abs(arr[0] - x);

    // Если первый элемент точно равен x, можно сразу вернуть его (лучший случай: O(1)).
    if (minDiff == 0) {
        return closest;
    }

    // Перебираем оставшиеся элементы массива.
    // В худшем случае (когда ближайший элемент находится в конце) потребуется выполнить (n - 1) сравнений,
    // то есть временная сложность алгоритма O(n) при использовании одного цикла.
    for (size_t i = 1; i < n; i++) {
        float diff = abs(arr[i] - x);
        if (diff < minDiff) {
            minDiff = diff;
            closest = arr[i];
        }
    }
    return closest;
}

/// Функция для тестирования функции findClosestElement.
void testFindClosestElement() {
    {
        // Точное совпадение: x совпадает с элементом массива.
        float arr[] = { 1, 3, 5, 7, 9 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        float x = 5;
        assert(findClosestElement(arr, n, x) == 5);
    }
    {
        // Ближайший элемент находится в середине массива.
        float arr[] = { 1, 4, 6, 8, 10 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        float x = 7;
        // Разница для 6 и 8 равна 1, но функция вернет первый найденный, т.е. 6.
        assert(findClosestElement(arr, n, x) == 6);
    }
    {
        // Ближайший элемент — первый элемент массива.
        float arr[] = { 5, 10, 15, 20 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        float x = 2;
        assert(findClosestElement(arr, n, x) == 5);
    }
    {
        // Ближайший элемент — последний элемент массива.
        float arr[] = { 3, 6, 9, 12, 15 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        float x = 16;
        assert(findClosestElement(arr, n, x) == 15);
    }
    {
        // Массив с повторяющимися элементами.
        float arr[] = { 10, 20, 20, 30, 40 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        float x = 22;
        // Разница для 20 равна 2, для 30 равна 8, поэтому возвращается 20.
        assert(findClosestElement(arr, n, x) == 20);
    }
    {
        // Массив из одного элемента
        float arr[] = { 7 };
        size_t n = 1;
        float x = 1000;
        assert(findClosestElement(arr, n, x) == 7);
    }
    cout << "Все тесты для findClosestElement пройдены успешно" << endl;
}