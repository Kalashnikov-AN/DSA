#pragma once
#include "AVLTree.h"
#include <cassert>
#include <iostream>

/**
 * ������������ ������� � AVL ������.
 * �����������:
 * - ������ ������
 * - ������ �� ������ ����
 * - ��������� ������� � �������������
 * - ������� ����������
 * - ������� ���������������� �������
 */
void test_insertAVL() {
    AVLTree<int> tree;

    // 1. ������� � ������ ������
    tree.insert(10);
    assert(tree.get_root() != nullptr);
    assert(tree.get_root()->value == 10);

    // 2. ������� ������� ����
    tree.insert(5);
    tree.insert(15);
    assert(tree.get_root()->left->value == 5);
    assert(tree.get_root()->right->value == 15);

    // 3. �������, ���������� LL �������
    tree.insert(3); // ���������� 3 ������ ������� �������
    assert(tree.get_root()->value == 10 || tree.get_root()->value == 5); // ������������ ���������

    // 4. �������, ���������� RR �������
    tree.insert(20);
    tree.insert(25); // ������ ��������� ������������
    assert(tree.get_root()->right->value == 20 || tree.get_root()->right->value == 25);

    // 5. ������� ��������� � ������ ��������������
    size_t size_before = tree.size();
    tree.insert(10);
    assert(tree.size() == size_before);

    std::cout << "test_insert passed\n";
}

/**
 * ������������ �������� �� AVL ������.
 * ���������������:
 * - �������� �� ������� ������
 * - �������� ������������� ����
 * - �������� �����
 * - �������� ���� � ����� ��������
 * - �������� ���� � ����� ���������
 */
//void test_removeAVL() {
//    AVLTree<int> tree;
//
//    // 1. �������� �� ������� ������
//    tree.remove(10); // �� ������ ������
//    cout << "1";
//    // 2. �������� ������������� ����
//    tree.insert(10);
//    tree.remove(10);
//    assert(tree.empty());
//    cout << "2";
//    // 3. �������� �����
//    tree.insert(10);
//    tree.insert(5);
//    tree.insert(15);
//    tree.remove(5);
//    assert(tree.get_root()->left == nullptr);
//    cout << "3";
//    // 4. �������� ���� � ����� ��������
//    tree.insert(12);
//    tree.remove(15);
//    assert(tree.get_root()->right->value == 12);
//    cout << "4";
//    // 5. �������� ���� � ����� ���������
//    tree.insert(20);
//    tree.insert(18);
//    tree.remove(12);
//    assert(tree.search(12) == nullptr);
//    cout << "5";
//    std::cout << "test_remove passed\n";
//}
void test_removeAVL() {
    AVLTree<int> tree;
    // 1. �������� �� ������� ������
    tree.remove(10); // �� ������ ������
    cout << "1";
    // 2. �������� ������������� ����
    tree.insert(10);
    tree.remove(10);
    assert(tree.empty());
    cout << "2";
    // 3. �������� �����
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.remove(5);
    assert(tree.get_root()->left == nullptr);
    cout << "3";
    // 4. �������� ���� � ����� ��������
    tree.insert(12);
    tree.remove(15);
    assert(tree.search(12) != nullptr);  // ��������� ������� 12
    assert(tree.search(15) == nullptr);  // ��������� ���������� 15
    cout << "4";
    // 5. �������� ���� � ����� ���������
    tree.insert(20);
    tree.insert(18);
    tree.remove(12);
    assert(tree.search(12) == nullptr);
    cout << "5";
    std::cout << "test_remove passed\n";
}
/**
 * ������������ ������ � AVL ������.
 * ���������������:
 * - ������ ������
 * - ����� �����
 * - ����� �����
 * - ����� ��������������� ��������
 * - ����� ����� ��������
 */
void test_searchAVL() {
    AVLTree<int> tree;

    // 1. ����� � ������ ������
    assert(tree.search(10) == nullptr);

    // 2. ����� �����
    tree.insert(10);
    assert(tree.search(10) != nullptr);

    // 3. ����� �����
    tree.insert(5);
    tree.insert(15);
    assert(tree.search(5) != nullptr);
    assert(tree.search(15) != nullptr);

    // 4. ����� ��������������� ��������
    assert(tree.search(20) == nullptr);

    // 5. ����� ����� ��������
    tree.remove(5);
    assert(tree.search(5) == nullptr);

    std::cout << "test_search passed\n";
}

/**
 * ������������ ������ height() � AVL ������.
 * ���������������:
 * - ������ ������
 * - ������ �� ������ ����
 * - ��������� ������� � �������������
 * - ����� ��������
 * - ������� ���������������� �������
 */
void test_heightAVL() {
    AVLTree<int> tree;

    // 1. ������ ������
    assert(tree.height() == 0);

    // 2. ����������� ������
    tree.insert(10);
    assert(tree.height() == 1);

    // 3. ��������� ����� � �������������
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    int h = tree.height();
    assert(h >= 2 && h <= 4);

    // 4. ����� ��������
    tree.remove(15);
    int h2 = tree.height();
    assert(h2 <= h);

    // 5. ������� ������
    for (int i = 20; i <= 50; i += 5) tree.insert(i);
    assert(tree.height() <= 7); // AVL ����������� ��������������� ������

    std::cout << "test_height passed\n";
}


/**
 * ������ ���� ������
 */
void run_all_tests() {
    test_insertAVL();
    test_removeAVL();
    test_searchAVL();
    test_heightAVL();
    std::cout << "All AVLTree tests passed!\n";
}
