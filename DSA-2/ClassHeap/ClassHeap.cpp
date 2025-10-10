// Автор: Калашников А.Н.
#include <iostream>
#include "Heap.h"
#include <cassert>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    DynamicArray<int> arr;
    arr.push_back(4);
    arr.push_back(10);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(1);
    Heap<int> h1(arr);          
    h1.print_tree();
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

    Heap<int> *h2 = new Heap<int>();
    h2->print_tree();
    try {
        h2->get_min();
    }
    catch (runtime_error x) { cout << x.what(); }

    test_insert();
    test_get_min();
    test_extract_min();
    test_find();
    test_size_and_empty();
    test_constructor_from_array();
    test_print();
    test_print_tree();
    test_heap_sort();
    
}

