//Автор: Калашников А.Н.
#include <cassert>
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;


// 1) Тест: многократные вызовы begin() для одного дерева
void test_multiple_begin_calls() {
    cout << "test_multiple_begin_calls\n";

    // 1: пустое дерево — begin() несколько раз подряд
    {
        BinarySearchTree<int> bst;
        auto it1 = bst.begin();
        auto it2 = bst.begin();
        auto e1 = bst.end();
        auto e2 = bst.end();

        // Оба begin() создают итераторы с current == nullptr
        // => равны end()
        assert(!(it1 != e1));
        assert(!(it2 != e2));
        // Следовательно, begin() == end() и it1 == it2
        assert(!(it1 != it2));
    }

    // 2: дерево из одного узла — сравним begin() несколько раз
    {
        BinarySearchTree<int> bst;
        bst.insert(42);
        auto it1 = bst.begin();
        auto it2 = bst.begin();
        auto e = bst.end();

        // Оба begin() указывают на один и тот же корневой узел
        assert(!(it1 != it2));
        assert(*it1 == 42);
        assert(*it2 == 42);

        // После инкремента оба станут равны end()
        ++it1;
        ++it2;
        assert(!(it1 != e));
        assert(!(it2 != e));
    }

    // 3: простое дерево — три вызова begin()
    {
        BinarySearchTree<int> bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7}) bst.insert(v);

        auto it1 = bst.begin();
        auto it2 = bst.begin();
        auto it3 = bst.begin();
        auto e = bst.end();

        // Все три итератора начинают с минимального элемента (1)
        assert(*it1 == 1 && *it2 == 1 && *it3 == 1);
        assert(!(it1 != it2));
        assert(!(it2 != it3));

        // Двигаем один — должен измениться current
        ++it1;
        assert(it1 != it2);
        assert(*it1 == 2);
        assert(*it2 == 1);
    }

    // 4: дерево из 5 элементов — проверяем независимость итераторов
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i) bst.insert(i);

        auto it1 = bst.begin();
        auto it2 = bst.begin();
        auto e = bst.end();

        ++it1; // теперь it1 указывает на 2
        assert(it1 != it2);
        assert(*it1 == 2);
        assert(*it2 == 1);

        // Оба корректно дойдут до конца независимо
        int steps1 = 0, steps2 = 0;
        while (it1 != e) { ++it1; ++steps1; }
        while (it2 != e) { ++it2; ++steps2; }
        assert(steps1 == 4);
        assert(steps2 == 5);
    }

    // 5: begin() на разных BST
    {
        BinarySearchTree<int> bst1;
        BinarySearchTree<int> bst2;
        bst1.insert(10);
        bst2.insert(20);

        auto it1 = bst1.begin();
        auto it2 = bst2.begin();
        assert(it1 != it2);
        assert(*it1 == 10);
        assert(*it2 == 20);
    }

    cout << "  test_multiple_begin_calls: OK\n\n";
}


// 2) Тест: оператор ++
void test_iterator_increment() {
    cout << "test_iterator_increment\n";

    // 1: пустое дерево
    {
        BinarySearchTree<int> bst;
        auto it = bst.begin();
        auto e = bst.end();
        assert(!(it != e));
    }

    // 2: дерево из одного узла
    {
        BinarySearchTree<int> bst;
        bst.insert(10);
        auto it = bst.begin();
        auto e = bst.end();
        assert(*it == 10);
        ++it;
        assert(!(it != e));
    }

    // 3: простое дерево
    {
        BinarySearchTree<int> bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7})
            bst.insert(v);
        vector<int> expected = { 1,2,3,4,5,6,7 };
        vector<int> collected;
        for (auto it: bst)
            collected.push_back(it);
        assert(collected == expected);
    }

    // 4: все вправо
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i)
            bst.insert(i);
        int expected = 1;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            assert(*it == expected++);
        assert(expected == 6);
    }

    // 5: все влево
    {
        BinarySearchTree<int> bst;
        for (int i = 5; i >= 1; --i)
            bst.insert(i);
        int expected = 1;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            assert(*it == expected++);
        assert(expected == 6);
    }

    cout << "  test_iterator_increment: OK\n\n";
}


// 3) Тест: оператор *
void test_iterator_dereference() {
    cout << "test_iterator_dereference\n";

    // 1: пустое дерево
    {
        BinarySearchTree<int> bst;
        bool thrown = false;
        try {
            auto it = bst.begin();
            int x = *it;
        }
        catch (const out_of_range&) {
            thrown = true;
        }
        assert(thrown);
    }

    // 2: один узел
    {
        BinarySearchTree<int> bst;
        bst.insert(42);
        auto it = bst.begin();
        assert(*it == 42);
    }

    // 3: простое дерево
    {
        BinarySearchTree<int> bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7})
            bst.insert(v);
        auto it = bst.begin();
        assert(*it == 1);
        ++it;
        assert(*it == 2);
        ++it;
        assert(*it == 3);
    }

    // 4: вправо
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 9; ++i)
            bst.insert(i);
        auto it = bst.begin();
        for (int i = 1; i < 5; ++i)
            ++it;
        assert(*it == 5);
    }

    // 5: произвольный набор
    {
        BinarySearchTree<int> bst;
        vector<int> ins = { 10, 5, 15, 3, 7, 12, 18 };
        for (int v : ins)
            bst.insert(v);
        vector<int> expected = ins;
        sort(expected.begin(), expected.end());
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            collected.push_back(*it);
        assert(collected == expected);
    }

    cout << "  test_iterator_dereference: OK\n\n";
}


