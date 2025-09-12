//Автор: Калашников А.Н.
#include <iostream>
#include "TreeNode.h"
using namespace std;

int main()
{	
	setlocale(LC_ALL, "Russian");

	// корень дерева 
	TreeNode<int> *root = new TreeNode<int>(10);
	root->left = new TreeNode<int>(8); // выделяем память динамически под 5 узлов
	root->right = new TreeNode<int>(12);
	root->right->left = new TreeNode<int>(10);
	root->right->right = new TreeNode<int>(14);
	
	// Просматриваем содержимое двух узлов дерева в качестве примера 
	cout << ("Корень дерева = ") << root->value;
	cout << endl; 
	cout << ("Корень дерева -> направо -> направо =  ") << root->right->right->value;
	cout << endl;
	int i = 0;

	// Удаляем все узлы дерева
	while (root) {
		if (root->left) {
			TreeNode<int>* tmp = root->left;   // сохраняем ссылку на левого потомка
			root->left = tmp->right;           // переносим правую ветку наверх
			tmp->right = root;                 // делаем временный цикл
			root = tmp;                        // спускаемся вниз
		}
		else {
			TreeNode<int>* tmp = root;         // текущий узел
			root = root->right;                // переходим направо
			cout << tmp->value << endl;
			delete tmp;                        // удаляем узел
			
			i++;
			cout << i << endl;
		}
	}

	/* 
	Дерево является строгим, т.к. у каждого узла либо 0, либо 2 потомка.

	Дерево не является законченным, т.к. на последнем уровне листья собраны справа, а не слева.

	Дерево не является совершенным, т.к. листья расположены на разных уровнях
	*/
}

