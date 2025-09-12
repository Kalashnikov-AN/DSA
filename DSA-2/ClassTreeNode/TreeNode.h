//Автор: Калашников А.Н.
#pragma once
#include <iostream>

// Шаблонный класс узла бинарного дерева
// Храним данные в поле value, указатели на левого и правого потомка.
template<typename T>
class TreeNode {
public:
	T value; // данные в узле
	TreeNode<T>* left; // указатель на левого потомка 
	TreeNode<T>* right; // указатель на правого потомка 

	// Конструктор: инициализирует значение и обнуляет указатели
	TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}

	
};