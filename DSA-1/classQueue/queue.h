#pragma once
#include "C:\Users\huuma\Documents\DSA\DSA-1\doublyLinkedList\list.h"
#include <stdexcept>
using namespace std;

template <typename T>
class Queue {
private:
    DoublyLinkedList<T> list;

public:
    // ������� ����
    Queue() = default;
    ~Queue() = default;

    // ����������� �����������
    Queue(const Queue& other){
        list = other.list;
    } 

    Queue& operator=(const Queue& other) { // ������������ ������������
        if (this != &other) {
            list = other.list;
        }
        return *this;
    }

    // ����������� �����������
    Queue(Queue&& other) noexcept {
        list = move(other.list);
    } 

    Queue& operator=(Queue&& other) noexcept { // ������������ ������������
        if (this != &other) {
            list = move(other.list);
        }
        return *this;
    }

    // ���������� �������� � ����� ������� (O(1))
    void enqueue(const T& value) {
        list.insert_back(value);
    }

    // �������� �������� �� ������ ������� (O(1))
    T dequeue() {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        T value = front();
        list.remove_front();
        return value;
    }

    // ������ � ������� �������� (O(1))
    T& front() {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        return list.at(0);
    }

    // ����������� ������ � ������� �������� (O(1))
    const T& front() const {
        if (isEmpty()) {
            throw underflow_error("������� �����");
        }
        return list.at(0);
    }

    // �������� �� ������� (O(1))
    bool isEmpty() const {
        return list.size() == 0;
    }

    // ������ ������� (O(1))
    size_t size() const {
        return list.size();
    }

    // ������� ������� (O(n))
    void clear() {
        list.clear();
    }
};

void testQueue();