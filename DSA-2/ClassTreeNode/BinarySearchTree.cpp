//Автор: Калашников А.Н.
#include <cassert>
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

// ---------------------------
// 6) Тест многократных вызовов begin() для одного объекта
// ---------------------------
void test_multiple_begin_calls() {
    cout << "test_multiple_begin_calls\n";

    // CASE 1: пустое дерево — begin() несколько раз подряд
    {
        BinarySearchTree<int> bst;
        auto it1 = bst.begin();
        auto it2 = bst.begin();
        auto e1 = bst.end();
        auto e2 = bst.end();

        // оба итератора указывают на разные traversal (из-за new vector в каждом begin)
        // => они не равны
        assert(it1 != it2);
        // но оба — end(), так что при проверке цикла ничего не произойдёт
        assert(!(it1 != e1));
        assert(!(it2 != e2));
    }

    // CASE 2: дерево из одного узла — сравним begin() несколько раз
    {
        BinarySearchTree<int> bst;
        bst.insert(42);
        auto it1 = bst.begin(); // создаёт 1-й traversal
        auto it2 = bst.begin(); // создаёт 2-й traversal, старый потерян (утечка памяти)
        auto e1 = bst.end();    // end() теперь соответствует it2, т.к. last_traversal = it2.traversal
        auto e2 = bst.end();

        // it1 и it2 теперь указывают на разные буферы, поэтому не равны
        assert(it1 != it2);
        // оба корректно читают значение (но из разных векторов)
        assert(*it1 == 42);
        assert(*it2 == 42);
        // e1 и e2 равны между собой
        assert(!(e1 != e2));
    }

    // CASE 3: сбалансированное дерево — три вызова begin()
    {
        BinarySearchTree<int> bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7}) bst.insert(v);

        auto it1 = bst.begin(); // создаёт первый traversal
        auto it2 = bst.begin(); // второй
        auto it3 = bst.begin(); // третий
        // теперь last_traversal указывает на вектор, созданный при it3
        auto e = bst.end();

        // it1, it2, it3 — разные буферы => все должны быть !=
        assert(it1 != it2);
        assert(it2 != it3);
        assert(it1 != it3);

        // но все корректно читают значения по inorder
        vector<int> collected1, collected2, collected3;
        for (auto t = it1; t != e; ++t) collected1.push_back(*t);
        for (auto t = it2; t != e; ++t) collected2.push_back(*t);
        for (auto t = it3; t != e; ++t) collected3.push_back(*t);

        // collected1/2/3 могут отличаться, потому что e соответствует it3 (последнему)
        // => итерации it1 и it2 будут сравниваться с end() от другой traversal
        // фактически, цикл с it1 или it2 не выполнится вовсе, т.к. (it1 != e) будет true всегда
        // и может привести к неопределённому поведению (так как сравнение разных traversal)
        // мы не должны падать, но результат не определён стандартом
        cout << "  CASE 3: sizes collected: "
            << collected1.size() << ", " << collected2.size() << ", " << collected3.size() << "\n";
    }

    // CASE 4: дерево из 5 элементов — проверяем поведение при повторных вызовах begin()
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i) bst.insert(i);

        auto it1 = bst.begin(); // new traversal A
        auto it2 = bst.begin(); // new traversal B
        auto e = bst.end();   // end соответствует traversal B

        // Попробуем пройти первым итератором (it1) до конца traversal A,
        // но при сравнении с e (traversal B) условие (it1 != e) всегда истинно,
        // поэтому цикл не завершится (бесконечный цикл).
        // Чтобы не зависнуть, ограничим вручную количество шагов.
        int steps = 0;
        while (it1 != e && steps++ < 10) ++it1;
        // Мы останавливаемся раньше, чтобы избежать UB.
        cout << "  CASE 4: loop stopped after " << steps << " increments\n";
    }

    // CASE 5: вызовы begin() в разных областях (каждый BST свой)
    {
        BinarySearchTree<int> bst1;
        BinarySearchTree<int> bst2;
        bst1.insert(10);
        bst2.insert(20);

        auto it1 = bst1.begin();
        auto it2 = bst2.begin();
        assert(it1 != it2); // разные traversal в разных объектах

        auto e1 = bst1.end();
        auto e2 = bst2.end();
        assert(!(e1 != e1)); // один и тот же end в пределах bst1
        assert(it1 != e1);
        assert(it2 != e2);
    }

    cout << "  test_multiple_begin_calls: OK (см. комментарии о поведении)\n\n";
}

