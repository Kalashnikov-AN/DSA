#include <cassert>
#include <iostream>
#include "PostfixCalculator.h"
using namespace std;

void testCalculator() {
    PostfixCalculator calc;

    // Тестирование базовых операций
    assert(calc.evaluate("3 4 +") == 7);
    assert(calc.evaluate("5 2 -") == 3);
    assert(calc.evaluate("6 3 *") == 18);
    assert(calc.evaluate("8 4 /") == 2);

    // Комбинированные выражения
    assert(calc.evaluate("5 1 2 + 4 * + 3 -") == 14); // 5 + (1+2)*4 -3 = 14
    assert((calc.evaluate("10 6 9 3 + -11 * / *") - -5/11) < 0.0000001); // 10 * (6 / ((9+3)*-11)) = -5/11

    // Десятичные числа и отрицательные значения
    assert(abs(calc.evaluate("3,5 2,5 +") == 6.0));
    assert(calc.evaluate("-3 5 *") == -15);

    // Тестирование исключений
    try {
        calc.evaluate("3 +");
        assert(false);
    }
    catch (const runtime_error& e) {
        assert(string(e.what()) == "Недостаточно операндов");
    }

    try {
        calc.evaluate("5 0 /");
        assert(false);
    }
    catch (const runtime_error& e) {
        assert(string(e.what()) == "Деление на ноль");
    }

    try {
        calc.evaluate("2 3 x");
        assert(false);
    }
    catch (const invalid_argument& e) {
        assert(string(e.what()) == "Недопустимый токен: x");
    }

    cout << "Все тесты калькулятора пройдены\n";
}
