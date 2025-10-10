//Автор: Калашников А.Н.
#pragma once
#include <iostream>
#include <algorithm>  
#include <stdexcept>
#include "TreeNode.h"
#include <stack>
#include "TreeNodeFunctions.h"
#include "..\..\DSA-2\ClassIterator\AbstractIterator.h"
using namespace std;

void test_multiple_begin_calls();
void test_iterator_increment();
void test_iterator_dereference();
void test_iterator_comparison();
void test_iterator_full_traversal();
void test_iterator_exceptions();
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
    mutable vector<T>* last_traversal = nullptr;
    /*
     mutable — это ключевое слово, которое позволяет изменять
     данные в полях класса даже внутри константного метода (или константного объекта)
    */
public:
    /// Конструктор: инициализирует пустое дерево
    BinarySearchTree() : root(nullptr) {}

    /// Деструктор: очищает дерево
    ~BinarySearchTree() {
        clear();
    }

/// Класс итератора для бинарного дерева поиска 
/// Итератор предназначен для обхода элементов дерева в порядке возрастания (in-order)
/// Итератор не хранит указатель на сам узел дерева, а работает через вектор traversal,
/// в который заранее записаны все элементы дерева при вызове `begin()`.
    class Iterator : public AbstractIterator<T> {
        vector<T>* traversal; ///< Указатель на вектор, содержащий последовательность элементов дерева (in-order)
        size_t index;         ///< Текущая позиция в векторе (индекс текущего элемента)

    public:
       /// Конструктор итератора
       /// @param vec — указатель на вектор, в котором хранится результат обхода дерева
       /// @param i — индекс текущего элемента (по умолчанию 0)
       /// Если vec = nullptr, итератор считается пустым или указывающим на конец.
        Iterator(vector<T>* vec = nullptr, size_t i = 0)
            : traversal(vec), index(i) {
        }
        /// Оператор инкремента — переход к следующему элементу
        ///
        /// Проверяет, что вектор существует и что индекс ещё не вышел за пределы.
        /// Если индекс находится в пределах диапазона — увеличивает `index` на 1.
        /// @return ссылка на текущий итератор после смещения вперёд 
        Iterator& operator++() override {
            if (traversal && index < traversal->size())
                ++index;
            return *this;
        }

        /// Оператор разыменования `*`
        /// Используется для доступа к текущему значению итератора.
        /// @return ссылка на текущий элемент дерева, представленный в векторе `traversal`
        /// @throws out_of_range — если итератор указывает за пределы диапазона или не инициализирован.    
        T& operator*() const override {
            if (!traversal || index >= traversal->size())
                throw out_of_range("Элемент не существует");
            return (*traversal)[index];
        }

        /// Оператор сравнения на неравенство
        /// Логика:
        /// 1. Через `dynamic_cast` проверяется, действительно ли `other` является итератором того же типа (`Iterator`).
        ///    Если нет (например, сравнивают итератор BST и итератор списка), то возвращается `true` — они не равны.
        /// 2. Если оба итератора одного типа, они считаются равными только если:
        ///    - указывают на один и тот же вектор `traversal`
        ///    - и имеют одинаковый индекс `index` 
        /// @param other — другой итератор (через базовый тип AbstractIterator<T>)
        /// @return true, если итераторы указывают на разные элементы или на разные обходы
        bool operator!=(const AbstractIterator<T>& other) const override {
            const Iterator* it = dynamic_cast<const Iterator*>(&other);
            if (!it)
                return true;
            return traversal != it->traversal || index != it->index;
        }
    };

    /// Возвращает итератор, указывающий на первый элемент (начало обхода)
    /// 1. Создаёт новый динамический вектор `vec` и выполняет рекурсивный обход дерева (in-order),
    ///    записывая элементы в этот вектор.
    /// 2. Создаёт итератор `it_begin`, указывающий на первый элемент (`index = 0`).
    /// 3. Сохраняет указатель `last_traversal = vec`, чтобы метод `end()` мог использовать тот же вектор.
    Iterator begin() const {
        // создаём вектор и наполняем его обходом in-order
        vector<T>* vec = new vector<T>();
        inorder(root, *vec);

        // создаём итератор, указывающий на начало
        Iterator it_begin(vec, 0);

        // сохраняем указатель, чтобы end() мог использовать тот же самый вектор
        last_traversal = vec;
        return it_begin;
    }

    /// Возвращает итератор, указывающий на элемент после последнего
    /// Использует тот же самый вектор `last_traversal`, что и `begin()`,
    /// чтобы оба итератора работали с одним и тем же набором данных.
    /// Возвращает итератор, указывающий на индекс `size()` — то есть «один элемент за последним».
    Iterator end() const {
        // если обход ещё не выполнялся (last_traversal == nullptr), возвращаем пустой итератор
        if (!last_traversal)
            return Iterator(nullptr, 0);
        // создаём итератор, указывающий за последний элемент в векторе
        return Iterator(last_traversal, last_traversal->size());
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
        delete last_traversal; // очищаем память от последнего обхода
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
