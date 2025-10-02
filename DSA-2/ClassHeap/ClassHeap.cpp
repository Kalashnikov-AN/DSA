#include <iostream>
#include "Heap.h"
#include <cassert>
using namespace std;

int main()
{
    DynamicArray<int> arr;
    arr.push_back(4);
    arr.push_back(10);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(1);
    Heap<int> h1(arr);          // конструктор-копия
    assert(h1.find(4) == 1);
    assert(h1.find(1) == 0);
    cout << "Heap from copy: ";
    h1.print();

    h1.insert(2);
    assert(h1.find(2) == 2);
    cout << "After insert(2): ";
    h1.print();

    cout << "Extract min: ";
    h1.extract_min();
    h1.print();
}

