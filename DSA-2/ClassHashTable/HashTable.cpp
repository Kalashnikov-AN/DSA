// Автор: Калашников А.Н.
#include "HashTable.h"
#include <cassert>

/*
    Тестируем insert()
    Каждая проверка прокомментирована; минимум 5 сценариев.
*/
void test_insert() {
    cout << "test_insert: start\n";

    // Case 1: вставка в пустую таблицу
    {
        HashTable<int> ht;
        assert(ht.empty());
        ht.insert(42);
        assert(!ht.empty());
        assert(ht.size() == 1);
        assert(ht.find(42));
    }

    // Case 2: вставка дубликата (должен игнорироваться)
    {
        HashTable<int> ht;
        ht.insert(10);
        ht.insert(10); // дубликат
        ht.insert(10); // снова
        assert(ht.size() == 1);
        assert(ht.find(10));
    }

    // Case 3: маленькая таблица с коллизиями (форсируем коллизии с помощью хеша-константы)
    {
        // хеш-функция, возвращающая константу -> все ключи попадают в одну цепочку
        auto const_hash = [](const int&) -> size_t { return 1; };
        HashTable<int> ht(4, const_hash);
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4);
        // Все должны присутствовать, несмотря на коллизии
        assert(ht.size() == 4);
        assert(ht.find(1) && ht.find(2) && ht.find(3) && ht.find(4));
    }

    // Case 4: крупная таблица — вставка многих элементов
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

    // Case 5: вставка после удаления (вставка повторно того же ключа после удаления)
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

    // Case 6: вставка строк (проверка перегрузки djb2 для string)
    {
        HashTable<string> ht;
        ht.insert("alpha");
        ht.insert("beta");
        ht.insert("gamma");
        assert(ht.size() == 3);
        assert(ht.find("alpha") && ht.find("beta") && ht.find("gamma"));
    }

    cout << "test_insert: passed\n";
}

/*
    Тестируем find()
    В каждом блоке — минимум 5 различных сценариев/утверждений.
*/
void test_find() {
    cout << "test_find: start\n";

    // Case 1: поиск в пустой таблице
    {
        HashTable<int> ht;
        assert(!ht.find(1));
        assert(ht.size() == 0);
    }

    // Case 2: поиск существующего и несуществующего элемента
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

    // Case 3: поиск при коллизиях (все элементы в одной цепочке)
    {
        auto const_hash = [](const int&) -> size_t { return 0; };
        HashTable<int> ht(2, const_hash);
        for (int i = 1; i <= 6; ++i) ht.insert(i);
        for (int i = 1; i <= 6; ++i) assert(ht.find(i));
        assert(!ht.find(999));
    }

    // Case 4: поиск после серии вставок и удалений
    {
        HashTable<int> ht;
        for (int i = 0; i < 50; ++i) ht.insert(i);
        for (int i = 0; i < 25; ++i) ht.remove(i);
        for (int i = 0; i < 25; ++i) assert(!ht.find(i));
        for (int i = 25; i < 50; ++i) assert(ht.find(i));
    }

    // Case 5: поиск в большой таблице (случайные выборки)
    {
        HashTable<int> ht(64);
        for (int i = 0; i < 2000; ++i) ht.insert(i * 2); // только четные
        assert(ht.find(0));
        assert(ht.find(100));
        assert(ht.find(1998 * 1)); // 1998 (проверка больших значений)
        assert(!ht.find(1)); // нечетное — не вставляли
    }

    // Case 6: тип string — тест точного совпадения
    {
        HashTable<string> ht;
        ht.insert("one");
        ht.insert("two");
        ht.insert("three");
        assert(ht.find("one"));
        assert(!ht.find("One")); // чувствителен к регистру
    }

    cout << "test_find: passed\n";
}

/*
    Тестируем remove()
    Минимум 5 кейсов: удаление из пустой, удаления существующего/несущ. элемента,
    удаление при коллизиях, удаление многих элементов (повторяющиеся удаления).
*/
void test_remove() {
    cout << "test_remove: start\n";

    // Case 1: удаление из пустой таблицы (ничего не должно сломаться)
    {
        HashTable<int> ht;
        ht.remove(5); // ничего не делает
        assert(ht.size() == 0);
        assert(ht.empty());
    }

    // Case 2: удаление существующего элемента
    {
        HashTable<int> ht;
        ht.insert(100);
        assert(ht.find(100));
        ht.remove(100);
        assert(!ht.find(100));
        assert(ht.size() == 0);
    }

    // Case 3: удаление несуществующего ключа (не должно влиять на таблицу)
    {
        HashTable<int> ht;
        ht.insert(1);
        ht.insert(2);
        ht.remove(3); // нет такого
        assert(ht.size() == 2);
        assert(ht.find(1) && ht.find(2));
    }

    // Case 4: удаление в таблице с коллизиями
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

    // Case 5: множественные удаления (удаляем почти всё) — проверка целостности
    {
        HashTable<int> ht(64);
        for (int i = 0; i < 200; ++i) ht.insert(i);
        for (int i = 0; i < 190; ++i) ht.remove(i);
        assert(ht.size() == 10);
        for (int i = 190; i < 200; ++i) assert(ht.find(i));
        for (int i = 0; i < 190; ++i) assert(!ht.find(i));
    }

    // Case 6: удаление и повторная вставка того же ключа
    {
        HashTable<string> ht;
        ht.insert("x");
        ht.remove("x");
        assert(!ht.find("x"));
        ht.insert("x");
        assert(ht.find("x"));
    }

    cout << "test_remove: passed\n";
}

