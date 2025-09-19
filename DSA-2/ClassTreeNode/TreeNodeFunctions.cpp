#include "TreeNode.h"
#include "TreeNodeFunctions.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// Тест обходов (preorder, inorder, postorder, bfs, preorder_iterative)
void test_traversals() {
    // Строим дерево:
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7
    TreeNode<int>* root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);

    std::vector<int> res;

    preorder(root, res);
    assert((res == std::vector<int>{4, 2, 1, 3, 6, 5, 7}));

    res.clear();
    inorder(root, res);
    assert((res == std::vector<int>{1, 2, 3, 4, 5, 6, 7}));

    res.clear();
    postorder(root, res);
    assert((res == std::vector<int>{1, 3, 2, 5, 7, 6, 4}));

    res.clear();
    bfs(root, res);
    assert((res == std::vector<int>{4, 2, 6, 1, 3, 5, 7}));

    res.clear();
    preorder_iterative(root, res);
    assert((res == std::vector<int>{4, 2, 1, 3, 6, 5, 7}));

    delete_tree(root);
    std::cout << "Тест обходов в дереве пройден!\n";
}


// Тест подсчёта узлов
void test_count_nodes() {
    TreeNode<int>* root = nullptr;
    assert(count_nodes(root) == 0);

    root = new TreeNode<int>(1);
    assert(count_nodes(root) == 1);

    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    assert(count_nodes(root) == 3);

    delete_tree(root);
    std::cout << "Тест подсчёта узлов дерева пройден!\n";
}

// Тест глубины дерева
void test_depth() {
    TreeNode<int>* root = nullptr;
    assert(depth(root) == 0);

    root = new TreeNode<int>(1);
    assert(depth(root) == 1);

    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(3);
    assert(depth(root) == 3);

    delete_tree(root);
    std::cout << "Тест определения глубины дерева пройден!\n";
}

// Тест печати дерева
void test_print_tree() {
    TreeNode<int>* root = new TreeNode<int>(10);
    root->left = new TreeNode<int>(5);
    root->right = new TreeNode<int>(20);

    std::cout << "Вывод дерева (test_print_tree):\n";
    print_tree(root);

    delete_tree(root);
    std::cout << "Тест печати дерева пройден!\n";
}

// Тест удаления дерева
void test_delete_tree() {
    TreeNode<int>* root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);

    delete_tree(root);
    //cout << "\n" << (root->value) << "\n";
    assert(root == nullptr);
    // После удаления указатель root «висячий», 
    // но памяти не должно утечь (проверить можно инструментами типа valgrind).
    std::cout << "Тест удаления дерева пройден!\n";
}

/**
 * @brief Тестирование функции search_any (поиск в произвольном бинарном дереве).
 *
 * Проверяются сценарии:
 * 1. Пустое дерево
 * 2. Дерево из одного узла
 * 3. Маленькое бинарное дерево
 * 4. Вырожденное дерево (цепочка)
 * 5. Дерево с дубликатами
 */
void test_search_any() {
    std::cout << "=== test_search_any ===\n";

    /// 1. Пустое дерево
    TreeNode<int>* root1 = nullptr;
    assert(search_any(root1, 5) == nullptr);

    /// 2. Дерево из одного узла
    TreeNode<int>* root2 = new TreeNode<int>(42);
    assert(search_any(root2, 42) != nullptr);              // элемент есть
    assert(search_any(root2, 42)->value == 42);
    assert(search_any(root2, 7) == nullptr);               // элемента нет
    delete_tree(root2);

    /// 3. Маленькое дерево:
    ///        10
    ///       /  \
    ///      5   20
    ///     / \
    ///    3   7
    TreeNode<int>* root3 = new TreeNode<int>(10);
    root3->left = new TreeNode<int>(5);
    root3->right = new TreeNode<int>(20);
    root3->left->left = new TreeNode<int>(3);
    root3->left->right = new TreeNode<int>(7);

    assert(search_any(root3, 7) != nullptr);
    assert(search_any(root3, 7)->value == 7);
    assert(search_any(root3, 20) != nullptr);
    assert(search_any(root3, 20)->value == 20);
    assert(search_any(root3, 100) == nullptr); // элемента нет
    delete_tree(root3);

    /// 4. Вырожденное дерево (цепочка вправо):
    /// 1 -> 2 -> 3 -> 4 -> 5
    TreeNode<int>* root4 = new TreeNode<int>(1);
    root4->right = new TreeNode<int>(2);
    root4->right->right = new TreeNode<int>(3);
    root4->right->right->right = new TreeNode<int>(4);
    root4->right->right->right->right = new TreeNode<int>(5);

    assert(search_any(root4, 4) != nullptr);
    assert(search_any(root4, 4)->value == 4);
    assert(search_any(root4, 99) == nullptr);
    delete_tree(root4);

    /// 5. Дерево с дубликатами:
    ///        1
    ///       / \
    ///      2   1
    TreeNode<int>* root5 = new TreeNode<int>(1);
    root5->left = new TreeNode<int>(2);
    root5->right = new TreeNode<int>(1);

    TreeNode<int>* found = search_any(root5, 1);
    assert(found != nullptr);
    assert(found->value == 1); // должен вернуть хотя бы один из 1
    delete_tree(root5);

    std::cout << "Все тесты search_any пройдены!\n\n";
}