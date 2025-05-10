#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

void testQueue() {
    // Тест 1: Базовая работа очереди
    Queue<int> q;
    assert(q.isEmpty());
    assert(q.size() == 0);

    q.enqueue(10);
    assert(q.front() == 10);
    assert(q.size() == 1);

    q.enqueue(20);
    assert(q.front() == 10);
    assert(q.size() == 2);

    q.dequeue();
    assert(q.front() == 20);
    assert(q.size() == 1);

    // Тест 2: Очистка очереди
    q.clear();
    assert(q.isEmpty());
    // Очистка пустой очереди
    q.clear();

    // Тест 3: Исключения
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

    // Тест 4: Конструктор копирования
    Queue<int> q2;
    q2.enqueue(1);
    q2.enqueue(2);
    Queue<int> q3(q2);
    assert(q3.size() == 2);
    assert(q3.front() == 1);

    // Тест 5: Присваивание копированием
    Queue<int> q4;
    q4 = q3;
    assert(q4.front() == 1);
    q4.dequeue();
    assert(q4.front() == 2);

    // Тест 6: Перемещение
    Queue<int> q5 = move(q4);
    assert(q5.size() == 1);
    assert(q4.isEmpty());

    // Тест 7: Строки
    Queue<string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    assert(strQueue.front() == "Hello");
    strQueue.dequeue();
    assert(strQueue.front() == "World");

    cout << "Все тесты пройдены успешно" << endl;
}
