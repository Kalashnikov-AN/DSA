//Автор: Калашников А.Н.
#include "TreeNode.h"
#include "TreeNodeFunctions.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

// Тест Preorder Traversal (NLR)
void test_preorder() {
    vector<int> res;

    // 1. Пустое дерево
    preorder<int>(nullptr, res);
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(10);
    res.clear();
    preorder(root, res);
    assert((res == vector<int>{10}));
    delete_tree(root);

    // 3. Вырожденное дерево (список вправо)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    res.clear();
    preorder(root, res);
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 4. Совершенное дерево
    //       2
    //      / \
    //     1   3
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    preorder(root, res);
    assert((res == vector<int>{2, 1, 3}));
    delete_tree(root);

    

    // 5. Большое дерево с произвольными узлами
    //       4
    //     /   \
    //    10     2
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(10);
    root->right = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    preorder(root, res);
    assert((res == vector<int>{4, 10, 1, 3, 2, 5, 7}));
    delete_tree(root);
    cout << "Тест preorder пройден!\n";
}

// Тест Inorder Traversal (LNR)
void test_inorder() {
    vector<int> res;

    // 1. Пустое дерево
    inorder<int>(nullptr, res);
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(10);
    res.clear();
    inorder(root, res);
    assert((res == vector<int>{10}));
    delete_tree(root);

    // 3. Вырожденное дерево (список влево)
    root = new TreeNode<int>(3);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    res.clear();
    inorder(root, res);
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 4. Совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    inorder(root, res);
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 5. Большое дерево с произвольными узлами
    //       4
    //     /   \
    //    10     2
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(10);
    root->right = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    inorder(root, res);
    assert((res == vector<int>{1, 10, 3, 4, 5, 2, 7}));
    delete_tree(root);

    cout << "Тест inorder пройден!\n";
}

// Тест Postorder Traversal (LRN)
void test_postorder() {
    vector<int> res;

    // 1. Пустое дерево
    postorder<int>(nullptr, res);
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(42);
    res.clear();
    postorder(root, res);
    assert((res == vector<int>{42}));
    delete_tree(root);

    // 3. Вырожденное дерево (список вправо)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    res.clear();
    postorder(root, res);
    assert((res == vector<int>{3, 2, 1}));
    delete_tree(root);

    // 4. Совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    postorder(root, res);
    assert((res == vector<int>{1, 3, 2}));
    delete_tree(root);

    // 5. Большое дерево с произвольными узлами
    //       4
    //     /   \
    //    10     2
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(10);
    root->right = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    postorder(root, res);
    assert((res == vector<int>{1, 3, 10, 5, 7, 2, 4}));
    delete_tree(root);

    cout << "Тест postorder пройден!\n";
}

// Тест BFS Traversal (уровневый обход)
void test_bfs() {
    vector<int> res;

    // 1. Пустое дерево
    bfs<int>(nullptr, res);
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(100);
    res.clear();
    bfs(root, res);
    assert((res == vector<int>{100}));
    delete_tree(root);

    // 3. Вырожденное дерево (список вправо)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    res.clear();
    bfs(root, res);
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 4. Бинарное дерево поиска
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    bfs(root, res);
    assert((res == vector<int>{4, 2, 6, 1, 3, 5, 7}));
    delete_tree(root);

    // 5. Большое дерево с произвольными узлами
    //       4
    //     /   \
    //    10     2
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(10);
    root->right = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    bfs(root, res);
    assert((res == vector<int>{4, 10, 2, 1, 3, 5, 7}));
    delete_tree(root);

    cout << "Тест bfs пройден!\n";
}



