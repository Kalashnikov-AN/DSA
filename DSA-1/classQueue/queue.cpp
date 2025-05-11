#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"
using namespace std;
// Автор: Калашников А.Н.

/// Тесты для класса очередь
void testQueue() {
    
    // Конструктор по умолчанию
    Queue<int> q;

    // Проверка isEmpty и size
    assert(q.isEmpty());
    assert(q.size() == 0);

    // Добавление элемента
    q.enqueue(10);
    assert(q.front() == 10);
    assert(q.size() == 1);

    // Снова добавление элемента
    q.enqueue(20);
    assert(q.front() == 10);
    assert(q.size() == 2);

    // Удаление элемента 
    q.dequeue();
    assert(q.front() == 20);
    assert(q.size() == 1);

    // Очистка очереди
    q.clear();
    assert(q.isEmpty());

    // Очистка пустой очереди
    assert(q.isEmpty());
    q.clear();
    assert(q.isEmpty());

    // Проверка исключений
    try {
        q.front();
        assert(false);
    }
    catch (const underflow_error& e) {
        assert(string(e.what()) == "Очередь пуста");
    }

    try {
        q.dequeue();
        assert(false);
    }
    catch (const underflow_error& e) {
        assert(string(e.what()) == "Очередь пуста");
    }

    // Конструктор копирования
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    Queue<int> q2(q1);
    assert(q2.size() == 2);
    assert(q2.front() == 1);

    // Оператор присваивания копированием
    Queue<int> q3;
    q3 = q2;
    assert(q3.front() == 1);

    // Конструктор перемещения
    Queue<int> q4(move(q2));
    assert(q4.size() == 2); // q2 имел 2 элемента
    assert(q2.size() == 0); // После перемещения исходная очередь должна быть пуста
    
    // Оператор присваивания перемещением
    Queue<int> q5 = move(q3);
    assert(q5.size() == 2); // q3 имел 2 элемента
    assert(q3.isEmpty()); // После перемещения исходная очередь должна быть пуста

    // Тест 7: Строки
    Queue<string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    assert(strQueue.front() == "Hello");
    strQueue.dequeue();
    assert(strQueue.front() == "World");

    cout << "Все тесты пройдены успешно" << endl;
}
