//Автор: Калашников А.Н.
#pragma once
#include "TreeNode.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

/**
 * Прямой обход (NLR: Node, Left, Right)
 * O(n), где n — количество узлов
 * Результат сохраняется в вектор.
 * @param T тип данных в узлах дерева
 * @param node корень поддерева
 * @param result вектор для сохранения порядка обхода
 */
template<typename T>
void preorder(TreeNode<T>* node, vector<T>& result) {
    if (!node) return;
    result.push_back(node->value);       // 1. обрабатываем текущий узел
    preorder(node->left, result);        // 2. рекурсивно левое поддерево
    preorder(node->right, result);       // 3. рекурсивно правое поддерево
}

/**
 *  Прямой обход (печать значений узлов).
 *  O(n)
 */
template<typename T>
void preorder_print(TreeNode<T>* node) {
    if (!node) return;
    cout << node->value << " ";     // сначала выводим текущий узел
    preorder_print(node->left);          // затем левое поддерево
    preorder_print(node->right);         // затем правое поддерево
}

/**
 *  Прямой обход с применением функции к каждому узлу.
 *  O(n)
 * @param func функция (лямбда или function), применяемая к значению
 */
template<typename T>
void preorder_apply(TreeNode<T>* node, function<void(T&)> func) {
    if (!node) return;
    func(node->value);                   // применяем функцию к текущему узлу
    preorder_apply(node->left, func);    // левое поддерево
    preorder_apply(node->right, func);   // правое поддерево
}

/**
 *  Симметричный обход (LNR), результат в вектор.
 *  O(n)
 */
template<typename T>
void inorder(TreeNode<T>* node, vector<T>& result) {
    if (!node) return;
    inorder(node->left, result);         // сначала левое поддерево
    result.push_back(node->value);       // потом текущий узел
    inorder(node->right, result);        // потом правое поддерево
}

/**
 *  Симметричный обход с печатью.
 *  O(n)
 */
template<typename T>
void inorder_print(TreeNode<T>* node) {
    if (!node) return;
    inorder_print(node->left);
    cout << node->value << " ";
    inorder_print(node->right);
}

/**
 *  Симметричный обход с применением функции к каждому узлу.
 *  O(n)
 */
template<typename T>
void inorder_apply(TreeNode<T>* node, function<void(T&)> func) {
    if (!node) return;
    inorder_apply(node->left, func);
    func(node->value);
    inorder_apply(node->right, func);
}

/**
 *  Обратный обход (LRN), результат в вектор.
 *  O(n)
 */
template<typename T>
void postorder(TreeNode<T>* node, vector<T>& result) {
    if (!node) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->value);       // последний шаг — текущий узел
}

/**
 *  Обратный обход с печатью.
 *  O(n)
 */
template<typename T>
void postorder_print(TreeNode<T>* node) {
    if (!node) return;
    postorder_print(node->left);
    postorder_print(node->right);
    cout << node->value << " ";
}

/**
 *  Обратный обход с применением функции к каждому узлу.
 *  O(n)
 */
template<typename T>
void postorder_apply(TreeNode<T>* node, function<void(T&)> func) {
    if (!node) return;
    postorder_apply(node->left, func);
    postorder_apply(node->right, func);
    func(node->value);
}

/**
 *  Обход в ширину (BFS, уровень за уровнем).
 * Использует очередь.
 *  O(n)
 */
template<typename T>
void bfs(TreeNode<T>* root, vector<T>& result) {
    if (!root) return; // если дерева не существует - ничего не возвращаем
    queue<TreeNode<T>*> q;
    q.push(root); // добавляем в очередь корень
    while (!q.empty()) { // если очередь не пуста
        TreeNode<T>* node = q.front(); q.pop(); // запоминаем начальный элемент очереди, затем удаляем
        result.push_back(node->value); // заносим значение начального элемента в вектор
        if (node->left) q.push(node->left); // если у узла есть потомок слева - заносим его в очередь
        if (node->right) q.push(node->right); // если у узла есть потомок справа - заносим его в очередь
        // левый обработается раньше, т.к. используем очередь
    }
}

