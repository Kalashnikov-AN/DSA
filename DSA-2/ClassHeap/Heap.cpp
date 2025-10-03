// Автор: Калашников А.Н.
#include <cassert>
#include "Heap.h"   
#include "C:\Users\huuma\Documents\DSA\DSA-1\classDynamicArray\dynArray.h"

using namespace std;

/**
 *  Тест метода insert()
 */
void test_insert() {
    Heap<int> h;

    // 1. Вставка в пустую кучу
    h.insert(10);
    assert(h.get_min() == 10);

    // 2. Вставка меньшего элемента -> он становится корнем
    h.insert(5);
    assert(h.get_min() == 5);

    // 3. Вставка большего элемента -> корень не меняется
    h.insert(20);
    assert(h.get_min() == 5);

    // 4. Несколько вставок в разнобой
    h.insert(3);
    h.insert(8);
    assert(h.get_min() == 3);

    // 5. Проверка размера
    assert(h.size() == 5);
}

/**
 *  Тест метода get_min()
 */
void test_get_min() {
    Heap<int> h;

    // 1. Пустая куча -> исключение
    bool caught = false;
    try { h.get_min(); }
    catch (const runtime_error&)
    { caught = true; }
    assert(caught);

    // 2. Куча из одного узла
    h.insert(42);
    assert(h.get_min() == 42);

    // 3. Несколько элементов
    h.insert(10);
    h.insert(5);
    assert(h.get_min() == 5);

    // 4. Добавление ещё меньшего
    h.insert(1);
    assert(h.get_min() == 1);

    // 5. Корректность при большом числе элементов
    for (int i = 100; i < 200; i++) h.insert(i);
    assert(h.get_min() == 1);
}

/**
 *  Тест метода extract_min()
 */
void test_extract_min() {
    Heap<int> h;

    // 1. Пустая куча (должен просто вывести сообщение и не упасть)
    h.extract_min();
    assert(h.empty());

    // 2. Куча из одного узла
    h.insert(10);
    h.extract_min();
    assert(h.empty());

    // 3. Несколько элементов
    h.insert(10);
    h.insert(5);
    h.insert(20);
    h.extract_min();
    assert(h.get_min() == 10);

    // 4. Извлекаем все элементы по очереди
    h.extract_min(); // удалим 10
    h.extract_min(); // удалим 20
    assert(h.empty());

    // 5. Проверка порядка удаления на куче {7, 3, 9, 1}
    h.insert(7);
    h.insert(3);
    h.insert(9);
    h.insert(1);
    h.extract_min(); // удаляем 1
    assert(h.get_min() == 3);
}

/**
 *  Тест метода find()
 */
void test_find() {
    Heap<int> h;

    // 1. Поиск в пустой куче
    assert(h.find(10) == -1);

    // 2. Куча из одного узла (элемент есть)
    h.insert(42);
    assert(h.find(42) != -1);

    // 3. Куча из одного узла (элемента нет)
    assert(h.find(100) == -1);

    // 4. Несколько элементов, поиск существующего
    h.insert(5);
    h.insert(10);
    h.insert(3);
    int idx = h.find(10);
    assert(idx >= 0);

    // 5. Несколько элементов, поиск отсутствующего
    assert(h.find(99) == -1);
}

/**
 *  Тест метода empty() и size()
 */
void test_size_and_empty() {
    Heap<int> h;

    // 1. Новая куча пуста
    assert(h.empty());
    assert(h.size() == 0);

    // 2. Куча из одного элемента
    h.insert(5);
    assert(!h.empty());
    assert(h.size() == 1);

    // 3. Несколько элементов
    h.insert(10);
    h.insert(1);
    assert(h.size() == 3);

    // 4. Удаляем один элемент
    h.extract_min();
    assert(h.size() == 2);

    // 5. Удаляем все
    h.extract_min();
    h.extract_min();
    assert(h.empty());
    assert(h.size() == 0);
}

/**
 *  Тест конструктора Heap(const DynamicArray<T>&)
 */
void test_constructor_from_array() {
    DynamicArray<int> arr(10);
    arr.push_back(10);
    arr.push_back(5);
    arr.push_back(30);
    arr.push_back(2);
    arr.push_back(8);

    Heap<int> h(arr);

    // 1. Куча должна быть не пустой
    assert(!h.empty());

    // 2. Размер совпадает
    assert(h.size() == 5);

    // 3. Минимальный элемент — 2
    assert(h.get_min() == 2);

    // 4. Извлекаем минимальный (2), новый минимум = 5
    h.extract_min();
    assert(h.get_min() == 5);

    // 5. Удаляем все -> куча должна быть пустой
    while (!h.empty()) h.extract_min();
    assert(h.empty());
}

/**
 *  Тест метода print()
 * Просто выводим разные кучи на экран (визуальная проверка).
 */
void test_print() {
    cout << "\n=== Тест print() ===\n";

    // 1. Пустая куча
    Heap<int> h1;
    h1.print();

    // 2. Куча из одного элемента
    h1.insert(42);
    h1.print();

    // 3. Несколько элементов
    h1.insert(10);
    h1.insert(5);
    h1.print();

    // 4. После удаления
    h1.extract_min();
    h1.print();

    // 5. Большая куча
    for (int i = 0; i < 10; i++) h1.insert(i);
    h1.print();
}

/**
 *  Тест метода print_tree()
 * Просто выводим дерево на экран (визуальная проверка).
 */
void test_print_tree() {
    cout << "\n=== Тест print_tree() ===\n";

    // 1. Пустая куча
    Heap<int> h1;
    h1.print_tree();

    // 2. Один элемент
    h1.insert(42);
    h1.print_tree();

    // 3. Несколько элементов
    h1.insert(10);
    h1.insert(5);
    h1.print_tree();

    // 4. После удаления
    h1.extract_min();
    h1.print_tree();

    // 5. Большая куча
    for (int i = 0; i < 7; i++) h1.insert(i);
    h1.print_tree();
}


