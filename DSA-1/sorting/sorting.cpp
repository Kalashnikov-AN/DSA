#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
// Автор: Калашников А.Н.
int main() {
    setlocale(LC_ALL, "Russian");

    srand(9 * 42);
    int size = rand() % 11 + 10; // Размер 10-20
    cout << "Размер: " << size << endl;
    vector<int> arr(size);
    cout << "Исходный массив: ";
    for (int& num : arr) {
        num = rand() % 31;
        cout << num << " ";
    }
    cout << "\n";

    int sortType = rand() % 3;
    switch (sortType) {
    case 0:
        cout << "Выбрана быстрая сортировка\n";
        break;
    case 1:
        cout << "Выбрана сортировка слиянием\n";
        break;
    case 2:
        cout << "Выбрана сортировка Шелла\n";
        break;
    }

}