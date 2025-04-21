// Автор: Калашников А.Н.
#include <locale>
#include "dynArray.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");
    runTests();
    test_push_pop_front();
    test_insert_at();
    test_remove_at();
}
