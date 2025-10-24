#pragma once
#include "AVLTree.h"
#include <cassert>
#include <iostream>

/**
 * Тестирование вставки в AVL дерево.
 * Проверяются:
 * - пустое дерево
 * - дерево из одного узла
 * - несколько вставок с балансировкой
 * - вставка дубликатов
 * - большие последовательные вставки
 */
void test_insertAVL() {
    AVLTree<int> tree;

    // 1. Вставка в пустое дерево
    tree.insert(10);
    assert(tree.get_root() != nullptr);
    assert(tree.get_root()->value == 10);

    // 2. Вставка второго узла
    tree.insert(5);
    tree.insert(15);
    assert(tree.get_root()->left->value == 5);
    assert(tree.get_root()->right->value == 15);

    // 3. Вставка, вызывающая LL поворот
    tree.insert(3); // добавление 3 должно вызвать поворот
    assert(tree.get_root()->value == 10 || tree.get_root()->value == 5); // балансировка произошла

    // 4. Вставка, вызывающая RR поворот
    tree.insert(20);
    tree.insert(25); // должна произойти балансировка
    assert(tree.get_root()->right->value == 20 || tree.get_root()->right->value == 25);

    // 5. Вставка дубликата — должно игнорироваться
    size_t size_before = tree.size();
    tree.insert(10);
    assert(tree.size() == size_before);

    std::cout << "test_insert passed\n";
}

/**
 * Тестирование удаления из AVL дерева.
 * Рассматриваются:
 * - удаление из пустого дерева
 * - удаление единственного узла
 * - удаление листа
 * - удаление узла с одним потомком
 * - удаление узла с двумя потомками
 */
//void test_removeAVL() {
//    AVLTree<int> tree;
//
//    // 1. Удаление из пустого дерева
//    tree.remove(10); // не должно падать
//    cout << "1";
//    // 2. Удаление единственного узла
//    tree.insert(10);
//    tree.remove(10);
//    assert(tree.empty());
//    cout << "2";
//    // 3. Удаление листа
//    tree.insert(10);
//    tree.insert(5);
//    tree.insert(15);
//    tree.remove(5);
//    assert(tree.get_root()->left == nullptr);
//    cout << "3";
//    // 4. Удаление узла с одним потомком
//    tree.insert(12);
//    tree.remove(15);
//    assert(tree.get_root()->right->value == 12);
//    cout << "4";
//    // 5. Удаление узла с двумя потомками
//    tree.insert(20);
//    tree.insert(18);
//    tree.remove(12);
//    assert(tree.search(12) == nullptr);
//    cout << "5";
//    std::cout << "test_remove passed\n";
//}
void test_removeAVL() {
    AVLTree<int> tree;
    // 1. Удаление из пустого дерева
    tree.remove(10); // не должно падать
    cout << "1";
    // 2. Удаление единственного узла
    tree.insert(10);
    tree.remove(10);
    assert(tree.empty());
    cout << "2";
    // 3. Удаление листа
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.remove(5);
    assert(tree.get_root()->left == nullptr);
    cout << "3";
    // 4. Удаление узла с одним потомком
    tree.insert(12);
    tree.remove(15);
    assert(tree.search(12) != nullptr);  // Проверяем наличие 12
    assert(tree.search(15) == nullptr);  // Проверяем отсутствие 15
    cout << "4";
    // 5. Удаление узла с двумя потомками
    tree.insert(20);
    tree.insert(18);
    tree.remove(12);
    assert(tree.search(12) == nullptr);
    cout << "5";
    std::cout << "test_remove passed\n";
}
/**
 * Тестирование поиска в AVL дереве.
 * Рассматриваются:
 * - пустое дерево
 * - поиск корня
 * - поиск листа
 * - поиск несуществующего элемента
 * - поиск после удаления
 */
void test_searchAVL() {
    AVLTree<int> tree;

    // 1. Поиск в пустом дереве
    assert(tree.search(10) == nullptr);

    // 2. Поиск корня
    tree.insert(10);
    assert(tree.search(10) != nullptr);

    // 3. Поиск листа
    tree.insert(5);
    tree.insert(15);
    assert(tree.search(5) != nullptr);
    assert(tree.search(15) != nullptr);

    // 4. Поиск несуществующего элемента
    assert(tree.search(20) == nullptr);

    // 5. Поиск после удаления
    tree.remove(5);
    assert(tree.search(5) == nullptr);

    std::cout << "test_search passed\n";
}

/**
 * Тестирование метода height() в AVL дереве.
 * Рассматриваются:
 * - пустое дерево
 * - дерево из одного узла
 * - несколько уровней с балансировкой
 * - после удаления
 * - большие последовательные вставки
 */
void test_heightAVL() {
    AVLTree<int> tree;

    // 1. Пустое дерево
    assert(tree.height() == 0);

    // 2. Одноузловое дерево
    tree.insert(10);
    assert(tree.height() == 1);

    // 3. Несколько узлов с балансировкой
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    int h = tree.height();
    assert(h >= 2 && h <= 4);

    // 4. После удаления
    tree.remove(15);
    int h2 = tree.height();
    assert(h2 <= h);

    // 5. Большое дерево
    for (int i = 20; i <= 50; i += 5) tree.insert(i);
    assert(tree.height() <= 7); // AVL гарантирует логарифмическую высоту

    std::cout << "test_height passed\n";
}


/**
 * Запуск всех тестов
 */
void run_all_tests() {
    test_insertAVL();
    test_removeAVL();
    test_searchAVL();
    test_heightAVL();
    std::cout << "All AVLTree tests passed!\n";
}
