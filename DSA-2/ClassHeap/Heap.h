// �����: ���������� �.�.
#pragma once
#include <stdexcept>
#include <iostream>
#include "..\..\DSA-1\classDynamicArray\dynArray.h"


using namespace std;

/**
 * ��������� ����� ��� ���������� ����������� ���� (min-heap).
 * �������� �������������� � ������� DynamicArray<T>.
 * �������� � ������ ���� <= �������� ��� ��������.
 */
template <typename T>
class Heap {
private:
    DynamicArray<T> data;  /// ������������ ������ ��� �������� ��������� ����

    /**
     *  ����������� ����� (�������������� �������� ���� ��� �������).
     *  O(log n)
     */
    void bubble_up(size_t index) {
        while (index > 0) { // ���� �� ����� �� �����
            size_t parent = (index - 1) / 2; // �������� ������� ��� ���������� ������� �������
            if (data[index] < data[parent]) {  // ���� ����������� ���� ������ �� ��������, ��� ��� ������
                swap(data[index], data[parent]); // ������ �� �������
                index = parent; // �������������� ������ ������������ ����
            }
            else {
                break;
            }
        }
    }

    /**
     *  ����������� ���� (�������������� �������� ���� ��� ��������).
     *  O(log n)
     */
    void trickle_down(size_t index) {
        size_t n = data.size();
        while (true) {
            size_t left = 2 * index + 1; // ����� ������� �������� ����
            size_t right = 2 * index + 2; // ������ ������� �������� ����
            size_t smallest = index; // ������� ����, ������ ���� ���������� �� ��������

            if (left < n && data[left] < data[smallest]) // ����� ������� ���������� � ��� �������� ������ �������� ����
                smallest = left;
            if (right < n && data[right] < data[smallest]) // ������ ������� ���������� � ��� �������� ������ �������� ����
                smallest = right;

            if (smallest != index) { // ����� ���� � ������� ���������
                swap(data[index], data[smallest]); // ������ �������
                index = smallest; // ����� ������� ����
            }
            else { // ���� �� ����� ���� � ������� ���������, ������ �� ����� ����� ������ ����
                break; // ������� �� �����
            }
        }
    }

public:
    /// ����������� �� ���������
    Heap(size_t initial_capacity = 16) : data(initial_capacity) {}

   /**
        * ����������� � �����������
        * @param arr � ������ DynamicArray<T>
        *  O(n)
        */
        Heap(const DynamicArray<T>&arr) : data(arr) {
        // ���������� ���� �� O(n)
        for (int i = (data.size()) / 2 - 1; i >= 0; --i) {
            trickle_down(i);
        }
    }

    /// ��������, ����� �� ����
    bool empty() const {
        return data.size() == 0;
    }

    /// ���������� ���������
    size_t size() const {
        return data.size();
    }

    /**
     *  ������� �������� � ����
     *  O(log n)
     */
    void insert(const T& value) {
        data.push_back(value);
        bubble_up(data.size() - 1);
    }

    /**
     *  ���������� ����������� ������� (������ ����)
     *  O(1)
     */
    const T& get_min() const {
        if (empty()) throw runtime_error("���� �����!");
        return data[0];
    }

    /**
     *  �������� ������������ �������� (����� ����)
     *  O(log n)
     */
    void extract_min() {
        if (empty()) {
            cout << "���� �����!";
            return;
        }
        if (data.size() == 1) { // ���� ���� ������� �� ������ �����
            data.pop_back(); // ������� ������
            return; // ��������� ������ ������
        }
        data[0] = data[data.size() - 1]; // ������ �� ����� ����� �������� ������ ������� �����
        data.pop_back(); // ������� ��� ����
        trickle_down(0); // ������ ������ �� ������� � ����������� ��������� 
    }

    /**
 *  ����� �������� � ����
 * @param value �������� ��� ������
 * @return ������ ���������� �������� ��� -1, ���� ������� �� ������
 *  O(n)
 */
    int find(const T& value) const {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == value) {
                return i; // ����� � ���������� ������
            }
        }
        return -1; // �� �����
    }

    /**
  *  �������� ���� � ���� ������ �� �������, � ���������
  * �������� ��������� �� ������
  *  O(n)
  */
    void print_tree() const {
        size_t n = data.size();
        if (empty()) {
            cout << "���� �����!\n";
            return;
        }

        // ��������� ���������� ������� � ������
        size_t levels = 0;
        for (size_t cnt = n; cnt > 0; cnt /= 2) levels++;

        size_t max_width = static_cast<size_t>(pow(2, levels)); // ������ ������ (��������)

        size_t index = 0;
        for (size_t level = 0; level < levels; ++level) {
            size_t nodes_on_level = static_cast<size_t>(pow(2, level));  // ������� ����� �� ���� ������
            size_t space_between = max_width / nodes_on_level; // ���������� ����� ������

            // ������ ����� ������ ��������� �� ������
            cout << string(space_between / 2, ' '); // ������ ����� �������� �� space_between / 2 ��������

            for (size_t i = 0; i < nodes_on_level && index < n; ++i, ++index) {
                cout << data[index];
                // ������� ����� ��������
                if (i != nodes_on_level - 1) {
                    cout << string(space_between - 1, ' ');
                }
            }
            cout << "\n\n"; 
        }
    }

    /**
     *  ������ �������� ����, ���������� � ������������ �������
     *  O(n)
     */
    void print() const {
        for (size_t i = 0; i < data.size(); i++)
            cout << data[i] << " ";
        cout << "\n";
    }


};

/**
 * ������� ���������� ����� (heap sort)
 * 1. ������ min-heap �� �������.
 * 2. ��������� ����������� ������� �� ������, ������� ��� � ����� �������.
 * 3. ����� ���������� ������ ����� ������������ �� �����������.
 * O(n log n)
 */
template <typename T>
void heapSort(DynamicArray<T>& arr) {
    size_t n = arr.size();
    if (n <= 1) return; // ��� �������������

    // ���������� min-heap 
    Heap<T> heap(arr);
    heap.print_tree();
    // ��������� �������� �� ������ 
    for (size_t i = 0; i < n; ++i) {
        arr[i] = heap.get_min(); // ����������� ������� �� ������� ��������
        heap.extract_min();      // ������� ��� �� ����
    }
}

void test_heap_sort();
void test_insert();
void test_get_min();
void test_extract_min();
void test_find();
void test_size_and_empty();
void test_constructor_from_array();
void test_print();
void test_print_tree();