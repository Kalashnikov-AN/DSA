// Автор: Калашников А.Н.
#include <iostream>
#include <cassert>
#include <stdexcept>
#include "list.h"
#include <vector>
using namespace std;

template <typename T>
using List = DoublyLinkedList<T>;

// Тест 1: оператор ++ (префиксный инкремент)
// ---------------------------
void test_iterator_increment() {
    cout << "test_iterator_increment\n";

    // CASE 1: пустой список — begin() == end(), ++ не ломает сравнение
    {
        DoublyLinkedList<int> lst;
        auto it = lst.begin();
        auto e = lst.end();
        assert(!(it != e));        // begin == end для пустого
        ++it;                      // ++ не должен вызвать UB
        assert(!(it != e));        // по-прежнему равны
    }

    // CASE 2: один элемент — ++ переводит в end
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(7);
        auto it = lst.begin();
        auto e = lst.end();
        assert(*it == 7);          // изначально указывает на элемент
        ++it;                      // теперь должен указывать на end
        assert(!(it != e));
    }

    // CASE 3: небольшой список (3 элемента) — проходим по всем элементам
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1); lst.insert_back(2); lst.insert_back(3);
        vector<int> seen;
        for (auto it = lst.begin(); it != lst.end(); ++it)
            seen.push_back(*it);
        assert((seen == vector<int>{1, 2, 3}));
    }

    // CASE 4: большой список (100 элементов) — считаем шаги ++
    {
        DoublyLinkedList<int> lst;
        for (int i = 0; i < 100; ++i) lst.insert_back(i);
        size_t count = 0;
        for (auto it = lst.begin(); it != lst.end(); ++it) ++count;
        assert(count == 100);
    }

    // CASE 5: многократный ++ за end — ничего критического не происходит (итератор остаётся end)
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1);
        lst.insert_back(2);
        auto it = lst.begin();
        auto e = lst.end();
        // продвинем на много шагов
        for (int k = 0; k < 10; ++k) ++it;
        // должен быть равен end (или nullptr)
        assert(!(it != e));
    }

    cout << "  test_iterator_increment: OK\n\n";
}

// ---------------------------
// Тест 2: оператор * (разыменование)
// ---------------------------
void test_iterator_dereference() {
    cout << "test_iterator_dereference\n";

    // CASE 1: пустой список — разыменование должно бросать исключение
    {
        DoublyLinkedList<int> lst;
        bool thrown = false;
        try { int x = *lst.begin(); (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 2: список из одного узла — значение читается и меняется через iterator
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(42);
        auto it = lst.begin();
        assert(*it == 42);           // читаем
        *it = 100;                   // меняем через итератор (он возвращает ссылку)
        assert(lst[0] == 100);       // изменение видно в списке
    }

    // CASE 3: многопозиционный доступ: второй элемент можно получить и изменить
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1); lst.insert_back(2); lst.insert_back(3);
        auto it = lst.begin();
        ++it;                        // теперь указывает на второй элемент
        assert(*it == 2);
        *it = 20;
        assert(lst[1] == 20);
    }

    // CASE 4: dereference(end()) — бросает
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(5);
        auto e = lst.end();
        bool thrown = false;
        try { int x = *e; (void)x; }
        catch (const out_of_range&) { thrown = true; }
        assert(thrown);
    }

    // CASE 5: два итератора на один и тот же узел — изменения видны на обоих
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(7); lst.insert_back(8);
        auto it1 = lst.begin();
        auto it2 = lst.begin();
        assert(*it1 == *it2);
        *it1 = 99;
        assert(*it2 == 99);
        assert(lst[0] == 99);
    }

    cout << "  test_iterator_dereference: OK\n\n";
}

// ---------------------------
// Тест 3: оператор != (сравнение итераторов)
// ---------------------------
void test_iterator_comparison() {
    cout << "test_iterator_comparison\n";

    // CASE 1: пустой список — begin == end
    {
        DoublyLinkedList<int> lst;
        assert(!(lst.begin() != lst.end()));
    }

    // CASE 2: список из одного узла — begin != end; копия итератора равна оригиналу
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1);
        auto a = lst.begin();
        auto b = a;                  // копия итератора
        assert(!(a != b));           // равны
        assert(a != lst.end());      // begin != end
    }

    // CASE 3: итераторы на разные позиции — должны быть не равны
    {
        DoublyLinkedList<int> lst;
        for (int i = 1; i <= 4; ++i) lst.insert_back(i);
        auto it1 = lst.begin(); ++it1; // points to second
        auto it2 = lst.begin(); ++it2; ++it2; // points to third
        assert(it1 != it2);
    }

    // CASE 4: итераторы от разных списков — не равны
    {
        DoublyLinkedList<int> a, b;
        a.insert_back(1);
        b.insert_back(1);
        auto ia = a.begin();
        auto ib = b.begin();
        assert(ia != ib); // разные объекты / разные указатели
    }

    // CASE 5: достижение конца — итератор, дошедший до конца, равен end()
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(10);
        auto it = lst.begin();
        ++it;
        assert(!(it != lst.end()));
    }

    cout << "  test_iterator_comparison: OK\n\n";
}

