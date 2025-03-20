// Автор: Калашников А.Н.
#pragma once

/// Возвращает элемент массива arr размера n, наиболее близкий к заданному числу x.
/// Если в массиве несколько элементов с одинаковой минимальной разницей, возвращается первый найденный.
float findClosestElement(const float* arr, size_t n, float x);

/// Функция для тестирования функции findClosestElement.
void testFindClosestElement();