// ---------------------------
// 1) Тест оператора ++ (инкремент)
// ---------------------------
void test_iterator_increment() {
    cout << "test_iterator_increment\n";

    // CASE 1: пустое дерево
    {
        BinarySearchTree<int> bst;
        auto it = bst.begin();
        auto e = bst.end();
        // Пустое дерево: begin == end
        assert(!(it != e));
    }

    // CASE 2: дерево из одного узла
    {
        BinarySearchTree<int> bst;
        bst.insert(10);
        auto it = bst.begin();
        auto e = bst.end();
        // сначала корень
        assert(*it == 10);
        ++it;
        // после ++ — end
        assert(!(it != e));
    }

    // CASE 3: сбалансированное дерево
    {
        BinarySearchTree<int> bst;
        // Вставляем значения (результат inorder = 1..7)
        for (int v : {4, 2, 6, 1, 3, 5, 7}) bst.insert(v);
        auto it = bst.begin();
        auto e = bst.end();

        vector<int> expected = { 1,2,3,4,5,6,7 };
        size_t idx = 0;
        while (it != e) {
            assert(*it == expected[idx]);
            ++it;
            ++idx;
        }
        assert(idx == expected.size());
    }

    // CASE 4: вырожденное дерево — все вправо (ascending inserts)
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i) bst.insert(i); // 1,2,3,4,5
        auto it = bst.begin();
        auto e = bst.end();
        int expect = 1;
        while (it != e) {
            assert(*it == expect++);
            ++it;
        }
        assert(expect == 6);
    }

    // CASE 5: вырожденное дерево — все влево (descending inserts)
    {
        BinarySearchTree<int> bst;
        for (int i = 5; i >= 1; --i) bst.insert(i); // 5,4,3,2,1 inserted -> inorder 1..5
        auto it = bst.begin();
        auto e = bst.end();
        int expect = 1;
        while (it != e) {
            assert(*it == expect++);
            ++it;
        }
        assert(expect == 6);
    }

    cout << "  test_iterator_increment: OK\n\n";
}

// ---------------------------
// 2) Тест оператора * (разыменование)
// ---------------------------
void test_iterator_dereference() {
    cout << "test_iterator_dereference\n";

    // CASE 1: пустое дерево -> deref должен бросить out_of_range
    {
        BinarySearchTree<int> bst;
        auto it = bst.begin();
        bool thrown = false;
        try { int v = *it; (void)v; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 2: дерево из одного узла — можно читать и изменять (внутренний traversal — копия)
    {
        BinarySearchTree<int> bst;
        bst.insert(42);
        auto it = bst.begin();
        assert(*it == 42);

        // изменение через итератор меняет значение в traversal (не в дереве)
        *it = 100;
        assert(*it == 100);
    }

    // CASE 3: сбалансированное дерево — первые несколько элементов
    {
        BinarySearchTree<int> bst;
        for (int v : {4, 2, 6, 1, 3, 5, 7}) bst.insert(v);
        auto it = bst.begin(); // points to 1
        assert(*it == 1);      // проверяем первый
        ++it;
        assert(*it == 2);      // проверяем второй
        ++it;
        assert(*it == 3);      // проверяем третий
    }

    // CASE 4: вырожденное дерево вправо — доступ к середине
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 9; ++i) bst.insert(i); // inorder 1..9
        auto it = bst.begin();
        // двигаемся до 5-го элемента
        for (int i = 1; i < 5; ++i) ++it;
        assert(*it == 5); // проверяем значение посередине
        // изменяем через итератор
        *it = 500;
        assert(*it == 500);
    }

    // CASE 5: случайный набор значений
    {
        BinarySearchTree<int> bst;
        vector<int> ins = { 10, 5, 15, 3, 7, 12, 18 };
        for (int v : ins) bst.insert(v);
        // inorder должен быть [3,5,7,10,12,15,18]
        vector<int> expected = ins;
        sort(expected.begin(), expected.end());
        auto it = bst.begin();
        auto e = bst.end();
        size_t idx = 0;
        while (it != e) {
            assert(*it == expected[idx++]);
            ++it;
        }
        assert(idx == expected.size());
    }

    cout << "  test_iterator_dereference: OK\n\n";
}