// Тест Preorder Traversal (итеративный)
void test_preorder_iterative() {
    vector<int> res;

    // 1. Пустое дерево
    preorder_iterative<int>(nullptr, res);
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(10);
    res.clear();
    preorder_iterative(root, res);
    assert((res == vector<int>{10}));
    delete_tree(root);

    // 3. Вырожденное дерево (список влево)
    root = new TreeNode<int>(3);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    res.clear();
    preorder_iterative(root, res);
    assert((res == vector<int>{3, 2, 1}));
    delete_tree(root);

    // 4. Совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    preorder_iterative(root, res);
    assert((res == vector<int>{2, 1, 3}));
    delete_tree(root);

    // 5. Большое дерево с произвольными узлами
    //       4
    //     /   \
    //    10     2
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(10);
    root->right = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    preorder_iterative(root, res);
    assert((res == vector<int>{4, 10, 1, 3, 2, 5, 7}));
    delete_tree(root);

    cout << "Тест preorder_iterative пройден!\n";
}

// Тест preorder с передачей функции как параметра
void test_preorder_apply() {
    vector<int> res;

    // 1. Пустое дерево
    preorder_apply<int>(nullptr, [&](int& v) { res.push_back(v); });
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(10);
    res.clear();
    preorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{10}));
    delete_tree(root);

    // 3. Вырожденное дерево (вправо)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    res.clear();
    preorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 4. Маленькое совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    preorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{2, 1, 3}));
    delete_tree(root);

    // 5. Дерево среднего размера
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    preorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{4, 2, 1, 3, 6, 5, 7}));
    delete_tree(root);

    cout << "Тест preorder_apply пройден!\n";
}

// Тест inorder с передачей функции как параметра
void test_inorder_apply() {
    vector<int> res;

    // 1. Пустое дерево
    inorder_apply<int>(nullptr, [&](int& v) { res.push_back(v); });
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(10);
    res.clear();
    inorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{10}));
    delete_tree(root);

    // 3. Вырожденное дерево (влево)
    root = new TreeNode<int>(3);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(1);
    res.clear();
    inorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 4. Маленькое совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    inorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 2, 3}));
    delete_tree(root);

    // 5. Дерево среднего размера
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    inorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 2, 3, 4, 5, 6, 7}));
    delete_tree(root);

    cout << "Тест inorder_apply пройден!\n";
}

// Тест postorder с передачей функции как параметра
void test_postorder_apply() {
    vector<int> res;

    // 1. Пустое дерево
    postorder_apply<int>(nullptr, [&](int& v) { res.push_back(v); });
    assert(res.empty());

    // 2. Один узел
    TreeNode<int>* root = new TreeNode<int>(42);
    res.clear();
    postorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{42}));
    delete_tree(root);

    // 3. Вырожденное дерево (вправо)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    res.clear();
    postorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{3, 2, 1}));
    delete_tree(root);

    // 4. Маленькое совершенное дерево
    root = new TreeNode<int>(2);
    root->left = new TreeNode<int>(1);
    root->right = new TreeNode<int>(3);
    res.clear();
    postorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 3, 2}));
    delete_tree(root);

    // 5. Дерево среднего размера
    //       4
    //     /   \
    //    2     6
    //   / \   / \
    //  1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    res.clear();
    postorder_apply<int>(root, [&](int& v) { res.push_back(v); });
    assert((res == vector<int>{1, 3, 2, 5, 7, 6, 4}));
    delete_tree(root);

    cout << "Тест postorder_apply пройден!\n";
}


// Тест подсчёта узлов
void test_count_nodes() {
    // 1) Пустое дерево
    TreeNode<int>* root = nullptr;
    assert(count_nodes(root) == 0);

    // 2) Дерево из одного узла
    root = new TreeNode<int>(1);
    assert(count_nodes(root) == 1);
    delete_tree(root);

    // 3) Дерево из двух узлов (корень + левый ребёнок)
    root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    assert(count_nodes(root) == 2);
    delete_tree(root);

    // 4) Вырожденное дерево (цепочка влево: 1-2-3-4-5)
    root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(3);
    root->left->left->left = new TreeNode<int>(4);
    root->left->left->left->left = new TreeNode<int>(5);
    assert(count_nodes(root) == 5);
    delete_tree(root);

    // 5) Совершенное дерево среднего размера
    //        4
    //      /   \
    //     2     6
    //    / \   / \
    //   1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    assert(count_nodes(root) == 7);
    delete_tree(root);

    cout << "Все тесты подсчёта узлов дерева пройдены!\n";
}


