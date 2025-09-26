//Автор: Калашников А.Н.
#include <iostream>
#include "TreeNode.h"
#include "TreeNodeFunctions.h"
#include "BinarySearchTree.h"
using namespace std;

int main()
{	
	setlocale(LC_ALL, "Russian");

	// корень дерева 
	//TreeNode<int> *root = new TreeNode<int>(10);
	//root->left = new TreeNode<int>(8); // выделяем память динамически под 5 узлов
	//root->right = new TreeNode<int>(12);
	//root->right->left = new TreeNode<int>(10);
	//root->right->right = new TreeNode<int>(14);
	//TreeNode<int>* test = new TreeNode<int>(2);
	//TreeNode<int>* copy = root->right;
	//test = root->right;
	//print_tree(test);
	//print_tree(copy);
	//print_tree(root, 10);
	//preorder_print<int>(root);
	//// Просматриваем содержимое двух узлов дерева в качестве примера 
	//cout << ("Корень дерева = ") << root->value;
	//cout << endl; 
	//cout << ("Корень дерева -> направо -> направо =  ") << root->right->right->value;
	//cout << endl;
	//cout << count_nodes<int>(root);
	//cout << endl;
	//cout << depth(root);
	//delete_tree(root);

	test_preorder();
	test_inorder();
	test_postorder();
	test_preorder_iterative();
	test_bfs();
	test_preorder_apply();
	test_inorder_apply();
	test_postorder_apply();
	test_search();
	test_search_any();
	test_count_nodes();
	test_depth();
	test_print_tree();
	test_delete_tree();
	test_insert();
	test_size();
	test_height();
	test_remove();
	test_clear_empty();
	test_successor();
	test_search();
	/* 
	Дерево является строгим, т.к. у каждого узла либо 0, либо 2 потомка.

	Дерево не является законченным, т.к. на последнем уровне листья собраны справа, а не слева.

	Дерево не является совершенным, т.к. листья расположены на разных уровнях
	*/
}

