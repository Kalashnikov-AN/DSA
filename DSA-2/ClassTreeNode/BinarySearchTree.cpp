//Автор: Калашников А.Н.
#include <cassert>
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

/**
 *  Тестирование метода insert()
 */
void test_insert() {
    // 1) Пустое дерево -> вставка
    BinarySearchTree<int> bst;
    assert(bst.empty());
    bst.insert(10);
    assert(!bst.empty());
    assert(bst.get_root()->value == 10);

    // 2) Вставка меньшего и большего значения
    bst.insert(5);
    bst.insert(15);
    assert(bst.get_root()->left->value == 5);
    assert(bst.get_root()->right->value == 15);

    // 3) Попытка вставки дубликата
    bst.insert(10);
    assert(bst.size() == 3);

    // 4) Вырожденное дерево (вставляем по убыванию)
    BinarySearchTree<int> bst2;
    bst2.insert(10);
    bst2.insert(9);
    bst2.insert(8);
    bst2.insert(7);
    assert(bst2.height() == 4); // цепочка вниз

    // 5) Более сложное дерево
    BinarySearchTree<int> bst3;
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        bst3.insert(v);
    assert(bst3.size() == 7);
    assert(bst3.get_root()->left->right->value == 40);

    cout << "test_insert passed\n";
}

/**
 *  Тестирование метода remove()
 */
void test_remove() {
    // 1) Удаление из пустого дерева
    BinarySearchTree<int> bst;
    bst.remove(10); // ничего не должно произойти
    assert(bst.size() == 0);

    // 2) Удаление из дерева из одного узла
    bst.insert(5);
    bst.remove(5);
    assert(bst.empty());

    // 3) Удаление листа
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.remove(5);
    assert(bst.size() == 2);

    // 4) Удаление узла с одним потомком
    bst.insert(12);
    bst.remove(15);
    assert(bst.size() == 2);

    // 5) Удаление узла с двумя потомками
    bst.insert(20);
    bst.insert(25);
    bst.remove(10); // корень с двумя детьми
    assert(bst.size() == 3);

    cout << "test_remove passed\n";
}

/**
 *  Тестирование метода successor()
 */
void test_successor() {
    BinarySearchTree<int> bst;

    // 1) Пустое дерево
    assert(bst.successor(10) == nullptr);

    // 2) Одно узловое дерево
    bst.insert(5);
    assert(bst.successor(5) == nullptr);

    // 3) Линейное дерево вправо
    bst.insert(10);
    bst.insert(15);
    assert(bst.successor(10)->value == 15);

    // 4) Сбалансированное дерево
    bst.insert(20);
    bst.insert(25);
    bst.insert(30);
    TreeNode<int>* succ = bst.successor(20);
    assert(succ && succ->value == 25);

    // 5) Successor максимального элемента = nullptr
    succ = bst.successor(30);
    assert(succ == nullptr);

    cout << "test_successor passed\n";
}

/**
 *  Тестирование метода search()
 */
void test_search() {
    BinarySearchTree<int> bst;

    // 1) Пустое дерево
    assert(bst.search(10) == nullptr);

    // 2) Один узел
    bst.insert(5);
    TreeNode<int>* found = bst.search(5);
    assert(found && found->value == 5);

    // 3) Вырожденное дерево
    bst.insert(4);
    bst.insert(3);
    bst.insert(2);
    found = bst.search(2);
    assert(found && found->value == 2);

    // 4) Несуществующее значение
    found = bst.search(100);
    assert(found == nullptr);

    // 5) Сбалансированное дерево
    BinarySearchTree<int> bst2;
    for (int v : {10, 5, 15, 3, 7, 12, 18})
        bst2.insert(v);
    found = bst2.search(7);
    assert(found && found->value == 7);

    cout << "test_search passed\n";
}


/**
 *  Тестирование метода size()
 */
void test_size() {
    BinarySearchTree<int> bst;
    assert(bst.size() == 0);

    bst.insert(1);
    assert(bst.size() == 1);

    bst.insert(2);
    bst.insert(3);
    assert(bst.size() == 3);

    cout << "test_size passed\n";
}

/**
 *  Тестирование метода height()
 */
void test_height() {
    BinarySearchTree<int> bst;
    assert(bst.height() == 0);

    bst.insert(10);
    assert(bst.height() == 1);

    // создаём вырожденное дерево (цепочка вправо)
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    assert(bst.height() == 4);

    cout << "test_height passed\n";
}

/**
 *  Тестирование метода clear() и empty()
 */
void test_clear_empty() {
    BinarySearchTree<int> bst;
    assert(bst.empty());

    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    assert(!bst.empty());

    bst.clear();
    assert(bst.empty());
    assert(bst.size() == 0);

    cout << "test_clear_empty passed\n";
}