// Тест глубины дерева
void test_depth() {
    // 1) Пустое дерево
    TreeNode<int>* root = nullptr;
    assert(depth(root) == -1);

    // 2) Дерево из одного узла
    root = new TreeNode<int>(1);
    assert(depth(root) == 0);
    delete_tree(root);

    // 3) Вырожденное дерево (цепочка вправо: 1-2-3-4)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    root->right->right->right = new TreeNode<int>(4);
    assert(depth(root) == 3);
    delete_tree(root);

    // 4) Несовершенное дерево
    //       1
    //      / \
    //     2   3
    //    /
    //   4
    root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    assert(depth(root) == 2);
    delete_tree(root);

    // 5) Совершенное дерево
    //        4
    //      /   \
    //     2     6
    //    / \   / \
    //   1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    assert(depth(root) == 2);
    delete_tree(root);

    cout << "Все тесты глубины дерева пройдены!\n";
}


// Тест печати дерева
void test_print_tree() {
    cout << "\nТестирование функции печати дерева:\n";
    // 1) Пустое дерево
    TreeNode<int>* root = nullptr;
    cout << "\nСлучай 1: пустое дерево\n";
    print_tree(root);

    // 2) Дерево из одного узла
    root = new TreeNode<int>(42);
    cout << "Случай 2: один узел\n";
    print_tree(root);
    delete_tree(root);

    // 3) Вырожденное дерево (цепочка влево: 1-2-3-4)
    root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->left->left = new TreeNode<int>(3);
    root->left->left->left = new TreeNode<int>(4);
    cout << "Случай 3: вырожденное дерево (цепочка влево)\n";
    print_tree(root);
    delete_tree(root);

    // 4) Несовершенное дерево
    //       10
    //      /
    //     5
    //      \
    //       7
    root = new TreeNode<int>(10);
    root->left = new TreeNode<int>(5);
    root->left->right = new TreeNode<int>(7);
    cout << "Случай 4: неcовершенное дерево\n";
    print_tree(root);
    delete_tree(root);

    // 5) Совершенное дерево среднего размера
    //        4
    //      /   \
    //     2     6
    //    / \   / \
    //   1   3 5   7
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    cout << "Случай 5: Совершенное дерево\n";
    print_tree(root);
    delete_tree(root);

    cout << "\nВсе тесты печати дерева пройдены!\n";
}


// Тест удаления дерева
void test_delete_tree() {

    // 1) Пустое дерево
    TreeNode<int>* root = nullptr;
    delete_tree(root);
    assert(root == nullptr);

    // 2) Дерево из одного узла
    root = new TreeNode<int>(1);
    delete_tree(root);
    assert(root == nullptr);

    // 3) Вырожденное дерево (цепочка вправо: 1-2-3-4)
    root = new TreeNode<int>(1);
    root->right = new TreeNode<int>(2);
    root->right->right = new TreeNode<int>(3);
    root->right->right->right = new TreeNode<int>(4);
    delete_tree(root);
    assert(root == nullptr);

    // 4) Малое неcовершенное дерево
    root = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left = new TreeNode<int>(1);
    delete_tree(root);
    assert(root == nullptr);

    // 5) Совершенное дерево среднего размера
    root = new TreeNode<int>(4);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(6);
    root->left->left = new TreeNode<int>(1);
    root->left->right = new TreeNode<int>(3);
    root->right->left = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(7);
    delete_tree(root);
    assert(root == nullptr);

    cout << "Все тесты удаления дерева пройдены!\n";
}


/**
 *  Тестирование функции search_any (поиск в произвольном бинарном дереве).
 */
void test_search_any() {
    
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

    cout << "Все тесты search_any пройдены!\n\n";
}