// 4) Тест: оператор !=
void test_iterator_comparison() {
    cout << "test_iterator_comparison\n";

    // 1: пустое дерево
    {
        BinarySearchTree<int> bst;
        auto b = bst.begin();
        auto e = bst.end();
        assert(!(b != e));
    }

    // 2: один элемент
    {
        BinarySearchTree<int> bst;
        bst.insert(7);
        auto b = bst.begin();
        auto e = bst.end();
        assert(b != e);
        ++b;
        assert(!(b != e));
    }

    // 3: копии итераторов
    {
        BinarySearchTree<int> bst;
        for (int v : {2, 1, 3})
            bst.insert(v);
        auto it1 = bst.begin();
        auto it2 = it1;
        assert(!(it1 != it2));
        ++it1;
        assert(it1 != it2);
    }

    // 4: end() дважды
    {
        BinarySearchTree<int> bst;
        bst.insert(100);
        auto e1 = bst.end();
        auto e2 = bst.end();
        assert(!(e1 != e2));
    }

    // 5: разные деревья
    {
        BinarySearchTree<int> a, b;
        a.insert(1);
        b.insert(2);
        auto itA = a.begin();
        auto itB = b.begin();
        assert(itA != itB);
    }

    cout << "  test_iterator_comparison: OK\n\n";
}


// 5) Тест: полный обход
void test_iterator_full_traversal() {
    cout << "test_iterator_full_traversal\n";

    // 1: пустое дерево
    {
        BinarySearchTree<int> bst;
        vector<int> result;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            result.push_back(*it);
        assert(result.empty());
    }

    // 2: один элемент
    {
        BinarySearchTree<int> bst;
        bst.insert(11);
        vector<int> result;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            result.push_back(*it);
        assert(result.size() == 1 && result[0] == 11);
    }

    // 3: простое дерево
    {
        BinarySearchTree<int> bst;
        vector<int> ins = { 4,2,6,1,3,5,7 };
        for (int v : ins)
            bst.insert(v);
        vector<int> expected = ins;
        sort(expected.begin(), expected.end());
        vector<int> result;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            result.push_back(*it);
        assert(result == expected);
    }

    // 4: вырожденное вправо
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 8; ++i)
            bst.insert(i);
        int expected = 1;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            assert(*it == expected++);
    }

    // 5: произвольное дерево
    {
        BinarySearchTree<int> bst;
        for (int v : {20, 10, 30, 5, 15, 25, 35})
            bst.insert(v);
        vector<int> expected = { 5,10,15,20,25,30,35 };
        vector<int> result;
        for (auto it = bst.begin(); it != bst.end(); ++it)
            result.push_back(*it);
        assert(result == expected);
    }

    cout << "  test_iterator_full_traversal: OK\n\n";
}


// 6) Тест: исключения
void test_iterator_exceptions() {
    cout << "test_iterator_exceptions\n";

    // 1: пустое дерево — при разыменовании бросается исключение
    {
        BinarySearchTree<int> bst;
        bool thrown = false;
        try {
            *bst.begin();
        }
        catch (const out_of_range&) {
            thrown = true;
        }
        assert(thrown);
    }

    // 2: разыменование end()
    {
        BinarySearchTree<int> bst;
        bst.insert(7);
        auto e = bst.end();
        bool thrown = false;
        try {
            *e;
        }
        catch (const out_of_range&) {
            thrown = true;
        }
        assert(thrown);
    }

    // 3: после прохода до конца
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 3; ++i)
            bst.insert(i);
        auto it = bst.begin();
        auto e = bst.end();
        while (it != e)
            ++it;
        bool thrown = false;
        try {
            *it;
        }
        catch (const out_of_range&) {
            thrown = true;
        }
        assert(thrown);
    }

    // 4: ++ за пределы end
    {
        BinarySearchTree<int> bst;
        for (int i : {2, 1, 3})
            bst.insert(i);
        auto it = bst.begin();
        auto e = bst.end();
        for (int i = 0; i < 10; ++i)
            ++it; // не должно быть исключений
        bool thrown = false;
        try {
            *it;
        }
        catch (const out_of_range&) {
            thrown = true;
        }
        assert(thrown);
    }

    //  5: убедимся, что копия итератора после ++ ведёт себя корректно
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i)
            bst.insert(i);
        auto it = bst.begin();
        ++it; // теперь указывает на второй
        auto it_copy = it; // копия
        assert(*it == *it_copy);
        ++it;
        assert(*it != *it_copy); 
    }


    cout << "  test_iterator_exceptions: OK\n\n";
}


