// Автор: Калашников А.Н.
#include <iostream>
#include <cassert>
#include "dynArray.h"
using namespace std;

/// Тесты для методов класса DynamicArray
void runTests() {

    // Тест конструктора и базовых операций
    DynamicArray<int> arr(5);
    assert(arr.size() == 0);
    assert(arr.capacity() == 5);

    // Тест push_back и оператора []
    for (int i = 0; i < 10; i++) {
        arr.push_back(i * 10);
    }
    assert(arr.size() == 10);
    // Если массив изначально имел емкость 5, после переполнения емкость должна увеличиться 
    assert(arr.capacity() >= 10);
    for (int i = 0; i < 10; i++) {
        assert(arr[i] == i * 10);
    }

    // Тест копирования 
    DynamicArray<int> copyArr = arr;  // конструктор копирования
    assert(copyArr.size() == arr.size());
    for (size_t i = 0; i < arr.size(); i++) {
        assert(copyArr[i] == arr[i]);
    }

    // Изменим оригинальный массив и проверим, что копия не изменилась ( проверка глубокого копирования )
    arr[0] = 999;
    assert(copyArr[0] != arr[0]);

    // Тест оператора присваивания
    DynamicArray<int> assignArr;
    assignArr = arr; // присваивание копированием
    assert(assignArr.size() == arr.size());
    for (size_t i = 0; i < arr.size(); i++) {
        assert(assignArr[i] == arr[i]);
    }

    // Тест pop_back и автоматического уменьшения выделенной под массив памяти
    size_t previousCapacity = arr.capacity();
    for (int i = 0; i < 8; i++) {
        arr.pop_back();
    }
    
    // Количество элементов массива уменьшилось
    assert(arr.size() == 2);

    // Поскольку после удаления большого количества элементов резерв памяти мог уменьшиться
    assert(arr.capacity() <= previousCapacity);

    // Тест доступа по индексу c проверкой исключения
    try {
        int temp = arr[100]; // должно вызвать исключение
        assert(false); // сюда выполнение не должно дойти
    }

    // Ожидается исключение
    catch (const out_of_range&) {
       
    }

    // Создание массива и добавление элементов
    DynamicArray<int> arrClear(5);
    arrClear.push_back(10);
    arrClear.push_back(20);
    arrClear.push_back(30);

    // Проверка начального состояния
    assert(arrClear.size() == 3);
    assert(arrClear.capacity() >= 3);

    // Вызов clear()
    arrClear.clear();

    // Проверка состояния после очистки
    assert(arrClear.size() == 0);

    // Попытка доступа по индексу должна вызвать исключение
    try {
        int value = arrClear[0];
        assert(false); // не должно достигаться
    }
    catch (const out_of_range&) {
        // Ожидаемое поведение
    }
    
    // Повторный вызов clear() не должен вызывать ошибок
    arrClear.clear();
    assert(arrClear.size() == 0);

    // Повторное добавление элементов после очистки
    arrClear.push_back(42);
    assert(arrClear.size() == 1);
    assert(arrClear[0] == 42);

    cout << "Все тесты пройдены успешно" << endl;
}