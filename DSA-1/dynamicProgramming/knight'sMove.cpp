﻿// Автор: Калашников А.Н.

#include <iostream>
#include <vector>
#include <algorithm> // для fill
#include <cassert>
using namespace std;

/*
8. Задача Ход конем
Шахматная ассоциация решила оснастить всех своих сотрудников такими телефонными номерами, которые бы набирались на кнопочном телефоне
ходом коня. Например, ходом коня набирается телефон 340-49-27. При этом телефонный номер не может начинаться ни с цифры 0, ни с цифры 8.
     7   8   9
     4   5   6
     1   2   3
         0
Напишите программу, определяющую количество телефонных номеров длины N, набираемых ходом коня.
*/

/// Возвращает количество телефонных номеров длины N, набираемых ходом коня.
size_t countPhoneNumbers(size_t N) {
    // 0 -> {4, 6}
    // 1 -> {6, 8}
    // 2 -> {7, 9}
    // 3 -> {4, 8}
    // 4 -> {0, 3, 9}
    // 5 -> {}  (из 5 ходов нет)
    // 6 -> {0, 1, 7}
    // 7 -> {2, 6}
    // 8 -> {1, 3}
    // 9 -> {2, 4}
    // Ходы коня для каждой цифры 
    vector<vector<size_t>> moves = {
        {4, 6},    // 0
        {6, 8},    // 1
        {7, 9},    // 2
        {4, 8},    // 3
        {0, 3, 9}, // 4
        {},        // 5
        {0, 1, 7}, // 6
        {2, 6},    // 7
        {1, 3},    // 8
        {2, 4}     // 9
    };

    // Храним только предыдущий и текущий вектор с количеством возможных номеров
    vector<size_t> prev(10, 0), cur(10, 0);

    // Вектор для номера длины 1
    for (size_t d = 0; d < 10; d++) {
        if (d != 0 && d != 8)
            prev[d] = 1;
        else
            prev[d] = 0;
    }

    // Для каждой длины номера пересчитываем кол-во возможных номеров
    for (size_t i = 2; i <= N; i++) {
        // Обнуляем текущий вектор
        fill(cur.begin(), cur.end(), 0);
        // Для каждой цифры p из предыдущего разряда, переходим по всем допустимым ходам p -> d.
        for (size_t p = 0; p < 10; p++) {
            for (size_t d : moves[p]) {
                cur[d] += prev[p];
            }
        }
        // Текущий вектор становится предыдущим для следующей итерации
        prev = cur;
    }

    // Ответ – сумма всех способов получить номер длины N
    size_t ans = 0;
    for (size_t d = 0; d < 10; d++) {
        ans += prev[d];
    }
    return ans;
}

/// Тестирование функции countPhoneNumbers.
void testCountPhoneNumbers() {

    // Тест для длины N = 1
    assert(countPhoneNumbers(1) == 8);

    // Тест для длины N = 2
    assert(countPhoneNumbers(2) == 16);

    // Тест для длины N = 10
    assert(countPhoneNumbers(10) == 11728);

    // Тест для длины N = 100
    assert(countPhoneNumbers(100) == 1860549596057436160);
    
    cout << "Все тесты для countPhoneNumbers пройдены успешно" << endl;
}