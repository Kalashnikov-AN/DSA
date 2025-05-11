#include "stack.h"
#include <cassert>
#include <iostream>
using namespace std;
// �����: ���������� �.�.

/// ����� ��� ������ �����
void test()
{
	// �������� ����������� �� ��������� 
	stack<int> stack1; 
	stack<int> stackEmpty;

	// �������� ������ ��������� �������
	assert(stack1.size() == 0); 
	assert(stackEmpty.size() == 0); 

	// �������� ������ isEmpty
	assert(stack1.isEmpty() == true); 
	assert(stackEmpty.isEmpty() == true);

	// �������� ���������� ��������
	stack1.push(0); 
	assert(stack1.size() == 1); // ������ ����������
	assert(stack1.isEmpty() == false);
	// �������� ��������� �������� �� �������
	assert(stack1.peek() == 0);  

	// �������� ���������� ��� ������ ��������
	stack1.push(1); 
	assert(stack1.size() == 2);  // ������ ���������� 
	assert(stack1.isEmpty() == false);
	// �������� ��������� �������� �� �������
	assert(stack1.peek() == 1); 

	// ����������� �����������
	stack<int> stack2(stack1);
	assert(stack2.size() == stack1.size());
	assert(stack2.peek() == stack1.peek());

	// �������� ������������ ������������
	stack<int> stack3;
	stack3 = stack1;
	assert(stack3.size() == stack1.size());
	assert(stack3.peek() == stack1.peek());

	// ����������� �����������
	stack<int> stack4(move(stack3));
	assert(stack4.size() == 2); // stack3 ���� 2 ��������
	assert(stack3.size() == 0); // ����� ����������� �������� ���� ������ ���� ����

	// �������� ������������ ������������
	stack<int> stack5;
	stack5 = move(stack4);
	assert(stack5.size() == 2);
	assert(stack4.size() == 0);

	// �������� �������� ��������
	stack1.pop(); 
	assert(stack1.size() == 1); // ������ ����������
	assert(stack1.isEmpty() == false); 
	assert(stack1.peek() == 0); 

	// �������� �������� ��� ������ �������� � �������� �������� ���������� ��������
	int a = stack1.pop(); 
	assert(a == 0);
	assert(stack1.size() == 0); // ������ ����������
	assert(stack1.isEmpty() == true); 

	// ���� �� ���������� ��� pop() ������� �����
	try {
		assert(stackEmpty.isEmpty() == true); // ���� ������������� ����
		stackEmpty.pop(); // �������� �������� �� ������� �����
		assert(false); // ���� ������ ����, ���� ��������
	}
	catch (const underflow_error&) {
	}

	// ������� ������� ����� 
	assert(stackEmpty.isEmpty() == true);
	stackEmpty.clear(); 
	assert(stackEmpty.size() == 0); // ������ = 0
	assert(stackEmpty.isEmpty() == true); // ���� ����

	// �������� clear �� �������� �����
	stack<int> stack6;
	stack6.push(10);
	stack6.push(20);
	assert(stack6.size() == 2);
	stack6.clear();
	assert(stack6.size() == 0);
	assert(stack6.isEmpty() == true);

	// ���������� ����� ������� ����������� ���������, ������� �����
	stack<int> stack7;
	for (int i = 0; i < 1'000'000; ++i) {
		stack7.push(i); // ��������� ���� ��������� ���������
	}
	assert(stack7.size() == 1'000'000);
	assert(stack7.peek() == 999'999);
	stack7.clear(); // ������� �����
	assert(stack7.size() == 0);
	assert(stack7.isEmpty() == true);

	cout << "��� ����� ������� ��������\n";
}