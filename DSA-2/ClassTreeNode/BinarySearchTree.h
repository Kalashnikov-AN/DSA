#pragma once
#include <iostream>
#include <algorithm>  
#include <stdexcept>
#include "TreeNode.h"
#include <stack>
using namespace std;

void test_insert();
void test_size();
void test_height();
void test_remove();
void test_clear_empty();
void test_successor();
void test_search();


/**
 * @brief Класс бинарного дерева поиска (BST).
 * Содержит методы вставки, удаления, поиска и работы с деревом.
 */
template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root; ///< Корень дерева

public:
    /// Конструктор: инициализирует пустое дерево
    BinarySearchTree() : root(nullptr) {}

    /// Деструктор: очищает дерево
    ~BinarySearchTree() {
        clear();
    }

    /**
     * @brief Вставка значения в дерево.
     * @complexity O(h), где h — высота дерева.
     */
    void insert(const T& value) {
        if (!root) {
            root = new TreeNode<T>(value);
            return;
        }

        TreeNode<T>* parent = nullptr;
        TreeNode<T>* curr = root;

        while (curr) {
            parent = curr;
            if (value < curr->value) {
                curr = curr->left;
            }
            else if (value > curr->value) {
                curr = curr->right;
            }
            else {
                return; // дубликаты игнорируем
            }
        }

        if (value < parent->value)
            parent->left = new TreeNode<T>(value);
        else
            parent->right = new TreeNode<T>(value);
    }

    /**
     * @brief Удаление значения из дерева.
     * @complexity O(h), где h — высота дерева.
     */
    void remove(const T& value) {
        TreeNode<T>* parent = nullptr;
        TreeNode<T>* curr = root;

        // Ищем узел
        while (curr && curr->value != value) {
            parent = curr;
            if (value < curr->value)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (!curr) return; // элемент не найден

        // Случай 1: узел без потомков
        if (!curr->left && !curr->right) {
            if (!parent) root = nullptr;
            else if (parent->left == curr) parent->left = nullptr;
            else parent->right = nullptr;
            delete curr;
        }
        // Случай 2: один потомок
        else if (!curr->left || !curr->right) {
            TreeNode<T>* child = curr->left ? curr->left : curr->right;
            if (!parent) root = child;
            else if (parent->left == curr) parent->left = child;
            else parent->right = child;
            delete curr;
        }
        // Случай 3: два потомка
        else {
            // ищем потомка (минимум в правом поддереве)
            TreeNode<T>* succParent = curr;
            TreeNode<T>* succ = curr->right;
            while (succ->left) {
                succParent = succ;
                succ = succ->left;
            }
            curr->value = succ->value; // копируем значение
            // удаляем потомка
            if (succParent->left == succ) succParent->left = succ->right;
            else succParent->right = succ->right;
            delete succ;
        }
    }

    /**
     * @brief Подсчёт количества узлов.
     * @complexity O(n), где n — количество узлов.
     */
    int size() const {
        if (!root) return 0;
        int count = 0;
        std::stack<TreeNode<T>*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode<T>* node = st.top(); st.pop();
            count++;
            if (node->left) st.push(node->left);
            if (node->right) st.push(node->right);
        }
        return count;
    }

    /**
     * @brief Определение высоты дерева.
     * @complexity O(n).
     */
    int height() const {
        if (!root) return 0;

        int maxDepth = 0;
        std::stack<TreeNode<T>*> nodeStack;
        std::stack<int> depthStack;

        nodeStack.push(root);
        depthStack.push(1);

        while (!nodeStack.empty()) {
            TreeNode<T>* node = nodeStack.top(); nodeStack.pop();
            int depth = depthStack.top(); depthStack.pop();

            if (depth > maxDepth) {
                maxDepth = depth;
            }

            if (node->left) {
                nodeStack.push(node->left);
                depthStack.push(depth + 1);
            }
            if (node->right) {
                nodeStack.push(node->right);
                depthStack.push(depth + 1);
            }
        }

        return maxDepth;
    }


    /**
     * @brief Проверка, пустое ли дерево.
     * @complexity O(1).
     */
    bool empty() const {
        return root == nullptr;
    }

    /**
     * @brief Получение указателя на корень дерева.
     * @complexity O(1).
     */
    TreeNode<T>* get_root() const {
        return root;
    }

    /**
     * @brief Очистка дерева (удаление всех узлов).
     * @complexity O(n).
     */
    void clear() {
        if (!root) return;
        std::stack<TreeNode<T>*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode<T>* node = st.top(); st.pop();
            if (node->left) st.push(node->left);
            if (node->right) st.push(node->right);
            delete node;
        }
        root = nullptr;
    }

    /**
     * @brief Поиск successor (следующего большего элемента).
     * @param value значение, для которого ищем successor
     * @return указатель на successor или nullptr
     * @complexity O(h).
     */
    TreeNode<T>* successor(const T& value) const {
        TreeNode<T>* curr = root;
        TreeNode<T>* succ = nullptr;

        while (curr) {
            if (value < curr->value) {
                succ = curr;
                curr = curr->left;
            }
            else if (value > curr->value) {
                curr = curr->right;
            }
            else {
                if (curr->right) {
                    TreeNode<T>* tmp = curr->right;
                    while (tmp->left) tmp = tmp->left;
                    return tmp;
                }
                break;
            }
        }
        return succ;
    }

/**
 * @brief Поиск ключа в бинарном дереве поиска (BST).
 * @return указатель на найденный узел или nullptr
 * O(h), где h — высота дерева
 *   худший случай: O(n) (вырожденное дерево),
 */
TreeNode<T>* search(const T& key) {
    TreeNode<T>* curr = root;

    while (curr) {
        if (key == curr->value) {
            return curr; // нашли узел
        }
        else if (key < curr->value) {
            curr = curr->left; // идём в левое поддерево
        }
        else {
            curr = curr->right; // идём в правое поддерево
        }
    }

    return nullptr; // элемент не найден
}


};
