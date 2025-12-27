// Автор: Калашников А.Н.

#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include "hashFunctions.h"
using namespace std;


/*
    Хеш-таблица
    Пользователь передаёт произвольную хеш-функцию через function<size_t(const Key&)>.
    Используется метод цепочек 
*/

template <typename Key>
class HashTable {
private:
    vector<list<Key>> table; // цепочки
    size_t table_size; // размер массива
    size_t num_elements; // количество элементов
    function<size_t(const Key&)> hasher; // пользовательская хеш-функция

    /// Проверка равенства ключей
    bool key_equality(const Key& a, const Key& b) const {
        return a == b;
    }

    /// Индекс бакета
    size_t index_for(const Key& key) const {
        return hasher(key) % table_size;
    }

    /// Перехеширование
    void rehash() {
        if ((double)num_elements / table_size > 0.75) {
            size_t new_size = table_size * 2;
            vector<list<Key>> new_table(new_size);

            for (auto& chain : table) {
                for (auto& key : chain) {
                    size_t new_index = hasher(key) % new_size;
                    new_table[new_index].push_back(key);
                }
            }

            table = move(new_table);
            table_size = new_size;
        }
        else if ((double)num_elements / table_size < 0.2) {
            size_t new_size = table_size / 2;
            if (new_size < 16)
                return;
            vector<list<Key>> new_table(new_size);

            for (auto& chain : table) {
                for (auto& key : chain) {
                    size_t new_index = hasher(key) % new_size;
                    new_table[new_index].push_back(key);
                }
            }

            table = move(new_table);
            table_size = new_size;
        }
    } 

public:
    /// Конструктор — принимает хеш-функцию
    HashTable(size_t init_size = 16,
        function<size_t(const Key&)> hash_func = function<size_t(const Key&)>())
        : table_size(init_size), num_elements(0) {
        if (table_size == 0)
            table_size = 16;  // Минимальный размер, чтобы избежать деления на 0
        table.resize(table_size);
        if (hash_func) {
            hasher = hash_func;
        }
        else {
            hasher = [](const Key& k) {
                return djb2(k);
                };  
        }
    }

    /// Вставка ключа
    void insert(const Key& key) {
        size_t idx = index_for(key);

        // проверяем дубликат
        for (const auto& k : table[idx]) {
            if (key_equality(k, key))
                return;
        }

        table[idx].push_back(key);
        num_elements++;
        // коэффициент загрузки
        if ((double)num_elements / table_size > 0.75) // рехэшируем если коэффициент загрузки > 0.75
            rehash();
    }

    /// Поиск ключа
    bool find(const Key& key) const {
        size_t idx = index_for(key);
        for (const auto& k : table[idx]) {
            if (key_equality(k, key))
                return true;
        }
        return false;
    }

    /// Удаление
    void remove(const Key& key) {
        size_t idx = index_for(key);
        auto& chain = table[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equality(*it, key)) {
                chain.erase(it);
                num_elements--;
                return;
            }
        }
        if ((double)num_elements / table_size < 0.2) // рехэшируем если коэффициент загрузки < 0.2
            rehash();
    }

    /// Возвращает размер таблицы
    size_t size() const {
        return num_elements; }

    /// Возвращает true/false пустая таблица или нет
    bool empty() const {
        return num_elements == 0; }
};

void test_insert();
void test_find();
void test_remove();
void test_rehash_behavior();