/**
 *  Тестирование метода insert()
 */
void test_insert() {
    // 1) Пустое дерево -> вставка
    BinarySearchTree<int> bst;
    assert(bst.empty());
    bst.insert(10);
    assert(!bst.empty());
    assert(bst.get_root()->value == 10);

    // 2) Вставка меньшего и большего значения
    bst.insert(5);
    bst.insert(15);
    assert(bst.get_root()->left->value == 5);
    assert(bst.get_root()->right->value == 15);

    // 3) Попытка вставки дубликата
    bst.insert(10);
    assert(bst.size() == 3);

    // 4) Вырожденное дерево (вставляем по убыванию)
    BinarySearchTree<int> bst2;
    bst2.insert(10);
    bst2.insert(9);
    bst2.insert(8);
    bst2.insert(7);
    assert(bst2.height() == 3); 

    // 5) Более сложное дерево
    BinarySearchTree<int> bst3;
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        bst3.insert(v);
    assert(bst3.size() == 7);
    assert(bst3.get_root()->left->right->value == 40);

    cout << "test_insert пройден!\n";
}

/**
 *  Тестирование метода remove()
 */
void test_remove() {
    // 1) Удаление из пустого дерева
    BinarySearchTree<int> bst;
    bst.remove(10); // ничего не должно произойти
    assert(bst.size() == 0);

    // 2) Удаление из дерева из одного узла
    bst.insert(5);
    bst.remove(5);
    assert(bst.empty());

    // 3) Удаление листа
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.remove(5);
    assert(bst.size() == 2);

    // 4) Удаление узла с одним потомком
    bst.insert(12);
    bst.remove(15);
    assert(bst.size() == 2);

    // 5) Удаление узла с двумя потомками (удаление корня вырожденного дерева)
    bst.insert(20);
    bst.insert(25);
    bst.remove(10); // корень с двумя детьми
    assert(bst.size() == 3);

    cout << "test_remove пройден!\n";
}

/**
 *  Тестирование метода successor()
 */
void test_successor() {
    BinarySearchTree<int> bst;

    // 1) Пустое дерево
    assert(bst.successor(10) == nullptr);

    // 2) Дерево с одним узлом
    bst.insert(5);
    assert(bst.successor(5) == nullptr);

    // 3) Вырожденное дерево
    bst.insert(10);
    bst.insert(15);
    assert(bst.successor(10)->value == 15);
    bst.clear();

    // 4) Совершенное дерево
    bst.insert(25);
    bst.insert(20);
    bst.insert(30);
    TreeNode<int>* succ = bst.successor(20);
    assert(succ && succ->value == 25);

    // 5) Successor максимального элемента = nullptr
    succ = bst.successor(30);
    assert(succ == nullptr);

    cout << "test_successor пройден!\n";
}

/**
 *  Тестирование метода search()
 */
void test_search() {
    BinarySearchTree<int> bst;

    // 1) Пустое дерево
    assert(bst.search(10) == nullptr);

    // 2) Один узел
    bst.insert(5);
    TreeNode<int>* found = bst.search(5);
    assert(found && found->value == 5);

    // 3) Вырожденное дерево
    bst.insert(4);
    bst.insert(3);
    bst.insert(2);
    found = bst.search(2);
    assert(found && found->value == 2);

    // 4) Несуществующее значение
    found = bst.search(100);
    assert(found == nullptr);

    // 5) Совершенное дерево
    BinarySearchTree<int> bst2;
    for (int v : {10, 5, 15, 3, 7, 12, 18})
        bst2.insert(v);
    found = bst2.search(7);
    assert(found && found->value == 7);

    cout << "test_search пройден!\n";
}


/**
 *  Тестирование метода size()
 */
void test_size() {
    BinarySearchTree<int> bst;
    // Пустое дерево
    assert(bst.size() == 0);

    // Дерево из одного узла
    bst.insert(1);
    assert(bst.size() == 1);

    bst.insert(2);
    bst.insert(3);
    // Вырожденное дерево
    assert(bst.size() == 3);

    cout << "test_size пройден!\n";
}

/**
 *  Тестирование метода height()
 */
void test_height() {
    BinarySearchTree<int> bst;
    // Пустое дерево
    assert(bst.height() == -1);

    // Дерево из одного узла
    bst.insert(10);
    assert(bst.height() == 0);

    // создаём вырожденное дерево (цепочка вправо)
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    assert(bst.height() == 3);

    cout << "test_height пройден!\n";
}

/**
 *  Тестирование метода clear() и empty()
 */
void test_clear_empty() {
    // Пустое дерево
    BinarySearchTree<int> bst;
    assert(bst.empty());

    // Вырожденное дерево
    bst.insert(1);
    bst.insert(2);
    bst.insert(3);
    assert(!bst.empty());

    // Тест метода clear
    bst.clear();
    // Снова пустое дерево после вызова метода очистки clear
    assert(bst.empty());
    assert(bst.size() == 0);

    cout << "test_clear_empty пройден!\n";
}


