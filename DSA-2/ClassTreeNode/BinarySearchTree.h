//Автор: Калашников А.Н.
#pragma once
#include <iostream>
#include <algorithm>  
#include <stdexcept>
#include "TreeNode.h"
#include <stack>
#include "TreeNodeFunctions.h"
using namespace std;

void test_insert();
void test_size();
void test_height();
void test_remove();
void test_clear_empty();
void test_successor();
void test_search();


/**
 *  Класс бинарного дерева поиска (BST).
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
     *  Вставка значения в дерево.
     *  O(h), где h — высота дерева.
     */
    void insert(const T& value) {
    // Если корень пустой (дерево ещё не создано), 
    // то новый элемент становится корнем
        if (!root) {
            root = new TreeNode<T>(value);
            return;
        }

        // Если дерево уже существует, начинаем поиск места вставки
        TreeNode<T>* parent = nullptr;
        TreeNode<T>* curr = root;

        while (curr) { // спускаемся вниз по дереву
            parent = curr; // запоминаем родителя
            if (value < curr->value) { // если вставляемое меньше текущего
                curr = curr->left; // спускаемся влево
            }
            else if (value > curr->value) { // если вставляемое больше текущего
                curr = curr->right; // спускаемся вправо
            }
            else {
                return; // дубликаты игнорируем
            }
        }
         // если вставляемое меньше значения родителя
        if (value < parent->value)
            parent->left = new TreeNode<T>(value); // производим вставку влево
        else    // иначе
            parent->right = new TreeNode<T>(value); // производим вставку вправо
    }

    /**
     *  Удаление значения из дерева.
     *  O(h), где h — высота дерева.
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
     *  Подсчёт количества узлов.
     *  O(n), где n — количество узлов.
     */
    size_t size() const {
        return count_nodes(root);
    }

    /**
     *  Определение высоты дерева.
     *  O(n).
     */
    int height() const {
        return depth(root);
    }


    /**
     *  Проверка, пустое ли дерево.
     *  O(1).
     */
    bool empty() const {
        return root == nullptr;
    }

    /**
     *  Получение указателя на корень дерева.
     *  O(1).
     */
    TreeNode<T>* get_root() const {
        return root;
    }

    /**
     *  Очистка дерева (удаление всех узлов).
     *  O(n).
     */
    void clear() {
        delete_tree(root);
    }

    /**
     *  Поиск successor (следующего большего элемента) O(h).
     * @param value значение, для которого ищем successor
     * @return указатель на successor или nullptr
     */
    TreeNode<T>* successor(const T& value) const {
        TreeNode<T>* curr = root; // начинаем поиск с корня дерева
        TreeNode<T>* succ = nullptr; // переменная для хранения возможного след. наибольшего
        // спускаемся по дереву
        while (curr) {
            if (value < curr->value) { // значение текущего узла больше value
                succ = curr; // значит узел может подходить для след. наибольшего
                curr = curr->left; // но возможно есть узел со значением еще меньше
            }
            else if (value > curr->value) { // если значение текущего узла меньше value
                curr = curr->right; // идем вправо, т.к. нам нужен узел со значением > value
            }
            else { // если значение текущего узла = value
                if (curr->right) { 
                    TreeNode<T>* tmp = curr->right; // спускаемся вправо на один уровень
                    while (tmp->left) tmp = tmp->left; // идём влево до конца
                    return tmp; // возвращаем след. наибольший
                }
                break; // выходим из цикла
            }
        }
        return succ; // возвращаем след. наибольший по окончании выполнения цикла while
    }

/**
 *  Поиск узла со значением key в бинарном дереве поиска (BST).
 * O(h), где h — высота дерева
 * худший случай: O(n) (вырожденное дерево),
 * @return указатель на найденный узел или nullptr
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
