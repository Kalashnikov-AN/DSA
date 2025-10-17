// Автор: Калашников А.Н.
#pragma once
#include <stdexcept>
#include <cstddef>
#include "..\..\DSA-2\ClassIterator\AbstractIterator.h"
using namespace std;

/// Шаблонный класс двусвязного списка
template <typename T>
class DoublyLinkedList {
private:
    /// Внутренняя структура узла списка
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) {
            data = value;
            prev = nullptr;
            next = nullptr;
        }
    };
    int _size; /// количество элементов 
    Node* head;  /// указатель на голову списка
    Node* tail;  /// указатель на хвост списка

public:

/**
 *  Класс итератора для двусвязного списка.
 *
 * Реализует базовый интерфейс итератора (AbstractIterator<T>) для прохода
 * по элементам двусвязного списка 
 *
 * Каждый объект Iterator хранит указатель current — это текущий узел (Node*),
 * на который итератор указывает в данный момент.
 *
 * Основные операции:
 * - operator++() — переход к следующему элементу 
 * - operator*() — разыменование итератора 
 * - operator!=() — сравнение двух итераторов 
 */
    class Iterator : public AbstractIterator<T> {
        /// Указатель на текущий узел, на который указывает итератор
        Node* current;

    public:
    /**
     * Конструктор итератора.
     * @param node Указатель на узел, с которого начинается итерация (по умолчанию nullptr).
     *
     * Если node == nullptr, итератор считается указывающим на "конец" списка
     */
        Iterator(Node* node = nullptr) : current(node) {}

    /**
    * Оператор префиксного инкремента 
    *
    * Перемещает итератор на следующий элемент списка.
    * Если текущий элемент существует 
    * итератор просто сдвигается на current->next.
    *
    * Если итератор уже указывает на конец (nullptr),
    * то он таким и остаётся.
    *
    * @return Ссылка на сам итератор 
    */
        Iterator& operator++() override {
            if (current)
                current = current->next;
            return *this;
        }

     /**
     * Оператор разыменования *
     *
     * Возвращает ссылку на данные data текущего узла.
     * 
     * @throws out_of_range если итератор указывает на несуществующий элемент или конец списка.
     *
     * @return Ссылка на значение типа T, хранящееся в текущем узле.
     */
        T& operator*() const override {
            if (!current)
                throw out_of_range("Элемент не существует");
            return current->data;
        }

     /**
     * Оператор сравнения на неравенство it1 != it2.
     *
     * Используется, чтобы проверить, указывают ли два итератора на разные элементы.
     *
     * Поскольку параметр имеет тип AbstractIterator<T>&, используется dynamic_cast
     * для безопасного приведения к типу Iterator*.
     * Это необходимо, потому что мы можем сравнивать итераторы разных типов,
     * реализующих один интерфейс AbstractIterator<T>.
     *
     * @param other Другой итератор для сравнения.
     * @return true, если итераторы указывают на разные узлы;
     *         false, если они указывают на один и тот же узел.
     */
        bool operator!=(const AbstractIterator<T>& other) const override {
            // Пробуем привести ссылку к типу Iterator*
            const Iterator* it = dynamic_cast<const Iterator*>(&other);
            // Если приведение не удалось (итераторы разных типов) или указатели разные - итераторы не равны
            return !it || this->current != it->current;
        }
    };

    /// Возвращает итератор, указывающий на первый элемент
    Iterator begin() const {
        return Iterator(head);
    }

    /// Возвращает итератор, указывающий на элемент после последнего
    Iterator end() const {
        return Iterator(nullptr);
    }

    /// Конструктор: создаёт пустой список
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    /// Деструктор: освобождает все узлы
    ~DoublyLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        _size = 0;
    }

    /// Конструктор копирования, other - копируемый объект
    DoublyLinkedList(const DoublyLinkedList& other)  {
        Node* curr = other.head;
        while (curr) {
            insert_back(curr->data);
            curr = curr->next;
        }
    }

    /// Оператор присваивания копированием, other - копируемый объект, возвращает ссылку на измённый исходный объект
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* curr = other.head;
            while (curr) {
                insert_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    /// Конструктор перемещения, other - rvalue ссылка на перемещаемый объект
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), _size(other._size) {
        other.head = nullptr;
        other.tail = nullptr;
        other._size = 0;
    }

    /// Оператор присваивания перемещением, other - rvalue ссылка на перемещаемый объект, возвращает ссылку на измённый исходный объект
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            _size = other._size;
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    /// Поиск элемента по значению, возвращает указатель на первый найденный узел или nullptr
    /// Average O(n)
    Node* find(const T& value) const {
        Node* curr = head;
        while (curr) {
            if (curr->data == value)
                return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    /// Вставить в начало списка значение value (O(1))
    void insert_front(const T& value) {
        Node* node = new Node(value);
        node->next = head;
        if (head)
            head->prev = node;
        head = node;
        if (!tail) // необходимо для случая вставки первого элемента в пустой список
            tail = node;
        _size++;
    }

    /// Вставить в конец списка значение value (O(1))
    void insert_back(const T& value) {
        Node* node = new Node(value);
        node->prev = tail;
        if (tail)
            tail->next = node;
        tail = node;
        if (!head) // необходимо для случая вставки первого элемента в пустой список
            head = node;
        _size++;
    }


    /// Удаление первого элемента (O(1))
    void remove_front() {
        if (!head)
            return;
        Node* to_delete = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete to_delete;
        _size--;
    }

    ///  Удаление последнего элемента (O(1))
    void remove_back() {
        if (!tail) throw underflow_error("Список пуст");
        Node* to_delete = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete to_delete;
        _size--;
    }

    /**
     * Удаление конкретного узла (O(n) для поиска)
     * @param node узел для удаления
     */
    void remove(Node* node) {
        if (!node)
            return;
        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;
        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;
        delete node;
        _size--;
    }

    /**
     * Конкатенация другого списка в конец текущего списка (O(n))
     * @param other другой список
     * После конкатенации other становится пустым
     */
    void concatenate(DoublyLinkedList& other) {
        Node* curr = other.head;
        while (curr) {
            insert_back(curr->data);
            curr = curr->next;
        }
        // очистим other 
        other.clear();
    }

    ///  Получить размер списка, O(1)
    size_t size() const {
        return _size;
    }

    ///  Полная очистка списка, освобождает все узлы
    void clear() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
        _size = 0;
    }

    /**
       * Поиск узла по индексу, возвращает указатель на узел или nullptr
       * @param index номер элемента в списке (0..size()-1)
       * @return Node* указатель на узел или nullptr, если индекс неверен
       */
    Node* node_at(size_t index) const {
        Node* curr = head;
        size_t i = 0;
        while (curr && i < index) {
            curr = curr->next;
            ++i;
        }
        return (i == index ? curr : nullptr);
    }

    /**
     * Доступ к элементу по индексу, возвращает ссылку на данные
     * @param index номер элемента
     * @throw out_of_range если индекс >= size()
     */
    T& at(size_t index) {
        Node* node = node_at(index);
        if (!node)
            throw out_of_range("Index out of range");
        return node->data;
    }

    /**
     * Константный доступ к элементу по индексу
     * @param index номер элемента
     * @throw out_of_range если индекс >= size()
     */const T& at(size_t index) const {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }

     /**
      *  Оператор доступа по индексу с помощью []
      * @param index позиция элемента
      * @return ссылка на элемент
      */
     T& operator[](size_t index) {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }

     /**
      *  Константный оператор доступа по индексу с помощью []
      * @param index позиция элемента
      * @return константная ссылка на элемент
      */
     const T& operator[](size_t index) const {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }


/**
 *  Удаление элемента по индексу 
 * @param index индекс удаляемого элемента
 * @throw out_of_range если индекс >= size()
 */
void remove_at(size_t index) {
    if (index >= _size)
        throw out_of_range("Index out of range");
    Node* node = node_at(index);
    remove(node);
}

/**
 *  Вставка элемента по индексу 
 * @param index позиция для вставки (0 <= index <= size())
 * @param value значение для вставки
 * @throw out_of_range если индекс > size()
 */
void insert_at(size_t index, const T& value) {
    if (index > _size)
        throw out_of_range("Index out of range");

    if (index == 0) {
        insert_front(value);
    }
    else if (index == _size) {
        insert_back(value);
    }
    else {
        Node* curr = node_at(index); // текущий элемент на позиции index
        Node* node = new Node(value);
        Node* prev = curr->prev;

        node->next = curr;
        node->prev = prev;
        prev->next = node;
        curr->prev = node;
        _size++;
    }
}


};

void test_iterator_increment();
void test_iterator_dereference();
void test_iterator_comparison();
void test_iterator_full_iteration();
void test_iterator_edge_cases();
void test_insert_and_size();
void test_find_and_insert_after();
void test_remove_front_and_back();
void test_remove_node();
void test_concatenate_and_clear();
void test_copy_constructor();
void test_copy_assignment();
void test_move_constructor();
void test_move_assignment();
void test_node_at_and_indexing();
void test_at_methods();
void test_insert_at_empty();
void test_insert_at_various_positions();
void test_remove_at_various_positions();
void test_remove_at_out_of_range();