/*
    Тестируем поведение rehash (масштабирование вверх и — косвенно — вниз).
    Заметьте: table_size приватное поле; мы не можем проверить его напрямую,
    но можем проверить корректность (сохранение всех элементов) после операций,
    которые должны вызвать rehash (увеличение и уменьшение).
    В каждом блоке — несколько проверок (>=5).
*/
void test_rehash_behavior() {
    cout << "test_rehash_behavior: start\n";

    // Case 1: рост таблицы — вставляем элементы свыше порога 0.75 * table_size
    {
        // начальный размер 4: порог 0.75 * 4 = 3 -> при вставке 4 элементов должен произойти rehash
        HashTable<int> ht(4);
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        // пока что не превышен >0.75 (3/4 == 0.75 -> условие строго >, пока не ре-хешится)
        assert(ht.size() == 3);
        ht.insert(4); // теперь (4/4=1.0) > 0.75 -> ре-хеш
        assert(ht.size() == 4);
        // убедимся, что все элементы находятся после ре-хеша
        for (int i = 1; i <= 4; ++i) assert(ht.find(i));
    }

    // Case 2: многократный рост (несколько удвоений)
    {
        HashTable<int> ht(2);
        int N = 5000; // большое количество -> много ре-хешей вверх
        for (int i = 0; i < N; ++i) ht.insert(i);
        assert(ht.size() == (size_t)N);
        // Проверим несколько образцовых значений
        assert(ht.find(0));
        assert(ht.find(123));
        assert(ht.find(N - 1));
    }

    // Case 3: спад (уменьшение размера) — вставляем много, затем удаляем много и проверяем, что оставшиеся корректны
    {
        // стартуем с большого initial чтобы деление на 2 могло сработать (new_size >= 16)
        HashTable<int> ht(128);
        for (int i = 0; i < 100; ++i) ht.insert(i); // 100 элементов
        assert(ht.size() == 100);
        // удаляем почти всё
        for (int i = 0; i < 90; ++i) ht.remove(i);
        // теперь size == 10, коэффициент загрузки = 10 / current_table_size
        // текущий table_size, возможно, уменьшился — мы не видим его напрямую,
        // но убеждаемся, что оставшиеся элементы доступны
        for (int i = 90; i < 100; ++i) assert(ht.find(i));
        assert(ht.size() == 10);
    }

    // Case 4: ре-хеш с коллизиями: убедимся, что элементы, находившиеся в одной цепочке,
    // после ре-хеша всё ещё доступны и не потеряны
    {
        auto const_hash = [](const int&) -> size_t { return 3; };
        HashTable<int> ht(4, const_hash);
        // вставим больше чем 0.75*4 чтобы инициировать рост
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        ht.insert(4); // должна произойти ре-хеш (увеличение)
        // все элементы должны быть найдены
        for (int i = 1; i <= 4; ++i) assert(ht.find(i));
    }

    // Case 5: стабильность после последовательных вставок и удалений
    {
        HashTable<int> ht(16);
        for (int i = 0; i < 300; ++i) ht.insert(i);
        for (int i = 0; i < 250; ++i) ht.remove(i);
        for (int i = 250; i < 300; ++i) assert(ht.find(i));
        assert(ht.size() == 50);
    }

    cout << "test_rehash_behavior: passed\n";
}

/*
    Тестируем size(), empty() и граничные кейсы в одной функции.
    Также проверяем поведение с нестандартным хешером (например, нетривиальных функций).
    Опять — минимум 5 сценариев.
*/
void test_size_empty_and_custom_hasher() {
    cout << "test_size_empty_and_custom_hasher: start\n";

    // Case 1: пустая таблица
    {
        HashTable<int> ht;
        assert(ht.empty());
        assert(ht.size() == 0);
    }

    // Case 2: после нескольких вставок/удалений size() корректен
    {
        HashTable<int> ht;
        ht.insert(1);
        ht.insert(2);
        ht.insert(3);
        assert(ht.size() == 3);
        ht.remove(2);
        assert(ht.size() == 2);
        ht.remove(100); // удаление несуществующего — не меняет size
        assert(ht.size() == 2);
    }

    // Case 3: custom hasher — хеш, который равен самому значению (identity)
    {
        auto identity = [](const int& x)->size_t { return static_cast<size_t>(x); };
        HashTable<int> ht(8, identity);
        ht.insert(5);
        ht.insert(13); // 13 % 8 == 5 -> коллизия по модулю, но хеш уникален
        assert(ht.find(5));
        assert(ht.find(13));
        assert(ht.size() == 2);
    }

    // Case 4: custom hasher на строках (простой)
    {
        auto len_hash = [](const string& s)->size_t { return s.size(); };
        HashTable<string> ht(4, len_hash);
        ht.insert("a");     // len 1
        ht.insert("bb");    // len 2
        ht.insert("ccc");   // len 3
        ht.insert("dddd");  // len 4
        // найдём все
        assert(ht.find("a"));
        assert(ht.find("bb"));
        assert(ht.find("ccc"));
        assert(ht.find("dddd"));
        assert(ht.size() == 4);
    }

    // Case 5: повторяющаяся вставка и удаление, проверка empty() в динамике
    {
        HashTable<int> ht;
        for (int i = 0; i < 10; ++i) ht.insert(i);
        for (int i = 0; i < 10; ++i) ht.remove(i);
        assert(ht.empty());
        assert(ht.size() == 0);
    }

    // Case 6: большие объёмы с кастомным хешем (проверка устойчивости)
    {
        auto mod7 = [](const int& x)->size_t { return (size_t)(x % 7); };
        HashTable<int> ht(32, mod7);
        for (int i = 0; i < 1000; ++i) ht.insert(i);
        assert(ht.size() == 1000);
        // проверим выборочные элементы
        assert(ht.find(0));
        assert(ht.find(7));
        assert(ht.find(999));
    }

    cout << "test_size_empty_and_custom_hasher: passed\n";
}