// ---------------------------
// Тест 4: полный проход по списку с накоплением (итерация)
// ---------------------------
void test_iterator_full_iteration() {
    cout << "test_iterator_full_iteration\n";

    // CASE 1: пустой список -> собрали пустой вектор
    {
        DoublyLinkedList<int> lst;
        vector<int> out;
        for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
        assert(out.empty());
    }

    // CASE 2: один элемент
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(123);
        vector<int> out;
        for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
        assert(out.size() == 1 && out[0] == 123);
    }

    // CASE 3: нечетное количество элементов (5)
    {
        DoublyLinkedList<int> lst;
        for (int i = 1; i <= 5; ++i) lst.insert_back(i);
        vector<int> out;
        for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
        assert(out == vector<int>({ 1,2,3,4,5 }));
    }

    // CASE 4: четное количество элементов (6)
    {
        DoublyLinkedList<int> lst;
        for (int i = 10; i < 16; ++i) lst.insert_back(i);
        vector<int> out;
        for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
        assert(out == vector<int>({ 10,11,12,13,14,15 }));
    }

    // CASE 5: большие списки — проверка корректности прохода и количества
    {
        DoublyLinkedList<int> lst;
        const int N = 200;
        for (int i = 0; i < N; ++i) lst.insert_back(i * 2);
        int cnt = 0;
        int prev = -1;
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            ++cnt;
            int v = *it;
            // проверим монотонность и корректность значения (каждый элемент i*2)
            assert(v % 2 == 0);
            if (prev != -1) assert(v > prev);
            prev = v;
        }
        assert(cnt == N);
    }

    cout << "  test_iterator_full_iteration: OK\n\n";
}

// ---------------------------
// Тест 5: краевые и «поведенческие» сценарии
// ---------------------------
void test_iterator_edge_cases() {
    cout << "test_iterator_edge_cases\n";

    // CASE 1: несколько ++ подряд на одном итераторе
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1); lst.insert_back(2); lst.insert_back(3);
        auto it = lst.begin();
        ++it; ++it; ++it; // два перехода до end и ещё один
        assert(!(it != lst.end())); // всё равно end
    }

    // CASE 2: использование итератора после удаления других узлов (корректность текущего)
    {
        DoublyLinkedList<int> lst;
        for (int i = 1; i <= 5; ++i) lst.insert_back(i);
        auto it = lst.begin(); ++it; // points to second node (2)
        // удалим первый элемент — итератор на 2-й должен оставаться валидным (поскольку узел 2 не удалялся)
        lst.remove_front(); // удаляет первый узел
        assert(*it == 2); // итератор по-прежнему валиден
    }

    // CASE 3: удаление текущего узла и поведение итератора (заметим: итератор станет висячим)
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(10); lst.insert_back(20); lst.insert_back(30);
        auto it = lst.begin(); ++it; // points to 20
        // удалим узел, на который указывает it
        auto nodePtr = lst.node_at(1); // внутренний указатель на узел со значением 20
        lst.remove(nodePtr); // удалили узел 20 — it становится висячим
        // Разыменовывать it теперь нельзя — поведение неопределено; проверяем, что remove корректно поменял размер
        assert(lst.size() == 2);
    }

    // CASE 4: копирование итераторов и независимость позиций
    {
        DoublyLinkedList<int> lst;
        for (int i = 1; i <= 4; ++i) lst.insert_back(i);
        auto it1 = lst.begin();
        auto it2 = it1; // копия
        ++it1;
        assert(*it2 == 1); // копия не сдвинулась
        assert(*it1 == 2);
    }

    // CASE 5: вставка в середину списка — итератор, указывающий на узлы до/после вставки, остаётся корректным для своих узлов
    {
        DoublyLinkedList<int> lst;
        lst.insert_back(1); lst.insert_back(3);
        auto itBefore = lst.begin(); ++itBefore; // points to 3
        lst.insert_at(1, 2); // вставляем 2 между 1 и 3
        // itBefore по-прежнему указывает на узел со значением 3, т.к. мы не удаляли его
        assert(*itBefore == 3);
        // а полный проход от начала вернёт [1,2,3]
        vector<int> out;
        for (auto it = lst.begin(); it != lst.end(); ++it) out.push_back(*it);
        assert(out == vector<int>({ 1,2,3 }));
    }

    cout << "  test_iterator_edge_cases: OK\n\n";
}

