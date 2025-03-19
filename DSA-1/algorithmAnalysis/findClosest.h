// Автор: Калашников А.Н.
#pragma once

/// Возвращает элемент массива arr размера n, наиболее близкий к заданному числу x.
/// Если в массиве несколько элементов с одинаковой минимальной разницей, возвращается первый найденный.
int findClosestElement(const int* arr, size_t n, int x);

/// Функция для тестирования функции findClosestElement.
void testFindClosestElement();