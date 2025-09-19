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

    // Конструктор копирования (глубокое копирование)
    TreeNode(const TreeNode& other)
        : value(other.value),
        left(other.left ? new TreeNode(*other.left) : nullptr),
        right(other.right ? new TreeNode(*other.right) : nullptr)
    {
    }

    //  Оператор присваивания (глубокое копирование)
    TreeNode& operator=(const TreeNode& other) {
        if (this == &other) return *this; // защита от самоприсваивания

        // сначала удаляем старые поддеревья
        delete left;
        delete right;

        // копируем значение
        value = other.value;

        // копируем поддеревья
        left = other.left ? new TreeNode(*other.left) : nullptr;
        right = other.right ? new TreeNode(*other.right) : nullptr;

        return *this;
    }
	
};