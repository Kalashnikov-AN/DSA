#pragma once
#include "stack.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
using namespace std;
// Автор: Калашников А.Н.

/// Класс стекового(постфиксного) калькулятора
class PostfixCalculator {
private:
    /// Стек для хранения операндов постфиксного выражения
    stack<double> operandStack; 

    /// Проверяет, является ли token оператором.
    /// Возвращает true/false
    bool isOperator(const string token) const {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    /// Выполнение операции op для операндов a и b, возвращает ответ типа double
    double applyOperator(const string op, double a, double b) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("Деление на ноль");
            return a / b;
        }
        throw invalid_argument("Неизвестный оператор"); // если не подошёл ни один оператор
    }

public:
    /// Вычисление значения постфиксного выражения expression, возвращает ответ типа double
    double evaluate(const string expression) {
        // Очищаем стек операндов перед вычислением нового выражения
        operandStack.clear();
        // Создаем поток для чтения токенов из строки
        istringstream iss(expression);
        string token;

        while (iss >> token) {
            if (isOperator(token)) {
                // Проверка наличия минимум двух операндов в стеке
                if (operandStack.size() < 2) {
                    throw runtime_error("Недостаточно операндов");
                }
                // Извлекаем операнды из стека в обратном порядке
                double b = operandStack.pop();
                double a = operandStack.pop();
                // Применяем оператор
                double result = applyOperator(token, a, b);
                // Помещаем результат в стек для последующих операций
                operandStack.push(result);
            }
            else {
                // Пробуем преобразовать токен в число
                try {
                    size_t pos;
                    double num = stod(token, &pos); // преобразуем token в число num. в pos запишется кол-во обработанных символов
                    // Проверяем, что вся строка была преобразована
                    if (pos != token.size()) {
                        throw invalid_argument("Ошибка в числе");
                    }
                    // Корректное число добавляем в стек
                    operandStack.push(num);
                }
                catch (...) {
                    throw invalid_argument("Недопустимый токен: " + token);
                }
            }
        }

        // В стеке должен остаться ровно один элемент - результат вычислений
        if (operandStack.size() != 1) {
            throw runtime_error("Некорректное выражение");
        }

        // Возвращаем итоговый результат с вершины стека
        return operandStack.peek();
    }
};

void testCalculator();