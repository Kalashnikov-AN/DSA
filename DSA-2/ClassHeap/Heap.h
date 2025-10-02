// �����: ���������� �.�.
// ���������� ���������� ������ Heap (����������� ����)
// ���������� ��������: DynamicArray<T>

#pragma once
#include <stdexcept>
#include <iostream>
#include "C:\Users\huuma\Documents\DSA\DSA-1\classDynamicArray\dynArray.h"

using namespace std;

/**
 * @class Heap
 * @brief ��������� ����� ��� ���������� ����������� ���� (min-heap).
 *
 * �������� �������������� � ������� DynamicArray<T>.
 * �������� min-heap: �������� � ������ ���� <= �������� ��� ��������.
 */
template <typename T>
class Heap {
private:
    DynamicArray<T> data;  ///< ������ ��� �������� ��������� ����

    /**
     * @brief ����������� ����� (�������������� �������� ���� ��� �������).
     * @complexity O(log n)
     */
    void bubble_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2; // �������� ������� ��� ���������� ������� �������
            if (data[index] < data[parent]) { 
                swap(data[index], data[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    /**
     * @brief ����������� ���� (�������������� �������� ���� ��� ��������).
     * @complexity O(log n)
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
    /// �����������
    Heap(size_t initial_capacity = 16) : data(initial_capacity) {}

   /**
        *@brief ����������� �� DynamicArray<T>(�����).
        * @param arr � ������ DynamicArray<T>
        *
        * @complexity O(n)
        */
        Heap(const DynamicArray<T>&arr) : data(arr) {
        // ���������� ���� �� O(n)
        for (int i = static_cast<int>(data.size()) / 2 - 1; i >= 0; --i) {
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
     * @brief ������� �������� � ����
     * @complexity O(log n)
     */
    void insert(const T& value) {
        data.push_back(value);
        bubble_up(data.size() - 1);
    }

    /**
     * @brief ���������� ����������� ������� (������ ����)
     * @complexity O(1)
     */
    const T& get_min() const {
        if (empty()) throw runtime_error("Heap is empty");
        return data[0];
    }

    /**
     * @brief �������� ������������ �������� (����� ����)
     * @complexity O(log n)
     */
    void extract_min() {
        if (empty()) throw runtime_error("Heap is empty");
        if (data.size() == 1) {
            data.pop_back();
            return;
        }
        data[0] = data[data.size() - 1];
        data.pop_back();
        trickle_down(0);
    }

    /**
 * @brief ����� �������� � ����
 * @param value �������� ��� ������
 * @return ������ ���������� �������� ��� -1, ���� ������� �� ������
 * @complexity O(n)
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
     * @brief ������ ���� (��� �������)
     * @complexity O(n)
     */
    void print() const {
        for (size_t i = 0; i < data.size(); i++)
            cout << data[i] << " ";
        cout << "\n";
    }
};