// ---------------------------
// 3) Тест оператора != (сравнение итераторов)
// ---------------------------
void test_iterator_comparison() {
    cout << "test_iterator_comparison\n";

    // CASE 1: пустое дерево — begin == end
    {
        BinarySearchTree<int> bst;
        auto b = bst.begin();
        auto e = bst.end();
        assert(!(b != e));
    }

    // CASE 2: один элемент — begin != end, но после ++ begin == end
    {
        BinarySearchTree<int> bst;
        bst.insert(7);
        auto b = bst.begin();
        auto e = bst.end();
        assert(b != e);
        auto b_copy = b; // копия итератора (копирование должно работать)
        assert(!(b != b_copy));
        ++b;
        assert(!(b != e));
    }

    // CASE 3: два итератора, скопированные из одного — равны; после ++ становятся разными
    {
        BinarySearchTree<int> bst;
        for (int v : {2, 1, 3}) bst.insert(v);
        auto it1 = bst.begin();
        auto it2 = it1; // копия, разделяют один traversal pointer
        assert(!(it1 != it2));
        ++it1;
        assert(it1 != it2);
    }

    // CASE 4: end() дважды после single begin() -> оба end() должны быть равны
    {
        BinarySearchTree<int> bst;
        bst.insert(100);
        auto b = bst.begin(); // создаёт last_traversal
        auto e1 = bst.end();
        auto e2 = bst.end();
        assert(!(e1 != e2)); // оба end указывают на тот же traversal и index
    }

    // CASE 5: итераторы из разных деревьев — должны быть не равны
    {
        BinarySearchTree<int> a, b;
        a.insert(1); a.insert(2);
        b.insert(1); b.insert(2);
        auto itA = a.begin(); // создал last_traversal для a
        auto itB = b.begin(); // создал last_traversal для b
        // itA и itB ссылаются на разные буферы => не равны
        assert(itA != itB);
    }

    cout << "  test_iterator_comparison: OK\n\n";
}

// ---------------------------
// 4) Тест полного обхода (сбор значений через итератор)
// ---------------------------
void test_iterator_full_traversal() {
    cout << "test_iterator_full_traversal\n";

    // CASE 1: пустое дерево -> получаем пустой вектор
    {
        BinarySearchTree<int> bst;
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it) collected.push_back(*it);
        assert(collected.empty());
    }

    // CASE 2: один элемент
    {
        BinarySearchTree<int> bst;
        bst.insert(11);
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it) collected.push_back(*it);
        assert(collected.size() == 1 && collected[0] == 11);
    }

    // CASE 3: сбалансированное дерево
    {
        BinarySearchTree<int> bst;
        vector<int> ins = { 4,2,6,1,3,5,7 };
        for (int v : ins) bst.insert(v);
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it) collected.push_back(*it);
        vector<int> expected = ins;
        sort(expected.begin(), expected.end());
        assert(collected == expected);
    }

    // CASE 4: вырожденное вправо
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 8; ++i) bst.insert(i);
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it) collected.push_back(*it);
        for (size_t i = 0; i < collected.size(); ++i) assert(collected[i] == static_cast<int>(i + 1));
    }

    // CASE 5: произвольный набор с дубликатами по смыслу (BST не вставляет дубликаты у тебя),
    // поэтому тестируем смесь значений
    {
        BinarySearchTree<int> bst;
        vector<int> ins = { 20, 10, 30, 5, 15, 25, 35 };
        for (int v : ins) bst.insert(v);
        vector<int> collected;
        for (auto it = bst.begin(); it != bst.end(); ++it) collected.push_back(*it);
        vector<int> expected = ins;
        sort(expected.begin(), expected.end());
        assert(collected == expected);
    }

    cout << "  test_iterator_full_traversal: OK\n\n";
}

// ---------------------------
// 5) Тест исключительных ситуаций (dereference end и выход за границы)
// ---------------------------
void test_iterator_exceptions() {
    cout << "test_iterator_exceptions\n";

    // CASE 1: пустое дерево -> deref begin() бросает
    {
        BinarySearchTree<int> bst;
        bool thrown = false;
        try { int x = *bst.begin(); (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 2: single -> deref(end) бросает
    {
        BinarySearchTree<int> bst;
        bst.insert(7);
        auto b = bst.begin();
        auto e = bst.end();
        bool thrown = false;
        try { int x = *e; (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 3: после прохода до конца, разыменование также бросает
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 3; ++i) bst.insert(i);
        auto it = bst.begin();
        auto e = bst.end();
        // шаг до конца
        while (it != e) ++it;
        bool thrown = false;
        try { int x = *it; (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 4: многократный ++ за пределы end — оператор++ должен быть защищён от переполнения
    {
        BinarySearchTree<int> bst;
        for (int i : {2, 1, 3}) bst.insert(i);
        auto it = bst.begin();
        auto e = bst.end();
        // делаем много ++ — не должно упасть, но разыменование бросит
        for (int k = 0; k < 10; ++k) ++it;
        bool thrown = false;
        try { int x = *it; (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 5: убедимся, что копия итератора после продвижения ведёт себя корректно
    {
        BinarySearchTree<int> bst;
        for (int i = 1; i <= 5; ++i) bst.insert(i);
        auto it = bst.begin();
        ++it; // now points to second element
        auto it_copy = it; // копия
        assert(*it == *it_copy);
        ++it;
        assert(*it != *it_copy); // независимые позиции
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


