// �����: ���������� �.�.
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

/// ���������� ������� ������� arr ������� n, �������� ������� � ��������� ����� x.
/// ���� � ������� ��������� ��������� � ���������� ����������� ��������, ������������ ������ ���������.
int findClosestElement(const int* arr, size_t n, int x) {
    // �������������� ��������� ������� ������ ��������� �������.
    int closest = arr[0];
    int minDiff = abs(arr[0] - x);

    // ���� ������ ������� ����� ����� x, ����� ����� ������� ��� (������ ������: O(1)).
    if (minDiff == 0) {
        return closest;
    }

    // ���������� ���������� �������� �������.
    // � ������ ������ (����� ��������� ������� ��������� � �����) ����������� ��������� (n - 1) ���������,
    // �� ���� ��������� ��������� ��������� O(n) ��� ������������� ������ �����.
    for (size_t i = 1; i < n; i++) {
        int diff = abs(arr[i] - x);
        if (diff < minDiff) {
            minDiff = diff;
            closest = arr[i];
        }
    }
    return closest;
}

/// ������� ��� ������������ ������� findClosestElement.
void testFindClosestElement() {
    {
        // ������ ����������: x ��������� � ��������� �������.
        int arr[] = { 1, 3, 5, 7, 9 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        int x = 5;
        assert(findClosestElement(arr, n, x) == 5);
    }
    {
        // ��������� ������� ��������� � �������� �������.
        int arr[] = { 1, 4, 6, 8, 10 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        int x = 7;
        // ������� ��� 6 � 8 ����� 1, �� ������� ������ ������ ���������, �.�. 6.
        assert(findClosestElement(arr, n, x) == 6);
    }
    {
        // ��������� ������� � ������ ������� �������.
        int arr[] = { 5, 10, 15, 20 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        int x = 2;
        assert(findClosestElement(arr, n, x) == 5);
    }
    {
        // ��������� ������� � ��������� ������� �������.
        int arr[] = { 3, 6, 9, 12, 15 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        int x = 16;
        assert(findClosestElement(arr, n, x) == 15);
    }
    {
        // ������ � �������������� ����������.
        int arr[] = { 10, 20, 20, 30, 40 };
        size_t n = sizeof(arr) / sizeof(arr[0]);
        int x = 22;
        // ������� ��� 20 ����� 2, ��� 30 ����� 8, ������� ������������ 20.
        assert(findClosestElement(arr, n, x) == 20);
    }
    cout << "��� ����� ��� findClosestElement �������� �������" << endl;
}