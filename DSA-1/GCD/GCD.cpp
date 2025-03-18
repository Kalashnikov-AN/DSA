// Автор: Калашников А.Н.

#include <iostream>
#include <cassert>
#include <locaLe>
#include "calculate.h"
using namespace std;

// Задание: 8. Найти НОД (наибольший общий делитель) двух натуральных чисел.


int main() {
    setlocale(LC_ALL, "Russian");
    testGCD(); // Запуск тестов для функции gcd
    cout << gcd(18, 27) << endl;
    cout << gcd(123, 456) << endl;
    cout << gcd(128, 1024) << endl;
}