/// Тест вставки элементов в начало/конец и проверки размера.
void test_insert_and_size() {
    List<int> lst;
    assert(lst.size() == 0);

    // Вставка в начало и конец
    lst.insert_front(10);
    assert(lst[0] == 10);
    assert(lst.size() == 1);
    assert(lst.find(10) != nullptr && lst.find(10)->data == 10);

    lst.insert_back(20);
    assert(lst.size() == 2);
    // проверяем порядок: head->10, tail->20
    assert(lst.find(10)->next->data == 20);
    assert(lst.find(20)->prev->data == 10);
}

/// Тест удаления элементов с начала и конца списка
void test_remove_front_and_back() {
    List<int> lst;
    lst.insert_back(1);
    lst.insert_back(2);
    lst.insert_back(3);
    assert(lst.size() == 3);

    // Удаление с начала
    lst.remove_front(); // уберёт 1
    assert(lst.size() == 2);
    assert(lst.find(1) == nullptr);
    assert(lst.find(2)->prev == nullptr);

    // Удаление с конца
    lst.remove_back(); // уберёт 3
    assert(lst.size() == 1);
    assert(lst.find(3) == nullptr);
    assert(lst.find(2)->next == nullptr);

    // Удаление из пустого — underflow_error
    lst.remove_front(); // теперь пусто
    bool underflow = false;
    try {
        lst.remove_front();
    }
    catch (const underflow_error&) {
        underflow = true;
    }
    assert(underflow);
}

/// Тест удаления конкретного узла
void test_remove_node() {
    DoublyLinkedList<char> lst;
    lst.insert_back('a');
    lst.insert_back('b');
    lst.insert_back('c');
    assert(lst.size() == 3);

    // Удаление конкретного узла 'b'
    auto nodeB = lst.find('b');
    lst.remove(nodeB);
    assert(lst.size() == 2);
    assert(lst.find('b') == nullptr);
    // Проверьте связь a <-> c
    auto nodeA = lst.find('a');
    auto nodeC = lst.find('c');
    assert(nodeA->next == nodeC);
    assert(nodeC->prev == nodeA);
}

/// Тест конкатенации двух списков и очистки
void test_concatenate_and_clear() {
    List<int> a, b;
    for (int i = 1; i <= 3; ++i) a.insert_back(i);
    for (int i = 4; i <= 6; ++i) b.insert_back(i);
    assert(a.size() == 3 && b.size() == 3);

    // Конкатенация b в a
    a.concatenate(b);
    assert(a.size() == 6);
    for (int i = 1; i <= 6; ++i) {
        assert(a.find(i) != nullptr);
    }
    // b должен быть очищен
    assert(b.size() == 0);

    // Очистка a
    a.clear();
    assert(a.size() == 0);
    assert(a.find(1) == nullptr);
}

/// Тест конструктора копирования
void test_copy_constructor() {
    List<int> a;
    for (int i = 1; i <= 5; ++i) a.insert_back(i);
    List<int> b(a);
    // Проверяем, что b содержит ту же последовательность
    assert(b.size() == a.size());
    for (int i = 1; i <= 5; ++i)
        assert(b.find(i) != nullptr && b.find(i)->data == i);
    // Изменение a не меняет b (глубокое копирование)
    a.remove_front();  // удаляем 1
    assert(a.size() == 4);
    assert(b.size() == 5);
    assert(b.find(1) != nullptr);
}

/// Тест оператора присваивания копированием
void test_copy_assignment() {
    List<string> a;
    a.insert_back("one");
    a.insert_back("two");
    List<string> b;
    b = a;
    assert(b.size() == a.size());
    assert(b.find("one") && b.find("two"));
    a.insert_back("three");
    assert(a.size() == 3);
    assert(b.size() == 2);
}

/// Тест конструктора перемещения
void test_move_constructor() {
    List<int> a;
    for (int i = 42; i <= 45; ++i) a.insert_back(i);
    List<int> b(move(a));
    // b получил данные
    assert(b.size() == 4);
    for (int i = 42; i <= 45; ++i)
        assert(b.find(i));
    // a должен быть пуст
    assert(a.size() == 0);
}

