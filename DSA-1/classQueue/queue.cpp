#include <cassert>
#include <iostream>
#include <string>
#include "queue.h"
using namespace std;
// �����: ���������� �.�.

/// ����� ��� ������ �������
void testQueue() {
    
    // ����������� �� ���������
    Queue<int> q;

    // �������� isEmpty � size
    assert(q.isEmpty());
    assert(q.size() == 0);

    // ���������� ��������
    q.enqueue(10);
    assert(q.front() == 10);
    assert(q.size() == 1);

    // ����� ���������� ��������
    q.enqueue(20);
    assert(q.front() == 10);
    assert(q.size() == 2);

    // �������� �������� 
    q.dequeue();
    assert(q.front() == 20);
    assert(q.size() == 1);

    // ������� �������
    q.clear();
    assert(q.isEmpty());

    // ������� ������ �������
    assert(q.isEmpty());
    q.clear();
    assert(q.isEmpty());

    // �������� ����������
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

    // ����������� �����������
    Queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    Queue<int> q2(q1);
    assert(q2.size() == 2);
    assert(q2.front() == 1);

    // �������� ������������ ������������
    Queue<int> q3;
    q3 = q2;
    assert(q3.front() == 1);

    // ����������� �����������
    Queue<int> q4(move(q2));
    assert(q4.size() == 2); // q2 ���� 2 ��������
    assert(q2.size() == 0); // ����� ����������� �������� ������� ������ ���� �����
    
    // �������� ������������ ������������
    Queue<int> q5 = move(q3);
    assert(q5.size() == 2); // q3 ���� 2 ��������
    assert(q3.isEmpty()); // ����� ����������� �������� ������� ������ ���� �����

    // ���� 7: ������
    Queue<string> strQueue;
    strQueue.enqueue("Hello");
    strQueue.enqueue("World");
    assert(strQueue.front() == "Hello");
    strQueue.dequeue();
    assert(strQueue.front() == "World");

    cout << "��� ����� �������� �������" << endl;
}