/**
 *  Нерекурсивный прямой обход (DFS), с использованием стека.
 *  O(n)
 */
template<typename T>
void preorder_iterative(TreeNode<T>* root, vector<T>& result) {
    if (!root) return; // если дерева не существует - ничего не возвращаем
    stack<TreeNode<T>*> st; 
    st.push(root); // если дерево существует - сначала добавляем в стэк корень
    while (!st.empty()) { // пока стэк не пуст
        TreeNode<T>* node = st.top(); st.pop(); // запоминаем верхний элемент стэка, затем удаляем
        result.push_back(node->value); // заносим значение верхнего элемента в вектор 
        if (node->right) st.push(node->right); // если у узла есть потомок справа - заносим его в стэк
        if (node->left) st.push(node->left); // если у узла есть потомок слева - заносим его в стэк 
        // левый обработается раньше, т.к. используем стэк
    }
}


/**
 *  Поиск значения в произвольном бинарном дереве (не обязательно BST).
 * Использует обход в глубину (DFS).
 * @param T тип данных
 * @param root корень дерева
 * @param key искомое значение
 * @return указатель на найденный узел или nullptr
 *  O(n), где n — количество узлов
 */
template<typename T>
TreeNode<T>* search_any(TreeNode<T>* root, const T& key) {
    if (!root) return nullptr;

    if (root->value == key) return root; // нашли

    // ищем в левом поддереве
    TreeNode<T>* leftResult = search_any(root->left, key);
    if (leftResult) return leftResult;

    // если не нашли слева - ищем справа
    return search_any(root->right, key);
}


/**
 *  Удаление всего дерева (освобождение памяти).
 * Использует модифицированный обход Морриса.
 * root передаётся по ссылке, после вызова обнуляется.
 * O(n)
 */
template<typename T>
void delete_tree(TreeNode<T>*& root) {
    while (root) {
        if (root->left) {
            TreeNode<T>* tmp = root->left;    // временно сохраняем левого потомка
            root->left = tmp->right;          // переносим его правую ветку
            tmp->right = root;                // создаём цикл
            root = tmp;                       // спускаемся вниз
        }
        else {
            TreeNode<T>* tmp = root;
            root = root->right;               // переходим вправо
            delete tmp;                       // удаляем текущий узел
        }
    }
    root = nullptr; 
}

/**
 *  Подсчёт количества узлов в дереве.
 * Использует прямой обход (preorder_apply).
 *  O(n)
 */
template<typename T>
int count_nodes(TreeNode<T>* root) {
    int count = 0;
    preorder_apply<T>(root, [&](T&) { count++; });
    return count;
}

/**
 *  Определение глубины (высоты) дерева.
 * Глубина = максимальная длина пути от корня до листа.
 *  O(n)
 */
template<typename T>
int depth(TreeNode<T>* root) {
    if (!root) return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return 1 + max(leftDepth, rightDepth);
}

/**
 *  Печать дерева в виде структуры (повёрнуто на 90°).
 * Правое поддерево печатается сверху, левое снизу.
 *  O(n)
 */
template<typename T>
void print_tree(TreeNode<T>* root, int indent = 0) {
    if (!root) return;
    if (root->right) print_tree(root->right, indent + 4);
    if (indent) cout << string(indent, ' ');
    cout << root->value << "\n";
    if (root->left) print_tree(root->left, indent + 4);
}

void test_traversals();
void test_search();
void test_count_nodes();
void test_depth();
void test_print_tree();
void test_delete_tree();
void test_search_any();
void test_preorder();
void test_inorder();
void test_postorder();
void test_bfs();
void test_preorder_iterative();
void test_preorder_apply();
void test_inorder_apply();
void test_postorder_apply();