/// Тест оператора присваивания перемещением
void test_move_assignment() {
    List<char> a;
    a.insert_back('x');
    a.insert_back('y');
    List<char> b;
    b.insert_back('z');
    // превращаем a в rvalue
    b = move(a); 
    // b получил x,y
    assert(b.size() == 2);
    assert(b.find('x') && b.find('y'));
    // a пуст
    assert(a.size() == 0);
}

/// Тесты для методов node_at и []
void test_node_at_and_indexing() {
    DoublyLinkedList<int> lst;
    // Заполним список значениями 5, 10, 15, 20
    lst.insert_back(5);
    lst.insert_back(10);
    lst.insert_back(15);
    lst.insert_back(20);

    // Размер
    assert(lst.size() == 4);

    // node_at: корректные индексы
    assert(lst.node_at(0) && lst.node_at(0)->data == 5);
    assert(lst.node_at(1) && lst.node_at(1)->data == 10);
    assert(lst.node_at(2) && lst.node_at(2)->data == 15);
    assert(lst.node_at(3) && lst.node_at(3)->data == 20);

    // node_at: несуществующие индексы
    assert(lst.node_at(4) == nullptr);
    assert(lst.node_at(100) == nullptr);

    // operator[] чтение и изменение
    assert(lst[0] == 5);
    assert(lst[3] == 20);
    lst[2] = 99;
    assert(lst[2] == 99);

    // operator[] выход за границу => исключение
    bool caught = false;
    try {
        int x = lst[4];
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);


    // const доступ
    const DoublyLinkedList<int>& clst = lst;
    assert(clst[0] == 5);
    assert(clst[2] == 99);
    caught = false;
    try {
        int y = clst[5];
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);

}

/// Тест для метода at
void test_at_methods() {
    DoublyLinkedList<string> lst;
    lst.insert_back("a");
    lst.insert_back("b");
    lst.insert_back("c");

    // at чтение
    assert(lst.at(0) == "a");
    assert(lst.at(1) == "b");
    assert(lst.at(2) == "c");

    // at запись
    lst.at(1) = "beta";
    assert(lst.at(1) == "beta");

    // at выход за границу
    bool caught = false;
    try {
        string s = lst.at(3);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);

    // константная версия
    const DoublyLinkedList<string>& clst = lst;
    assert(clst.at(0) == "a");
    assert(clst.at(1) == "beta");
    caught = false;
    try {
        string t = clst.at(5);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}

/// Тест: вставка по индексу в пустой список
void test_insert_at_empty() {
    DoublyLinkedList<int> lst;
    // вставка по индексу 0 в пустой список эквивалентна insert_front
    lst.insert_at(0, 42);
    assert(lst.size() == 1);
    assert(lst[0] == 42);

    // попытка вставить по индексу > size должна бросить исключение
    bool caught = false;
    try {
        lst.insert_at(2, 100);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}

/// Тест: вставка в начало, середину и конец
void test_insert_at_various_positions() {
    DoublyLinkedList<string> lst;
    lst.insert_back("A");
    lst.insert_back("C");

    // вставка в начало
    lst.insert_at(0, "X"); // X, A, C
    assert(lst.size() == 3);
    assert(lst[0] == "X");
    assert(lst[1] == "A");

    // вставка в середину
    lst.insert_at(2, "Y"); // X, A, Y, C
    assert(lst.size() == 4);
    assert(lst[2] == "Y");
    assert(lst[3] == "C");

    // вставка в конец (index == size)
    lst.insert_at(lst.size(), "Z"); // X, A, Y, C, Z
    assert(lst.size() == 5);
    assert(lst[4] == "Z");

}

/// Тест: удаление по индексу в разных позициях
void test_remove_at_various_positions() {
    DoublyLinkedList<char> lst;
    lst.insert_back('a');
    lst.insert_back('b');
    lst.insert_back('c');
    lst.insert_back('d'); // a, b, c, d

    // удаление первого
    lst.remove_at(0); // b, c, d
    assert(lst.size() == 3);
    assert(lst[0] == 'b');

    // удаление последнего
    lst.remove_at(lst.size() - 1); // b, c
    assert(lst.size() == 2);
    assert(lst[1] == 'c');

    // удаление в середине
    lst.insert_back('e'); // b, c, e
    lst.insert_back('f'); // b, c, e, f
    lst.remove_at(2);     // b, c, f
    assert(lst.size() == 3);
    assert(lst[2] == 'f');
}

/// Тест: удаление по неверному индексу
void test_remove_at_out_of_range() {
    DoublyLinkedList<double> lst;
    lst.insert_back(1.1);
    bool caught = false;
    try {
        lst.remove_at(1);
    }
    catch (const out_of_range&) {
        caught = true;
    }
    assert(caught);
}




