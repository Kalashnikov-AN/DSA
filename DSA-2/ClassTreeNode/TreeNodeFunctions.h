#pragma once
#include "TreeNode.h"
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <iostream>

// NLR (прямой обход): Node, Left, Right
template<typename T>
void preorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    result.push_back(node->value);
    preorder(node->left, result);
    preorder(node->right, result);
}

template<typename T>
void preorder_print(TreeNode<T>* node) {
    if (!node) return;
    std::cout << node->value << " ";
    preorder_print(node->left);
    preorder_print(node->right);
}

template<typename T>
void preorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    func(node->value);
    preorder_apply(node->left, func);
    preorder_apply(node->right, func);
}

// LNR (симметричный обход): Left, Node, Right
template<typename T>
void inorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

template<typename T>
void inorder_print(TreeNode<T>* node) {
    if (!node) return;
    inorder_print(node->left);
    std::cout << node->value << " ";
    inorder_print(node->right);
}

template<typename T>
void inorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    inorder_apply(node->left, func);
    func(node->value);
    inorder_apply(node->right, func);
}

// LRN (обратный обход): Left, Right, Node
template<typename T>
void postorder(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->value);
}

template<typename T>
void postorder_print(TreeNode<T>* node) {
    if (!node) return;
    postorder_print(node->left);
    postorder_print(node->right);
    std::cout << node->value << " ";
}

template<typename T>
void postorder_apply(TreeNode<T>* node, std::function<void(T&)> func) {
    if (!node) return;
    postorder_apply(node->left, func);
    postorder_apply(node->right, func);
    func(node->value);
}

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

/// Нерекурсивный обход в грубину
template<typename T>
void preorder_iterative(TreeNode<T>* root, std::vector<T>& result) {
    if (!root) return;
    std::stack<TreeNode<T>*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode<T>* node = st.top(); st.pop();
        result.push_back(node->value);
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}

template<typename T>
TreeNode<T>* search(TreeNode<T>* root, const T& key) {
    if (!root) return nullptr;
    if (root->value == key) return root;
    if (key < root->value) return search(root->left, key);
    else return search(root->right, key);
}
// BigO: O(h), где h — высота дерева (в худшем случае O(n), в сбалансированном O(log n))


template<typename T>
/// Удаление всех узлов дерева методом обхода Морриса
void delete_tree(TreeNode<T>* root) {
    // Удаляем все узлы дерева
    while (root) {
        if (root->left) {
            TreeNode<int>* tmp = root->left;   // сохраняем ссылку на левого потомка
            root->left = tmp->right;           // переносим правую ветку наверх
            tmp->right = root;                 // делаем временный цикл
            root = tmp;                        // спускаемся вниз
        }
        else {
            TreeNode<int>* tmp = root;         // текущий узел
            root = root->right;                // переходим направо
            //cout << tmp->value << endl;
            delete tmp;                        // удаляем узел

            //i++;
            //cout << i << endl;
        }
    }
}

// Подсчет узлов
template<typename T>
int count_nodes(TreeNode<T>* root) {
    int count = 0;
    preorder_apply<T>(root, [&](T&) { count++; }); // как параметр передаем лямбда функцию для увеличения счётчика
    return count;
}

/// Возвращает глубину дерева методом рекурсивного обхода LRN
template<typename T>
int depth(TreeNode<T>* root) { // вариация LRN 
    if (!root) return 0; // пустое дерево → глубина 0
    int leftDepth = depth(root->left);   // глубина левого поддерева
    int rightDepth = depth(root->right);  // глубина правого поддерева
    return 1 + std::max(leftDepth, rightDepth); // +1 за текущий узел
}


template<typename T>
void print_tree(TreeNode<T>* root, int indent = 0) {
    if (!root) return;
    if (root->right) print_tree(root->right, indent + 4);
    if (indent) std::cout << std::string(indent, ' ');
    std::cout << root->value << "\n";
    if (root->left) print_tree(root->left, indent + 4);
}
