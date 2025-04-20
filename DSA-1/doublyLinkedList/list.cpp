// �����: ���������� �.�.
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "list.h"
using namespace std;

template <typename T>
using List = DoublyLinkedList<T>;

/// ���� ������� ��������� � ������/����� � �������� �������.
void test_insert_and_size() {
    List<int> lst;
    assert(lst.size() == 0);

    // ������� � ������ � �����
    lst.insert_front(10);
    assert(lst[0] == 10);
    assert(lst.size() == 1);
    assert(lst.find(10) != nullptr && lst.find(10)->data == 10);

    lst.insert_back(20);
    assert(lst.size() == 2);
    // ��������� �������: head->10, tail->20
    assert(lst.find(10)->next->data == 20);
    assert(lst.find(20)->prev->data == 10);
}

/// ���� �������� ��������� � ������ � ����� ������
void test_remove_front_and_back() {
    List<int> lst;
    lst.insert_back(1);
    lst.insert_back(2);
    lst.insert_back(3);
    assert(lst.size() == 3);

    // �������� � ������
    lst.remove_front(); // ����� 1
    assert(lst.size() == 2);
    assert(lst.find(1) == nullptr);
    assert(lst.find(2)->prev == nullptr);

    // �������� � �����
    lst.remove_back(); // ����� 3
    assert(lst.size() == 1);
    assert(lst.find(3) == nullptr);
    assert(lst.find(2)->next == nullptr);

    // �������� �� ������� � underflow_error
    lst.remove_front(); // ������ �����
    bool underflow = false;
    try {
        lst.remove_front();
    }
    catch (const underflow_error&) {
        underflow = true;
    }
    assert(underflow);
}

/// ���� �������� ����������� ����
void test_remove_node() {
    DoublyLinkedList<char> lst;
    lst.insert_back('a');
    lst.insert_back('b');
    lst.insert_back('c');
    assert(lst.size() == 3);

    // �������� ����������� ���� 'b'
    auto nodeB = lst.find('b');
    lst.remove(nodeB);
    assert(lst.size() == 2);
    assert(lst.find('b') == nullptr);
    // ��������� ����� a <-> c
    auto nodeA = lst.find('a');
    auto nodeC = lst.find('c');
    assert(nodeA->next == nodeC);
    assert(nodeC->prev == nodeA);
}

/// ���� ������������ ���� ������� � �������
void test_concatenate_and_clear() {
    List<int> a, b;
    for (int i = 1; i <= 3; ++i) a.insert_back(i);
    for (int i = 4; i <= 6; ++i) b.insert_back(i);
    assert(a.size() == 3 && b.size() == 3);

    // ������������ b � a
    a.concatenate(b);
    assert(a.size() == 6);
    for (int i = 1; i <= 6; ++i) {
        assert(a.find(i) != nullptr);
    }
    // b ������ ���� ������
    assert(b.size() == 0);

    // ������� a
    a.clear();
    assert(a.size() == 0);
    assert(a.find(1) == nullptr);
}

/// ���� ������������ �����������
void test_copy_constructor() {
    List<int> a;
    for (int i = 1; i <= 5; ++i) a.insert_back(i);
    List<int> b(a);
    // ���������, ��� b �������� �� �� ������������������
    assert(b.size() == a.size());
    for (int i = 1; i <= 5; ++i)
        assert(b.find(i) != nullptr && b.find(i)->data == i);
    // ��������� a �� ������ b (�������� �����������)
    a.remove_front();  // ������� 1
    assert(a.size() == 4);
    assert(b.size() == 5);
    assert(b.find(1) != nullptr);
}

/// ���� ��������� ������������ ������������
void test_copy_assignment() {
    List<string> a;
    a.insert_back("one");
    a.insert_back("two");
    List<string> b;
    b = a;
    assert(b.size() == a.size());
    assert(b.find("one") && b.find("two"));
    a.insert_back("three");
    assert(a.size() == 3);
    assert(b.size() == 2);
}

/// ���� ������������ �����������
void test_move_constructor() {
    List<int> a;
    for (int i = 42; i <= 45; ++i) a.insert_back(i);
    List<int> b(move(a));
    // b ������� ������
    assert(b.size() == 4);
    for (int i = 42; i <= 45; ++i)
        assert(b.find(i));
    // a ������ ���� ����
    assert(a.size() == 0);
}

