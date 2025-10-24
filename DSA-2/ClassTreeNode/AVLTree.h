#pragma once
#include "BinarySearchTree.h"

/**
 *  ����� AVL ������ (����������� �� BinarySearchTree)
 *  ��������� ������������������� �������� ������ ������.
 *  ������������ ������������ ����� ������� � �������� ���������.
 */
template<typename T>
class AVLTree : public BinarySearchTree<T> {
private:
    using Node = TreeNode<T>;  // ������� ���������� ���� ����

    /// ��������� ������ ���� (nullptr ����� ������ 0)
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    /// ���������� ������� ���� (������� ����� ������ � ������� ���������)
    int getBalance(Node* node) const {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    /// ���������� ������ ���� �� ������ ��������
    void updateHeight(Node* node) {
        if (node)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    /// ������ ������� ��������� ������ ���� y
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // ��������� �������
        x->right = y;
        y->left = T2;

        // ��������� ������
        updateHeight(y);
        updateHeight(x);

        // ����� ������ ���������
        return x;
    }

    /// ����� ������� ��������� ������ ���� x
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // ��������� �������
        y->left = x;
        x->right = T2;

        // ��������� ������
        updateHeight(x);
        updateHeight(y);

        // ����� ������ ���������
        return y;
    }

    /// ����������� ������� � �������������
    Node* insertRec(Node* node, const T& key) {
        // ����������� ������� BST
        if (!node)
            return new Node(key);

        if (key < node->value)
            node->left = insertRec(node->left, key);
        else if (key > node->value)
            node->right = insertRec(node->right, key);
        else
            return node; // ��������� �� ���������

        // ��������� ������ �������� ����
        updateHeight(node);

        // ��������� ������
        int balance = getBalance(node);

        // ������������ 4 �������:

        // 1. ����� ����� (Right Rotation)
        if (balance > 1 && key < node->left->value)
            return rotateRight(node);

        // 2. ������ ������ (Left Rotation)
        if (balance < -1 && key > node->right->value)
            return rotateLeft(node);

        // 3. ����� ������ (Left Rotation -> Right Rotation)
        if (balance > 1 && key > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // 4. ������ ����� (Right Rotation -> Left Rotation)
        if (balance < -1 && key < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // ���� ��� �������������
    }

    /// ����������� �������� � �������������
    //Node* removeRec(Node* node, const T& key) {
    //    if (!node) return node;

    //    // ������� �������� �� BST
    //    if (key < node->value)
    //        node->left = removeRec(node->left, key);
    //    else if (key > node->value)
    //        node->right = removeRec(node->right, key);
    //    else {
    //        // ���� ������
    //        if (!node->left || !node->right) {
    //            Node* temp = node->left ? node->left : node->right;

    //            if (!temp) {
    //                // ��� ��������
    //                temp = node;
    //                node = nullptr;
    //            }
    //            else {
    //                // ���� �������
    //                *node = *temp;
    //            }
    //            delete temp;
    //        }
    //        else {
    //            // ��� ������� � ������� inorder-�������������
    //            Node* succ = node->right;
    //            while (succ->left)
    //                succ = succ->left;
    //            node->value = succ->value;
    //            node->right = removeRec(node->right, succ->value);
    //        }
    //    }

    //    // ���� ������ ����� ������
    //    if (!node)
    //        return node;

    //    // ��������� ������
    //    updateHeight(node);

    //    // ��������� ������
    //    int balance = getBalance(node);

    //    // ������������ (���������� �������)
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

        // ����������� �������� �� BST
        if (key < node->value) {
            node->left = removeRec(node->left, key);
        }
        else if (key > node->value) {
            node->right = removeRec(node->right, key);
        }
        else { // ���� ������
            // 1. ��� ��������
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // 2. ���� �������
            else if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child; // ���������� �������, ����� �������� ��������� ���� ���������
            }
            // 3. ��� �������
            else {
                // ������� inorder-������������� (������� � ������ ���������)
                Node* succ = node->right;
                while (succ->left)
                    succ = succ->left;
                node->value = succ->value; // �������� ��������
                node->right = removeRec(node->right, succ->value); // ������� successor
            }
        }

        // ��������� ������
        updateHeight(node);

        // ��������� ������
        int balance = getBalance(node);

        // ������������ 4 �������
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
    /// ����������� AVL ������
    AVLTree() : BinarySearchTree<T>() {}

    /// ������� � �������������
    void insert(const T& key) {
        this->root = insertRec(this->root, key);
    }

    /// �������� � �������������
    void remove(const T& key) {
        this->root = removeRec(this->root, key);
    }
};

void test_insertAVL();
void test_removeAVL();
void test_searchAVL();
void test_heightAVL();
void run_all_tests();