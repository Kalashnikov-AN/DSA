#include "stack.h"
#include <cassert>
#include <iostream>
using namespace std;
// Автор: Калашников А.Н.

/// Тесты для класса стека
void test()
{
	// Вызываем конструктор по умолчанию 
	stack<int> stack1; 
	stack<int> stackEmpty;

	// проверка метода получения размера
	assert(stack1.size() == 0); 
	assert(stackEmpty.size() == 0); 

	// проверка метода isEmpty
	assert(stack1.isEmpty() == true); 
	assert(stackEmpty.isEmpty() == true);

	// проверка добавления элемента
	stack1.push(0); 
	assert(stack1.size() == 1); // размер увеличился
	assert(stack1.isEmpty() == false);
	// проверка получения элемента на вершине
	assert(stack1.peek() == 0);  

	// проверка добавления ещё одного элемента
	stack1.push(1); 
	assert(stack1.size() == 2);  // размер увеличился 
	assert(stack1.isEmpty() == false);
	// проверка получения элемента на вершине
	assert(stack1.peek() == 1); 

	// Конструктор копирования
	stack<int> stack2(stack1);
	assert(stack2.size() == stack1.size());
	assert(stack2.peek() == stack1.peek());

	// Оператор присваивания копированием
	stack<int> stack3;
	stack3 = stack1;
	assert(stack3.size() == stack1.size());
	assert(stack3.peek() == stack1.peek());

	// Конструктор перемещения
	stack<int> stack4(move(stack3));
	assert(stack4.size() == 2); // stack3 имел 2 элемента
	assert(stack3.size() == 0); // После перемещения исходный стек должен быть пуст

	// Оператор присваивания перемещением
	stack<int> stack5;
	stack5 = move(stack4);
	assert(stack5.size() == 2);
	assert(stack4.size() == 0);

	// проверка удаления элемента
	stack1.pop(); 
	assert(stack1.size() == 1); // размер уменьшился
	assert(stack1.isEmpty() == false); 
	assert(stack1.peek() == 0); 

	// проверка удаления ещё одного элемента и возврата значения удаленного элемента
	int a = stack1.pop(); 
	assert(a == 0);
	assert(stack1.size() == 0); // размер уменьшился
	assert(stack1.isEmpty() == true); 

	// Тест на исключение при pop() пустого стека
	try {
		assert(stackEmpty.isEmpty() == true); // стек действительно пуст
		stackEmpty.pop(); // удаление элемента из пустого стека
		assert(false); // если попали сюда, тест провален
	}
	catch (const underflow_error&) {
	}

	// очистка пустого стека 
	assert(stackEmpty.isEmpty() == true);
	stackEmpty.clear(); 
	assert(stackEmpty.size() == 0); // размер = 0
	assert(stackEmpty.isEmpty() == true); // стек пуст

	// проверка clear на непустом стеке
	stack<int> stack6;
	stack6.push(10);
	stack6.push(20);
	assert(stack6.size() == 2);
	stack6.clear();
	assert(stack6.size() == 0);
	assert(stack6.isEmpty() == true);

	// заполнение стека большим количеством элементов, очистка стека
	stack<int> stack7;
	for (int i = 0; i < 1'000'000; ++i) {
		stack7.push(i); // заполняем стек миллионом элементов
	}
	assert(stack7.size() == 1'000'000);
	assert(stack7.peek() == 999'999);
	stack7.clear(); // очистка стека
	assert(stack7.size() == 0);
	assert(stack7.isEmpty() == true);

	cout << "Все тесты успешно пройдены\n";
}