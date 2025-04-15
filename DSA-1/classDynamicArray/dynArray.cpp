#include <iostream>
#include <cassert>
#include "dynArray.h"
using namespace std;

/// ����� ��� ������� ������ DynamicArray
void runTests() {

    // ���� ������������ � ������� ��������
    DynamicArray<int> arr(5);
    assert(arr.size() == 0);
    assert(arr.capacity() == 5);

    // ���� push_back � ��������� []
    for (int i = 0; i < 10; i++) {
        arr.push_back(i * 10);
    }
    assert(arr.size() == 10);
    // ���� ������ ���������� ���� ������� 5, ����� ������������ ������� ������ ����������� 
    assert(arr.capacity() >= 10);
    for (int i = 0; i < 10; i++) {
        assert(arr[i] == i * 10);
    }

    // ���� ����������� 
    DynamicArray<int> copyArr = arr;  // ����������� �����������
    assert(copyArr.size() == arr.size());
    for (size_t i = 0; i < arr.size(); i++) {
        assert(copyArr[i] == arr[i]);
    }

    // ������� ������������ ������ � ��������, ��� ����� �� ���������� ( �������� ��������� ����������� )
    arr[0] = 999;
    assert(copyArr[0] != arr[0]);

    // ���� ��������� ������������
    DynamicArray<int> assignArr;
    assignArr = arr; // ������������ ������������
    assert(assignArr.size() == arr.size());
    for (size_t i = 0; i < arr.size(); i++) {
        assert(assignArr[i] == arr[i]);
    }

    // ���� pop_back � ��������������� ���������� ���������� ��� ������ ������
    size_t previousCapacity = arr.capacity();
    for (int i = 0; i < 8; i++) {
        arr.pop_back();
    }
    assert(arr.size() == 2);

    // ��������� ����� �������� �������� ���������� ��������� ������ ������ ��� �����������
    assert(arr.capacity() <= previousCapacity);

    // ���� ������� �� ������� c ��������� ����������
    try {
        int temp = arr[100]; // ������ ������� ����������
        assert(false); // ���� ���������� �� ������ �����
    }

    // ��������� ����������
    catch (const out_of_range&) {
       
    }

    cout << "��� ����� �������� �������" << endl;
}