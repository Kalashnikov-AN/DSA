#pragma once
#include "TreeNode.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>

/// ================= ОБХОДЫ БИНАРНОГО ДЕРЕВА =================

/**
 * @brief Прямой обход (NLR: Node, Left, Right)
 * Результат сохраняется в вектор.
 * @tparam T тип данных в узлах дерева
 * @param node корень поддерева
 * @param result вектор для сохранения порядка обхода
 * @complexity O(n), где n — количество узлов
 */
template<typename T>
void preorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    result.push_back(node->value);       // 1. обрабатываем текущий узел
    preorder(node->left, result);        // 2. рекурсивно левое поддерево
    preorder(node->right, result);       // 3. рекурсивно правое поддерево
}

/**
 * @brief Прямой обход (печать значений узлов).
 * @complexity O(n)
 */
template<typename T>
void preorder_print(TreeNode<T>* node) {
    if (!node) return;
    std::cout << node->value << " ";     // сначала выводим текущий узел
    preorder_print(node->left);          // затем левое поддерево
    preorder_print(node->right);         // затем правое поддерево
}

/**
 * @brief Прямой обход с применением функции к каждому узлу.
 * @param func функция (лямбда или std::function), применяемая к значению
 * @complexity O(n)
 */
template<typename T>
void preorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    func(node->value);                   // применяем функцию к текущему узлу
    preorder_apply(node->left, func);    // левое поддерево
    preorder_apply(node->right, func);   // правое поддерево
}

/// --- Симметричный обход (LNR: Left, Node, Right) ---

/**
 * @brief Симметричный обход (LNR), результат в вектор.
 * Узлы обрабатываются в порядке возрастания (если дерево поиска).
 * @complexity O(n)
 */
template<typename T>
void inorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    inorder(node->left, result);         // сначала левое поддерево
    result.push_back(node->value);       // потом текущий узел
    inorder(node->right, result);        // потом правое поддерево
}

/**
 * @brief Симметричный обход с печатью.
 * @complexity O(n)
 */
template<typename T>
void inorder_print(TreeNode<T>* node) {
    if (!node) return;
    inorder_print(node->left);
    std::cout << node->value << " ";
    inorder_print(node->right);
}

/**
 * @brief Симметричный обход с применением функции к каждому узлу.
 * @complexity O(n)
 */
template<typename T>
void inorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    inorder_apply(node->left, func);
    func(node->value);
    inorder_apply(node->right, func);
}

/// --- Обратный обход (LRN: Left, Right, Node) ---

/**
 * @brief Обратный обход (LRN), результат в вектор.
 * @complexity O(n)
 */
template<typename T>
void postorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->value);       // последний шаг — текущий узел
}

/**
 * @brief Обратный обход с печатью.
 * @complexity O(n)
 */
template<typename T>
void postorder_print(TreeNode<T>* node) {
    if (!node) return;
    postorder_print(node->left);
    postorder_print(node->right);
    std::cout << node->value << " ";
}

/**
 * @brief Обратный обход с применением функции к каждому узлу.
 * @complexity O(n)
 */
template<typename T>
void postorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    postorder_apply(node->left, func);
    postorder_apply(node->right, func);
    func(node->value);
}

/// ================= ДРУГИЕ ОБХОДЫ =================

/**
 * @brief Обход в ширину (BFS, уровень за уровнем).
 * Использует очередь.
 * @complexity O(n)
 */
template<typename T>
void bfs(TreeNode<T>* root, std::vector<T>& result) {
    if (!root) return;
    std::queue<TreeNode<T>*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode<T>* node = q.front(); q.pop();
        result.push_back(node->value);
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

/**
 * @brief Нерекурсивный прямой обход (DFS), с использованием стека.
 * Полезно для больших деревьев, чтобы избежать переполнения стека вызовов.
 * @complexity O(n)
 */
template<typename T>
void preorder_iterative(TreeNode<T>* root, std::vector<T>& result) {
    if (!root) return;
    std::stack<TreeNode<T>*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode<T>* node = st.top(); st.pop();
        result.push_back(node->value);
        if (node->right) st.push(node->right); // сначала правый, чтобы левый обработался раньше
        if (node->left) st.push(node->left);
    }
}


/**
 * @brief Поиск значения в произвольном бинарном дереве (не обязательно BST).
 * Использует обход в глубину (DFS).
 * @tparam T тип данных
 * @param root корень дерева
 * @param key искомое значение
 * @return указатель на найденный узел или nullptr
 * @complexity O(n), где n — количество узлов
 */
template<typename T>
TreeNode<T>* search_any(TreeNode<T>* root, const T& key) {
    if (!root) return nullptr;

    if (root->value == key) return root; // нашли!

    // ищем в левом поддереве
    TreeNode<T>* leftResult = search_any(root->left, key);
    if (leftResult) return leftResult;

    // если не нашли слева → ищем справа
    return search_any(root->right, key);
}


/**
 * @brief Удаление всего дерева (освобождение памяти).
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
 * @brief Подсчёт количества узлов в дереве.
 * Использует прямой обход (preorder_apply).
 * @complexity O(n)
 */
template<typename T>
int count_nodes(TreeNode<T>* root) {
    int count = 0;
    preorder_apply<T>(root, [&](T&) { count++; });
    return count;
}

/**
 * @brief Определение глубины (высоты) дерева.
 * Глубина = максимальная длина пути от корня до листа.
 * @complexity O(n)
 */
template<typename T>
int depth(TreeNode<T>* root) {
    if (!root) return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return 1 + std::max(leftDepth, rightDepth);
}

/**
 * @brief Печать дерева в виде структуры (повёрнуто на 90°).
 * Правое поддерево печатается сверху, левое снизу.
 * @complexity O(n)
 */
template<typename T>
void print_tree(TreeNode<T>* root, int indent = 0) {
    if (!root) return;
    if (root->right) print_tree(root->right, indent + 4);
    if (indent) std::cout << std::string(indent, ' ');
    std::cout << root->value << "\n";
    if (root->left) print_tree(root->left, indent + 4);
}

void test_traversals();
void test_search();
void test_count_nodes();
void test_depth();
void test_print_tree();
void test_delete_tree();
void test_search_any();
