#include <iostream>
using namespace std;

long long counter; // Счётчик вызовов рекурсии

/// Функция для измерения глубины стека
void recursiveFunction() {
    ++counter; // Инкрементируем счётчик вызовов рекурсии
    cout << "Stack depth: " << counter << endl;

    // Вызываем функцию рекурсивно, пока не произойдет переполнение стека
    recursiveFunction();

}

int main() {
        recursiveFunction(); // Вызываем функцию рекурсивно, пока не произойдет переполнение стека
    
}