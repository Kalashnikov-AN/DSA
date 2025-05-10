#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

void testQueue() {
    // ���� 1: ������� ������ �������
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

    // ���� 2: ������� �������
    q.clear();
    assert(q.isEmpty());
    // ������� ������ �������
    q.clear();

    // ���� 3: ����������
    try {
        q.front();
        assert(false);
    }
    catch (const underflow_error& e) {
        assert(string(e.what()) == "������� �����");
    }

    try {
        q.dequeue();
        assert(false);
    }
    catch (const underflow_error& e) {
        assert(string(e.what()) == "������� �����");
    }

    // ���� 4: ����������� �����������
    Queue<int> q2;
    q2.enqueue(1);
    q2.enqueue(2);
    Queue<int> q3(q2);
    assert(q3.size() == 2);
    assert(q3.front() == 1);

    // ���� 5: ������������ ������������
    Queue<int> q4;
    q4 = q3;
    assert(q4.front() == 1);
    q4.dequeue();
    assert(q4.front() == 2);

    // ���� 6: �����������
    Queue<int> q5 = move(q4);
    assert(q5.size() == 1);
    assert(q4.isEmpty());

    // ���� 7: ������
    Queue<string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    assert(strQueue.front() == "Hello");
    strQueue.dequeue();
    assert(strQueue.front() == "World");

    cout << "��� ����� �������� �������" << endl;
}
