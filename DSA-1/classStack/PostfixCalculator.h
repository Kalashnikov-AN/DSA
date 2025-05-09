#pragma once
#include "stack.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
using namespace std;

class PostfixCalculator {
private:
    stack<double> operandStack; // ���� ��� �������� ���������

    // ��������, �������� �� ����� ����������
    bool isOperator(const string& token) const {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    // ���������� ��������
    double applyOperator(const string& op, double a, double b) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("������� �� ����");
            return a / b;
        }
        throw invalid_argument("����������� ��������");
    }

public:
    // ���������� ������������ ���������
    double evaluate(const string& expression) {
        operandStack.clear();
        istringstream iss(expression);
        string token;

        while (iss >> token) {
            if (isOperator(token)) {
                if (operandStack.size() < 2) {
                    throw runtime_error("������������ ���������");
                }
                double b = operandStack.pop();
                double a = operandStack.pop();
                double result = applyOperator(token, a, b);
                operandStack.push(result);
            }
            else {
                // ������� ������������� ����� � �����
                try {
                    size_t pos;
                    double num = stod(token, &pos); //todo: ��������� � stod
                    if (pos != token.size()) {
                        throw invalid_argument("������ � �����");
                    }
                    operandStack.push(num);
                }
                catch (...) {
                    throw invalid_argument("������������ �����: " + token);
                }
            }
        }

        if (operandStack.size() != 1) {
            throw runtime_error("������������ ���������");
        }

        return operandStack.peek();
    }
};

void testCalculator();