// Автор: Калашников А.Н.

#include <iostream>
#include "HashTable.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");

    HashTable<int> ht(16);

    ht.insert(10);
    ht.insert(20);
    ht.insert(30);

    cout << "20 найдено? " << (ht.find(20) ? "да" : "нет") << endl;
    ht.remove(20);
    cout << "20 найдено? " << (ht.find(20) ? "да" : "нет") << endl;
    test_insert();
    test_find();
    test_remove();
    test_rehash_behavior();
    test_size_empty_and_custom_hasher();
    cout << "\nAll tests passed successfully.\n";
}