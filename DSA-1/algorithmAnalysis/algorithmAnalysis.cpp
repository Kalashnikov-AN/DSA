// Автор: Калашников А.Н.
#include <iostream>
#include <locale>
#include "findClosest.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    
    testFindClosestElement();

    
    const size_t n = 1'000'000; 
    float* largeArray = new float[n];

    // Заполняем массив значениями от 0 до n-1.
    for (size_t i = 0; i < n; i++) {
        largeArray[i] = i;
    }
    float x = n / 3;
  
    cout << "Найденный элемент: " << findClosestElement(largeArray, n, x) << endl;

    delete[] largeArray;
}
