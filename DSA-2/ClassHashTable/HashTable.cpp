// Автор: Калашников А.Н.
#include "HashTable.h"
#include <cassert>

/*
    Тестируем insert()
*/
void test_insert() {

    // вставка в пустую таблицу
    {
        HashTable<int> ht;
        assert(ht.empty());
        ht.insert(42);
        assert(!ht.empty());
        assert(ht.size() == 1);
        assert(ht.find(42));
    }

    // вставка дубликата (должен игнорироваться)
    {
        HashTable<int> ht;
        ht.insert(10);
        ht.insert(10); // дубликат
        ht.insert(10); // снова
        assert(ht.size() == 1);
        assert(ht.find(10));
    }

    // маленькая таблица с коллизиями (коллизии с помощью хеша-константы)
    {
        // хеш-функция, возвращающая константу -> все элементы попадают в одну цепочку
        auto const_hash = [](const int&) -> size_t { return 1; };
        HashTable<int> ht(4, const_hash);
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4);
        // Все должны присутствовать, несмотря на коллизии
        assert(ht.size() == 4);
        assert(ht.find(1) && ht.find(2) && ht.find(3) && ht.find(4));
        assert(!ht.find(256));
    }

    // крупная таблица — вставка многих элементов
    {
        HashTable<int> ht(32);
        for (int i = 0; i < 1000; ++i) {
            ht.insert(i);
        }
        assert(ht.size() == 1000);
        // проверим несколько выборочных элементов
        assert(ht.find(0));
        assert(ht.find(500));
        assert(ht.find(999));
    }

    // вставка после удаления (вставка повторно того же элемента после удаления)
    {
        HashTable<int> ht;
        ht.insert(7);
        assert(ht.find(7));
        ht.remove(7);
        assert(!ht.find(7));
        ht.insert(7);
        assert(ht.find(7));
        assert(ht.size() == 1);
    }

    // вставка строк (проверка перегрузки djb2 для string)
    {
        HashTable<string> ht;
        ht.insert("alpha");
        ht.insert("beta");
        ht.insert("gamma");
        assert(ht.size() == 3);
        assert(ht.find("alpha") && ht.find("beta") && ht.find("gamma"));
    }

    cout << "test_insert: пройден\n";
}

/*
    Тестируем find()
*/
void test_find() {

    //  1: поиск в пустой таблице
    {
        HashTable<int> ht;
        assert(!ht.find(1));
        assert(ht.size() == 0);
    }

    //  2: поиск существующего и несуществующего элемента
    {
        HashTable<int> ht;
        ht.insert(11);
        ht.insert(22);
        ht.insert(33);
        assert(ht.find(11));
        assert(ht.find(22));
        assert(ht.find(33));
        assert(!ht.find(44));
    }

    //  3: поиск при коллизиях (все элементы в одной цепочке)
    {
        auto const_hash = [](const int&) -> size_t { return 0; };
        HashTable<int> ht(2, const_hash);
        for (int i = 1; i <= 6; ++i)
            ht.insert(i);
        for (int i = 1; i <= 6; ++i)
            assert(ht.find(i));
        assert(!ht.find(999));
    }

    //  4: поиск после нескольких вставок и удалений
    {
        HashTable<int> ht;
        for (int i = 0; i < 50; ++i)
            ht.insert(i);
        for (int i = 0; i < 25; ++i)
            ht.remove(i);
        for (int i = 0; i < 25; ++i)
            assert(!ht.find(i));
        for (int i = 25; i < 50; ++i)
            assert(ht.find(i));
    }

    //  5: поиск в большой таблице 
    {
        HashTable<int> ht(64);
        for (int i = 0; i < 2000; ++i)
            ht.insert(i * 2); // только четные
        assert(ht.find(0));
        assert(ht.find(100));
        assert(ht.find(1998 * 1)); 
        assert(!ht.find(1)); 
    }

    //  6: тип string — тест точного совпадения
    {
        HashTable<string> ht;
        ht.insert("one");
        ht.insert("two");
        ht.insert("three");
        assert(ht.find("one"));
        assert(!ht.find("One")); // чувствителен к регистру
    }

    cout << "test_find: пройден\n";
}

