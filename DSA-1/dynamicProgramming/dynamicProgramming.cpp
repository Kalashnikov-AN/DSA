// Автор: Калашников А.Н.

#include <iostream>
#include <locale>
#include "knight'sMove.h"

using namespace std;


int main() {

    setlocale(LC_ALL, "Russian");
    
    testCountPhoneNumbers();

    size_t N;
    cout << "Введите длину телефонного номера (N): ";
    cin >> N;
    size_t result = countPhoneNumbers(N);
    cout << "Для N = " << N << " количество номеров = " << result << endl;
   
}
