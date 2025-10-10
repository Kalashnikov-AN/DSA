// Автор: Калашников А.Н.
#include <iostream>
#include "list.h"
using namespace std;

int main()
{
    test_insert_and_size();
    //test_remove_front_and_back();
    test_remove_node();
    test_concatenate_and_clear();
    test_copy_constructor();
    test_copy_assignment();
    test_move_constructor();
    test_move_assignment();
    test_node_at_and_indexing();
    test_at_methods();
    test_insert_at_empty();
    test_insert_at_various_positions();
    test_remove_at_various_positions();
    test_remove_at_out_of_range();
    DoublyLinkedList<int> list;
    list.insert_back(10);
    list.insert_back(20);
    list.insert_back(30);

    for (auto it = list.begin(); it != list.end(); ++it)
        cout << *it << " ";   // 10 20 30
    for (auto t : list) {
        cout << t;
        cout << "\n";
    }
    test_iterator_increment();
    test_iterator_dereference();
    test_iterator_comparison();
    test_iterator_full_iteration();
    test_iterator_edge_cases();
}

