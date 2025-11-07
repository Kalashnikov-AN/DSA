// Автор: Калашников А.Н.

#include <iostream>
#include <vector>
#include <algorithm>    

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // Исходный вектор
    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // for_each 
    // Применяет функцию ко всем элементам контейнера
    cout << "Элементы массива: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        cout << n << " ";
        });
    cout << "\n";

    // any_of / all_of / none_of 
    // Проверяют выполнение логического условия хотя бы для одного / всех / ни одного элемента
    bool has_even = any_of(numbers.begin(), numbers.end(), [](int n) { return n % 2 == 0; });

    bool all_positive = all_of(numbers.begin(), numbers.end(), [](int n) { return n > 0; });

    bool none_negative = none_of(numbers.begin(), numbers.end(), [](int n) { return n < 0; });

    cout << "Есть ли хотя бы одно четное число? " << (has_even ? "Да" : "Нет") << "\n";

    cout << "Все ли числа положительные? " << (all_positive ? "Да" : "Нет") << "\n";

    cout << "Нет ли отрицательных чисел? " << (none_negative ? "Да" : "Нет") << "\n";

    // transform 
    // Преобразует каждый элемент по заданному правилу и записывает результат в новый контейнер
    vector<int> squares(numbers.size());
    transform(numbers.begin(), numbers.end(), squares.begin(), [](int n) {
        return n * n;
        });

    cout << "Квадраты элементов: ";

    for (auto x : squares) {
        cout << x << " ";
    }
    cout << "\n";

    // copy_if 
    // Копирует только те элементы, которые удовлетворяют условию
    vector<int> even_numbers;
    copy_if(numbers.begin(), numbers.end(), back_inserter(even_numbers), [](int n) {
        return n % 2 == 0; // предикат
        }); //todo: комменты foreach, copy_if. Какая функция подойдет. В copy_if предикат, а в for_each нет и тд

    cout << "Только четные числа: ";
    for (auto x : even_numbers) {
        for (auto x : even_numbers) {
            cout << x << " ";
        }
        cout << "\n";

    }
}