/*
    Тестируем remove()
*/
void test_remove() {

    //  1: удаление из пустой таблицы 
    {
        HashTable<int> ht;
        ht.remove(5); // ничего не делает
        assert(ht.size() == 0);
        assert(ht.empty());
    }

    //  2: удаление существующего элемента
    {
        HashTable<int> ht;
        ht.insert(100);
        assert(ht.find(100));
        ht.remove(100);
        assert(!ht.find(100));
        assert(ht.size() == 0);
    }

    //  3: удаление несуществующего элемента (не должно влиять на таблицу)
    {
        HashTable<int> ht;
        ht.insert(1);
        ht.insert(2);
        ht.remove(3);
        assert(ht.size() == 2);
        assert(ht.find(1) && ht.find(2));
    }

    //  4: удаление в таблице с коллизиями
    {
        auto const_hash = [](const int&) -> size_t { return 7; };
        HashTable<int> ht(8, const_hash);
        ht.insert(5);
        ht.insert(10);
        ht.insert(15);
        assert(ht.size() == 3);
        ht.remove(10);
        assert(!ht.find(10));
        assert(ht.find(5) && ht.find(15));
        assert(ht.size() == 2);
    }

    //  5: удаляем почти всё 
    {
        HashTable<int> ht(64);
        for (int i = 0; i < 200; ++i)
            ht.insert(i);
        for (int i = 0; i < 190; ++i)
            ht.remove(i);
        assert(ht.size() == 10);
        for (int i = 190; i < 200; ++i)
            assert(ht.find(i));
        for (int i = 0; i < 190; ++i)
            assert(!ht.find(i));
    }

    //  6: удаление и повторная вставка того же элемента
    {
        HashTable<string> ht;
        ht.insert("x");
        ht.remove("x");
        assert(!ht.find("x"));
        ht.insert("x");
        assert(ht.find("x"));
    }

    cout << "test_remove: пройден\n";
}

/*
    Косвенно тестируем поведение rehash 
*/
void test_rehash_behavior() {

    //  1: рост таблицы — вставляем элементы свыше порога 0.75 * table_size
    {
        // начальный размер 4: порог 0.75 * 4 = 3 -> при вставке 4 элементов должен произойти rehash
        HashTable<int> ht(4);
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        // пока что не превышен предел > 0.75 
        assert(ht.size() == 3);
        ht.insert(4); // теперь (4/4=1.0) > 0.75 -> рехеш
        assert(ht.size() == 4);
        // убедимся, что все элементы находятся после рехеша
        for (int i = 1; i <= 4; ++i)
            assert(ht.find(i));
    }

    //  2: многократный рост (несколько удвоений)
    {
        HashTable<int> ht(2);
        int N = 5000; // большое количество -> много рехешей вверх
        for (int i = 0; i < N; ++i)
            ht.insert(i);
        assert(ht.size() == N);
        // Проверим несколько значений
        assert(ht.find(0));
        assert(ht.find(123));
        assert(ht.find(N - 1));
    }

    //  3: уменьшение размера — вставляем много элементов, затем удаляем много элементов
    {
        // стартуем с большого размера чтобы деление на 2 могло сработать 
        HashTable<int> ht(128);
        for (int i = 0; i < 100; ++i)
            ht.insert(i); 
        assert(ht.size() == 100);
        // удаляем почти всё
        for (int i = 0; i < 90; ++i)
            ht.remove(i);
        // убеждаемся, что оставшиеся элементы доступны
        for (int i = 90; i < 100; ++i)
            assert(ht.find(i));
        assert(ht.size() == 10);
    }

    //  4: рехеш с коллизиями: убедимся, что элементы, находившиеся в одной цепочке,
    // после рехеша всё ещё доступны и не потеряны
    {
        auto const_hash = [](const int&) -> size_t { return 3; };
        HashTable<int> ht(4, const_hash);
        // вставим больше чем 0.75*4 чтобы инициировать рост
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4); // должен произойти рехеш 
        // все элементы должны быть найдены
        for (int i = 1; i <= 4; ++i)
            assert(ht.find(i));
    }

    //  5: много вставок и удалений
    {
        HashTable<int> ht(16);
        for (int i = 0; i < 300; ++i)
            ht.insert(i);
        for (int i = 0; i < 250; ++i)
            ht.remove(i);
        for (int i = 250; i < 300; ++i)
            assert(ht.find(i));
        assert(ht.size() == 50);
    }

    cout << "test_rehash_behavior: пройден\n";
}
