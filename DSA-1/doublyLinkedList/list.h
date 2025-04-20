// �����: ���������� �.�.
#pragma once
#include <stdexcept>
#include <cstddef>
using namespace std;

/// ��������� ����� ����������� ������
template <typename T>
class DoublyLinkedList {
private:
    /// ���������� ��������� ���� ������
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
    int _size; /// ���������� ��������� 
    Node* head;  /// ��������� �� ������ ������
    Node* tail;  /// ��������� �� ����� ������

public:

    /// �����������: ������ ������ ������
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        _size = 0;
    }

    /// ����������: ����������� ��� ����
    ~DoublyLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        _size = 0;
    }

    /// ����������� �����������, other - ���������� ������
    DoublyLinkedList(const DoublyLinkedList& other)  {
        Node* curr = other.head;
        while (curr) {
            insert_back(curr->data);
            curr = curr->next;
        }
    }

    /// �������� ������������ ������������, other - ���������� ������, ���������� ������ �� ������� �������� ������
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

    /// ����������� �����������, other - rvalue ������ �� ������������ ������
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), _size(other._size) {
        other.head = nullptr;
        other.tail = nullptr;
        other._size = 0;
    }

    /// �������� ������������ ������������, other - rvalue ������ �� ������������ ������, ���������� ������ �� ������� �������� ������
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

    /// ����� �������� �� ��������, ���������� ��������� �� ������ ��������� ���� ��� nullptr
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

    /// �������� � ������ ������ �������� value (O(1))
    void insert_front(const T& value) {
        Node* node = new Node(value);
        node->next = head;
        if (head)
            head->prev = node;
        head = node;
        if (!tail) // ���������� ��� ������ ������� ������� �������� � ������ ������
            tail = node;
        _size++;
    }

    /// �������� � ����� ������ �������� value (O(1))
    void insert_back(const T& value) {
        Node* node = new Node(value);
        node->prev = tail;
        if (tail)
            tail->next = node;
        tail = node;
        if (!head) // ���������� ��� ������ ������� ������� �������� � ������ ������
            head = node;
        _size++;
    }

    /// �������� ������� �������� (O(1))
    void remove_front() {
        if (!head)
            throw underflow_error("������ ����");
        Node* to_delete = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete to_delete;
        _size--;
    }

    ///  �������� ���������� �������� (O(1))
    void remove_back() {
        if (!tail) throw underflow_error("������ ����");
        Node* to_delete = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete to_delete;
        _size--;
    }

    /**
     * �������� ����������� ���� (O(n) ��� ������)
     * @param node ���� ��� ��������
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
     * ������������ ������� ������ � ����� �������� ������ (O(n))
     * @param other ������ ������
     * ����� ������������ other ���������� ������
     */
    void concatenate(DoublyLinkedList& other) {
        Node* curr = other.head;
        while (curr) {
            insert_back(curr->data);
            curr = curr->next;
        }
        // ������� other 
        other.clear();
    }

    ///  �������� ������ ������, O(1)
    size_t size() const {
        return _size;
    }

    ///  ������ ������� ������, ����������� ��� ����
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
       * ����� ���� �� �������, ���������� ��������� �� ���� ��� nullptr
       * @param index ����� �������� � ������ (0..size()-1)
       * @return Node* ��������� �� ���� ��� nullptr, ���� ������ �������
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
     * ������ � �������� �� �������, ���������� ������ �� ������
     * @param index ����� ��������
     * @throw out_of_range ���� ������ >= size()
     */
    T& at(size_t index) {
        Node* node = node_at(index);
        if (!node)
            throw out_of_range("Index out of range");
        return node->data;
    }

    /**
     * ����������� ������ � �������� �� �������
     * @param index ����� ��������
     * @throw out_of_range ���� ������ >= size()
     */const T& at(size_t index) const {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }

     /**
      *  �������� ������� �� ������� � ������� []
      * @param index ������� ��������
      * @return ������ �� �������
      */
     T& operator[](size_t index) {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }

     /**
      *  ����������� �������� ������� �� ������� � ������� []
      * @param index ������� ��������
      * @return ����������� ������ �� �������
      */
     const T& operator[](size_t index) const {
         Node* node = node_at(index);
         if (!node)
             throw out_of_range("Index out of range");
         return node->data;
     }


/**
 *  �������� �������� �� ������� 
 * @param index ������ ���������� ��������
 * @throw out_of_range ���� ������ >= size()
 */
void remove_at(size_t index) {
    if (index >= _size)
        throw out_of_range("Index out of range");
    Node* node = node_at(index);
    remove(node);
}

/**
 *  ������� �������� �� ������� 
 * @param index ������� ��� ������� (0 <= index <= size())
 * @param value �������� ��� �������
 * @throw out_of_range ���� ������ > size()
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
        Node* curr = node_at(index); // ������� ������� �� ������� index
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



