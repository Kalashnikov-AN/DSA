#include <cassert>
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

/**
 * @brief ������������ ������ insert()
 */
void test_insert() {
    BinarySearchTree<int> bst;
    assert(bst.empty());

    bst.insert(10);
    assert(!bst.empty());
    assert(bst.get_root()->value == 10);

    bst.insert(5);
    bst.insert(15);
    assert(bst.get_root()->left->value == 5);
    assert(bst.get_root()->right->value == 15);

    // ��������, ��� ��������� �� �����������
    bst.insert(10);
    assert(bst.size() == 3);

    cout << "test_insert passed\n";
}

/**
 * @brief ������������ ������ size()
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
 * @brief ������������ ������ height()
 */
void test_height() {
    BinarySearchTree<int> bst;
    assert(bst.height() == 0);

    bst.insert(10);
    assert(bst.height() == 1);

    // ������ ����������� ������ (������� ������)
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    assert(bst.height() == 4);

    cout << "test_height passed\n";
}

/**
 * @brief ������������ ������ remove()
 */
void test_remove() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(12);
    bst.insert(18);

    // �������� �����
    bst.remove(12);
    assert(bst.size() == 4);

    // �������� ���� � ����� ��������
    bst.remove(18);
    assert(bst.size() == 3);

    // �������� ���� � ����� ���������
    bst.remove(10);
    assert(bst.size() == 2);

    // �������� ��������������� ��������
    bst.remove(100);
    assert(bst.size() == 2);

    cout << "test_remove passed\n";
}

/**
 * @brief ������������ ������ clear() � empty()
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

/**
 * @brief ������������ ������ successor()
 */
void test_successor() {
    BinarySearchTree<int> bst;
    bst.insert(20);
    bst.insert(10);
    bst.insert(30);
    bst.insert(25);
    bst.insert(40);

    // successor(20) = 25
    TreeNode<int>* succ = bst.successor(20);
    assert(succ && succ->value == 25);

    // successor(25) = 30
    succ = bst.successor(25);
    assert(succ && succ->value == 30);

    // successor ������������� �������� = nullptr
    succ = bst.successor(40);
    assert(succ == nullptr);

    cout << "test_successor passed\n";
}

/**
 * @brief ������������ ������ search()
 */
void test_search() {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    TreeNode<int>* found = bst.search(5);
    assert(found && found->value == 5);

    found = bst.search(100);
    assert(found == nullptr);

    cout << "test_search passed\n";
}

