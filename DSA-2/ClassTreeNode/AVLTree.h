#pragma once
#include "BinarySearchTree.h"

/**
 *  Класс AVL дерева (наследуется от BinarySearchTree)
 *  Реализует самобалансирующееся бинарное дерево поиска.
 *  Поддерживает балансировку после вставки и удаления элементов.
 */
template<typename T>
class AVLTree : public BinarySearchTree<T> {
private:
    using Node = TreeNode<T>;  // удобное сокращение типа узла

    /// Получение высоты узла (nullptr имеет высоту 0)
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    /// Вычисление баланса узла (разница высот левого и правого поддерева)
    int getBalance(Node* node) const {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    /// Обновление высоты узла на основе потомков
    void updateHeight(Node* node) {
        if (node)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    /// Правый поворот поддерева вокруг узла y
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Выполняем поворот
        x->right = y;
        y->left = T2;

        // Обновляем высоты
        updateHeight(y);
        updateHeight(x);

        // Новый корень поддерева
        return x;
    }

    /// Левый поворот поддерева вокруг узла x
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Выполняем поворот
        y->left = x;
        x->right = T2;

        // Обновляем высоты
        updateHeight(x);
        updateHeight(y);

        // Новый корень поддерева
        return y;
    }

    /// Рекурсивная вставка с балансировкой
    Node* insertRec(Node* node, const T& key) {
        // Стандартная вставка BST
        if (!node)
            return new Node(key);

        if (key < node->value)
            node->left = insertRec(node->left, key);
        else if (key > node->value)
            node->right = insertRec(node->right, key);
        else
            return node; // дубликаты не вставляем

        // Обновляем высоту текущего узла
        updateHeight(node);

        // Вычисляем баланс
        int balance = getBalance(node);

        // Балансировка 4 случаев:

        // 1. Левый Левый (Right Rotation)
        if (balance > 1 && key < node->left->value)
            return rotateRight(node);

        // 2. Правый Правый (Left Rotation)
        if (balance < -1 && key > node->right->value)
            return rotateLeft(node);

        // 3. Левый Правый (Left Rotation -> Right Rotation)
        if (balance > 1 && key > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // 4. Правый Левый (Right Rotation -> Left Rotation)
        if (balance < -1 && key < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // узел уже сбалансирован
    }

    /// Рекурсивное удаление с балансировкой
    //Node* removeRec(Node* node, const T& key) {
    //    if (!node) return node;

    //    // Обычное удаление из BST
    //    if (key < node->value)
    //        node->left = removeRec(node->left, key);
    //    else if (key > node->value)
    //        node->right = removeRec(node->right, key);
    //    else {
    //        // Узел найден
    //        if (!node->left || !node->right) {
    //            Node* temp = node->left ? node->left : node->right;

    //            if (!temp) {
    //                // Нет потомков
    //                temp = node;
    //                node = nullptr;
    //            }
    //            else {
    //                // Один потомок
    //                *node = *temp;
    //            }
    //            delete temp;
    //        }
    //        else {
    //            // Два потомка — находим inorder-последователя
    //            Node* succ = node->right;
    //            while (succ->left)
    //                succ = succ->left;
    //            node->value = succ->value;
    //            node->right = removeRec(node->right, succ->value);
    //        }
    //    }

    //    // Если дерево стало пустым
    //    if (!node)
    //        return node;

    //    // Обновляем высоту
    //    updateHeight(node);

    //    // Проверяем баланс
    //    int balance = getBalance(node);

    //    // Балансировка (аналогично вставке)
    //    if (balance > 1 && getBalance(node->left) >= 0)
    //        return rotateRight(node);

    //    if (balance > 1 && getBalance(node->left) < 0) {
    //        node->left = rotateLeft(node->left);
    //        return rotateRight(node);
    //    }

    //    if (balance < -1 && getBalance(node->right) <= 0)
    //        return rotateLeft(node);

    //    if (balance < -1 && getBalance(node->right) > 0) {
    //        node->right = rotateRight(node->right);
    //        return rotateLeft(node);
    //    }

    //    return node;
    //}
    Node* removeRec(Node* node, const T& key) {
        if (!node) return node;

        // Стандартное удаление из BST
        if (key < node->value) {
            node->left = removeRec(node->left, key);
        }
        else if (key > node->value) {
            node->right = removeRec(node->right, key);
        }
        else { // узел найден
            // 1. Нет потомков
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // 2. Один потомок
            else if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child; // возвращаем потомка, чтобы родитель переписал свой указатель
            }
            // 3. Два потомка
            else {
                // находим inorder-последователя (минимум в правом поддереве)
                Node* succ = node->right;
                while (succ->left)
                    succ = succ->left;
                node->value = succ->value; // копируем значение
                node->right = removeRec(node->right, succ->value); // удаляем successor
            }
        }

        // Обновляем высоту
        updateHeight(node);

        // Проверяем баланс
        int balance = getBalance(node);

        // Балансировка 4 случаев
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }


public:
    /// Конструктор AVL дерева
    AVLTree() : BinarySearchTree<T>() {}

    /// Вставка с балансировкой
    void insert(const T& key) {
        this->root = insertRec(this->root, key);
    }

    /// Удаление с балансировкой
    void remove(const T& key) {
        this->root = removeRec(this->root, key);
    }
};

void test_insertAVL();
void test_removeAVL();
void test_searchAVL();
void test_heightAVL();
void run_all_tests();