/// ���� ��������� ������������ ������������
void test_move_assignment() {
    List<char> a;
    a.insert_back('x');
    a.insert_back('y');
    List<char> b;
    b.insert_back('z');
    // ���������� a � rvalue
    b = move(a); 
    // b ������� x,y
    assert(b.size() == 2);
    assert(b.find('x') && b.find('y'));
    // a ����
    assert(a.size() == 0);
}

/// ����� ��� ������� node_at � []
void test_node_at_and_indexing() {
    DoublyLinkedList<int> lst;
    // �������� ������ ���������� 5, 10, 15, 20
    lst.insert_back(5);
    lst.insert_back(10);
    lst.insert_back(15);
    lst.insert_back(20);

    // ������
    assert(lst.size() == 4);

    // node_at: ���������� �������
    assert(lst.node_at(0) && lst.node_at(0)->data == 5);
    assert(lst.node_at(1) && lst.node_at(1)->data == 10);
    assert(lst.node_at(2) && lst.node_at(2)->data == 15);
    assert(lst.node_at(3) && lst.node_at(3)->data == 20);

    // node_at: �������������� �������
    assert(lst.node_at(4) == nullptr);
    assert(lst.node_at(100) == nullptr);

    // operator[] ������ � ���������
    assert(lst[0] == 5);
    assert(lst[3] == 20);
    lst[2] = 99;
    assert(lst[2] == 99);

    // operator[] ����� �� ������� => ����������
    bool caught = false;
    try {
        int x = lst[4];
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);

    // const ������
    const DoublyLinkedList<int>& clst = lst;
    assert(clst[0] == 5);
    assert(clst[2] == 99);
    caught = false;
    try {
        int y = clst[5];
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);

}

/// ���� ��� ������ at
void test_at_methods() {
    DoublyLinkedList<string> lst;
    lst.insert_back("a");
    lst.insert_back("b");
    lst.insert_back("c");

    // at ������
    assert(lst.at(0) == "a");
    assert(lst.at(1) == "b");
    assert(lst.at(2) == "c");

    // at ������
    lst.at(1) = "beta";
    assert(lst.at(1) == "beta");

    // at ����� �� �������
    bool caught = false;
    try {
        string s = lst.at(3);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);

    // ����������� ������
    const DoublyLinkedList<string>& clst = lst;
    assert(clst.at(0) == "a");
    assert(clst.at(1) == "beta");
    caught = false;
    try {
        string t = clst.at(5);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}

/// ����: ������� �� ������� � ������ ������
void test_insert_at_empty() {
    DoublyLinkedList<int> lst;
    // ������� �� ������� 0 � ������ ������ ������������ insert_front
    lst.insert_at(0, 42);
    assert(lst.size() == 1);
    assert(lst[0] == 42);

    // ������� �������� �� ������� > size ������ ������� ����������
    bool caught = false;
    try {
        lst.insert_at(2, 100);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}

/// ����: ������� � ������, �������� � �����
void test_insert_at_various_positions() {
    DoublyLinkedList<string> lst;
    lst.insert_back("A");
    lst.insert_back("C");

    // ������� � ������
    lst.insert_at(0, "X"); // X, A, C
    assert(lst.size() == 3);
    assert(lst[0] == "X");
    assert(lst[1] == "A");

    // ������� � ��������
    lst.insert_at(2, "Y"); // X, A, Y, C
    assert(lst.size() == 4);
    assert(lst[2] == "Y");
    assert(lst[3] == "C");

    // ������� � ����� (index == size)
    lst.insert_at(lst.size(), "Z"); // X, A, Y, C, Z
    assert(lst.size() == 5);
    assert(lst[4] == "Z");

}

/// ����: �������� �� ������� � ������ ��������
void test_remove_at_various_positions() {
    DoublyLinkedList<char> lst;
    lst.insert_back('a');
    lst.insert_back('b');
    lst.insert_back('c');
    lst.insert_back('d'); // a, b, c, d

    // �������� �������
    lst.remove_at(0); // b, c, d
    assert(lst.size() == 3);
    assert(lst[0] == 'b');

    // �������� ����������
    lst.remove_at(lst.size() - 1); // b, c
    assert(lst.size() == 2);
    assert(lst[1] == 'c');

    // �������� � ��������
    lst.insert_back('e'); // b, c, e
    lst.insert_back('f'); // b, c, e, f
    lst.remove_at(2);     // b, c, f
    assert(lst.size() == 3);
    assert(lst[2] == 'f');
}

/// ����: �������� �� ��������� �������
void test_remove_at_out_of_range() {
    DoublyLinkedList<double> lst;
    lst.insert_back(1.1);
    bool caught = false;
    try {
        lst.remove_at(1);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}




