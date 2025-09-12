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

	
};