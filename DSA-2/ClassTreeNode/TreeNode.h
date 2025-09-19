//�����: ���������� �.�.
#pragma once
#include <iostream>

// ��������� ����� ���� ��������� ������
// ������ ������ � ���� value, ��������� �� ������ � ������� �������.
template<typename T>
class TreeNode {
public:
	T value; // ������ � ����
	TreeNode<T>* left; // ��������� �� ������ ������� 
	TreeNode<T>* right; // ��������� �� ������� ������� 

	// �����������: �������������� �������� � �������� ���������
	TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}

    // ����������� ����������� (�������� �����������)
    TreeNode(const TreeNode& other)
        : value(other.value),
        left(other.left ? new TreeNode(*other.left) : nullptr),
        right(other.right ? new TreeNode(*other.right) : nullptr)
    {
    }

    //  �������� ������������ (�������� �����������)
    TreeNode& operator=(const TreeNode& other) {
        if (this == &other) return *this; // ������ �� ����������������

        // ������� ������� ������ ����������
        delete left;
        delete right;

        // �������� ��������
        value = other.value;

        // �������� ����������
        left = other.left ? new TreeNode(*other.left) : nullptr;
        right = other.right ? new TreeNode(*other.right) : nullptr;

        return *this;
    }
	
};