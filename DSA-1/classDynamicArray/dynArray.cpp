// �����: ���������� �.�.
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
    
    // ���������� ��������� ������� �����������
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

    // �������� ������� � ���������� ���������
    DynamicArray<int> arrClear(5);
    arrClear.push_back(10);
    arrClear.push_back(20);
    arrClear.push_back(30);

    // �������� ���������� ���������
    assert(arrClear.size() == 3);
    assert(arrClear.capacity() >= 3);

    // ����� clear()
    arrClear.clear();

    // �������� ��������� ����� �������
    assert(arrClear.size() == 0);

    // ������� ������� �� ������� ������ ������� ����������
    try {
        int value = arrClear[0];
        assert(false); // �� ������ �����������
    }
    catch (const out_of_range&) {
        // ��������� ���������
    }
    
    // ��������� ����� clear() �� ������ �������� ������
    arrClear.clear();
    assert(arrClear.size() == 0);

    // ��������� ���������� ��������� ����� �������
    arrClear.push_back(42);
    assert(arrClear.size() == 1);
    assert(arrClear[0] == 42);

    cout << "��� ����� �������� �������" << endl;
}