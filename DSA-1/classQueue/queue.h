#pragma once
#include "C:\Users\huuma\Documents\DSA\DSA-1\doublyLinkedList\list.h"
#include <stdexcept>
using namespace std;
// �����: ���������� �.�.

/// ��������� ����� �������
template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list; // ���������� ���������� ������ ��� �������� ���������

public:

    /// ����������� �� ���������
    Queue() = default;

    /// ���������� �� ��������� 
    ~Queue() = default;

    /// ����������� �����������, other - ���������� ������
    Queue(const Queue& other) = default;

    /// �������� ������������ ������������, other - ���������� ������, ���������� ������ �� ������� �������� ������
    Queue& operator=(const Queue& other) = default;

    /// ����������� �����������, other - rvalue ������ �� ������������ ������
    Queue(Queue&& other) noexcept = default;

    /// �������� ������������ ������������, other - rvalue ������ �� ������������ ������, ���������� ������ �� ������� �������� ������
    Queue& operator=(Queue&& other) noexcept = default;

    /// ���������� �������� value � ����� ������� 
    void enqueue(const T value) {
        list.insert_back(value);
    }

    /// ������� ������� �� ������ ������� � ���������� ���
    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        T value = front();
        list.remove_front();
        return value;
    }

    /// ���������� ������ ������� �� ������� 
    T front() {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        return list.at(0);
    }

    /// ����������� ������ � ������� �������� 
    const T front() const {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        return list.at(0);
    }

    /// �������� ������� �� �������, ���������� true/false
    bool isEmpty() const {
        return list.size() == 0;
    }

    /// ���������� ������ ������� 
    size_t size() const {
        return list.size();
    }

    /// ������� �������
    void clear() {
        list.clear();
    }
};

/// ����� ��� ������ �������
void testQueue();