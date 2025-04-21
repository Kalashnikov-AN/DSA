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

    // Тест удаления элемента из пустого массива
    DynamicArray<int> arrEmpty(0);
    try {
        arrEmpty.pop_back();
        assert(false);
    }

    // Ожидается исключение
    catch (const underflow_error&) {

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

/// Тест для push_front и pop_front
void test_push_pop_front() {
    DynamicArray<int> a(2);
    assert(a.size() == 0);

    // push_front для пустого массива
    a.push_front(10);
    assert(a.size() == 1);
    assert(a[0] == 10);

   
    a.push_front(20); // [20,10]
    assert(a.size() == 2);
    assert(a[0] == 20);
    assert(a[1] == 10);

    // pop_front удаляет первый элемент из двух
    a.pop_front();    // [10]
    assert(a.size() == 1);
    assert(a[0] == 10);

    // pop_front для массива из 1 элемента
    a.pop_front();    
    assert(a.size() == 0);

    // pop_front для пустого массива
    bool caught = false;
    try {
        a.pop_front();
    }
    catch (const underflow_error&) {
        caught = true;
    }
    assert(caught);

}

/// Тест для insert_at
void test_insert_at() {
    DynamicArray<string> a(2);

    // insert_at в 0-ую позицию пустого массива
    a.insert_at(0, "A");    // ["A"]
    assert(a.size() == 1);
    assert(a[0] == "A");

    // insert_at в конец массива (index == size)
    a.insert_at(1, "C");    // ["A","C"]
    assert(a.size() == 2);
    assert(a[1] == "C");

    // insert_at для середины массива
    a.insert_at(1, "B");    // ["A","B","C"]
    assert(a.size() == 3);
    assert(a[0] == "A" && a[1] == "B" && a[2] == "C");

    // insert_at для некорректного индекса
    bool caught = false;
    try {
        a.insert_at(4, "X");
    }
    catch (const out_of_range&) {
        caught = true; }
    assert(caught);

}

/// Тест для remove_at
void test_remove_at() {
    DynamicArray<char> a(4);
    a.push_back('x');
    a.push_back('y');
    a.push_back('z');
    a.push_back('w');  // ['x','y','z','w']

    // remove_at для первого элемента
    a.remove_at(0);    // ['y','z','w']
    assert(a.size() == 3);
    assert(a[0] == 'y');

    // remove_at для последнего элемента
    a.remove_at(a.size() - 1); // ['y','z']
    assert(a.size() == 2);
    assert(a[1] == 'z');

    // remove_at для середины массива
    a.push_back('u');  // ['y','z','u']
    a.remove_at(1);    // ['y','u']
    assert(a.size() == 2);
    assert(a[0] == 'y' && a[1] == 'u');

    // remove_at для некорректного индекса
    bool caught = false;
    try {
        a.remove_at(5); }
    catch (const out_of_range&) {
        caught = true; }
    assert(caught);
}