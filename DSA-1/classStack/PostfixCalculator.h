#pragma once
#include "stack.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
using namespace std;

class PostfixCalculator {
private:
    stack<double> operandStack; // Стек для хранения операндов

    // Проверка, является ли токен оператором
    bool isOperator(const string& token) const {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    // Выполнение операции
    double applyOperator(const string& op, double a, double b) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("Деление на ноль");
            return a / b;
        }
        throw invalid_argument("Неизвестный оператор");
    }

public:
    // Вычисление постфиксного выражения
    double evaluate(const string& expression) {
        operandStack.clear();
        istringstream iss(expression);
        string token;

        while (iss >> token) {
            if (isOperator(token)) {
                if (operandStack.size() < 2) {
                    throw runtime_error("Недостаточно операндов");
                }
                double b = operandStack.pop();
                double a = operandStack.pop();
                double result = applyOperator(token, a, b);
                operandStack.push(result);
            }
            else {
                // Пробуем преобразовать токен в число
                try {
                    size_t pos;
                    double num = stod(token, &pos); //todo: разобрать в stod
                    if (pos != token.size()) {
                        throw invalid_argument("Ошибка в числе");
                    }
                    operandStack.push(num);
                }
                catch (...) {
                    throw invalid_argument("Недопустимый токен: " + token);
                }
            }
        }

        if (operandStack.size() != 1) {
            throw runtime_error("Некорректное выражение");
        }

        return operandStack.peek();
    }
};

void testCalculator();