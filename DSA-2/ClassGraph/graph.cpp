// Автор: Калашников А.Н.

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <algorithm>
#include "graph.h"
using namespace std;


// Test 1: тестирование операций с вершинами (addVertex, removeVertex, hasVertex, size)
// пустой граф, один элемент, несколько элементов,
// удаление существующих/несуществующих, повторное добавление.
void test_vertex_operations() {
    // Используем INF = 1000000000
    DirectedGraph<string, double> g(1000000000);

    // Случай 1: пустой граф
    assert(g.size() == 0);
    assert(!g.hasVertex("A"));

    // Случай 2: добавление одной вершины
    g.addVertex("A");
    assert(g.size() == 1);
    assert(g.hasVertex("A"));

    // Случай 3: добавление нескольких вершин
    g.addVertex("B");
    g.addVertex("C");
    assert(g.size() == 3);
    assert(g.hasVertex("B") && g.hasVertex("C"));

    // Случай 4: попытка добавить уже существующую вершину -> выбрасывает исключение
    bool threw = false;
    try {
        g.addVertex("B");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 5: удаление вершины в середине
    g.removeVertex("B");
    assert(g.size() == 2);
    assert(!g.hasVertex("B"));
    // Убедимся, что другие вершины сохранились
    assert(g.hasVertex("A") && g.hasVertex("C"));

    // Случай 6: удаление последней и проверка пустого графа
    g.removeVertex("C");
    g.removeVertex("A");
    assert(g.size() == 0);
    assert(!g.hasVertex("A"));

    // Случай 7: удаление несуществующей вершины должно бросить исключение
    bool threw2 = false;
    try {
        g.removeVertex("Z");
    }
    catch (const runtime_error&) {
        threw2 = true;
    }
    assert(threw2);

    cout << "test_vertex_operations passed\n";
}

// Test 2: тестирование операций с рёбрами (addEdge, removeEdge, hasEdge, getEdge)
// Случаи: вершины без рёбер, добавление ребра, редактирование (повторное addEdge),
// удаление ребра, операции с несуществующей вершиной.
void test_edge_operations() {
    DirectedGraph<string, double> g(1000000000);

    // Случай 1: пустой граф — попытка добавить ребро -> исключение (вершин нет)
    bool threw = false;
    try {
        g.addEdge("A", "B", 1.0);
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: создаём вершины, проверяем, что ребра отсутствуют
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    assert(!g.hasEdge("A", "B"));
    assert(!g.hasEdge("A", "C"));

    // Случай 3: добавляем ребро A->B
    g.addEdge("A", "B", 2.5);
    assert(g.hasEdge("A", "B"));
    assert(g.getEdge("A", "B") == 2.5);

    // Случай 4: редактируем ребро 
    g.addEdge("A", "B", 7.0);
    assert(g.getEdge("A", "B") == 7.0);

    // Случай 5: удаляем ребро
    g.removeEdge("A", "B");
    assert(!g.hasEdge("A", "B"));

    // Случай 6: попытка получить несуществующее ребро бросает исключение
    bool threw2 = false;
    try { g.getEdge("A", "B"); }
    catch (const runtime_error&) { threw2 = true; }
    assert(threw2);

    // Случай 7: операции с отсутствующей вершиной должны бросать исключение
    bool threw3 = false;
    try {
        g.removeEdge("X", "Y");
    }
    catch (const runtime_error&) {
        threw3 = true;
    }
    assert(threw3);

    cout << "test_edge_operations passed\n";
}

// Test 3: BFS — различные графы, проверяем порядок обхода и обработку ошибок.
// Минимум 5 случаев: пустой граф (ошибка), один узел, узлы без рёбер,
// простой путь, ветвящийся граф, граф с циклом.
void test_bfs() {
    DirectedGraph<string, double> g(1000000000);

    // Случай 1: пустой граф — запуск BFS должен бросить исключение
    bool threw = false;
    try {
        g.BFS("A");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: один узел
    g.addVertex("A");
    auto order1 = g.BFS("A");
    assert(order1.size() == 1 && order1[0] == "A");

    // Случай 3: несколько вершин, но без рёбер
    g.addVertex("B");
    g.addVertex("C");
    auto order2 = g.BFS("A");
    // BFS должен вернуть только стартовую вершину, т.к. нет рёбер
    assert(order2.size() == 1 && order2[0] == "A");

    // Случай 4: простой путь A->B->C
    g.addEdge("A", "B", 1.0);
    g.addEdge("B", "C", 1.0);
    auto order3 = g.BFS("A");
    // Oжидаемый порядок: A, B, C
    assert(order3.size() == 3 && order3[0] == "A" && order3[1] == "B" && order3[2] == "C");

    // Случай 5: ветвящийся граф A->B, A->C, B->D, C->E
    g.addVertex("D"); g.addVertex("E");
    g.addEdge("A", "C", 1.0); // уже установлено? повторно — безопасно
    g.addEdge("B", "D", 1.0);
    g.addEdge("C", "E", 1.0);
    auto order4 = g.BFS("A");
    // BFS посетит уровни: A, (B,C), (D,E) — порядок между B и C зависит от индексов вершин.
    assert(order4.size() == 5);
    assert(order4[0] == "A");
    // проверить, что элементы уровней 1 и 2 содержат нужные вершины (без строгого порядка)
    vector<string> level1 = { order4[1], order4[2] };
    sort(level1.begin(), level1.end());
    vector<string> expected1 = { "B","C" };
    sort(expected1.begin(), expected1.end());
    assert(level1 == expected1);

    vector<string> level2 = { order4[3], order4[4] };
    sort(level2.begin(), level2.end());
    vector<string> expected2 = { "D","E" };
    sort(expected2.begin(), expected2.end());
    assert(level2 == expected2);

    // Случай 6: граф с циклом (A->B, B->A)
    DirectedGraph<string, double> g2(1000000000);
    g2.addVertex("A");
    g2.addVertex("B");
    g2.addEdge("A", "B", 1.0);
    g2.addEdge("B", "A", 1.0);
    auto order5 = g2.BFS("A");
    // BFS должен посетить A и B ровно по одному разу
    assert(order5.size() == 2);
    assert((order5[0] == "A" && order5[1] == "B") || (order5[0] == "A" && order5[1] == "B"));

    cout << "test_bfs passed\n";
}

// Test 4: DFS — проверки похожи на BFS, но порядок отличается
void test_dfs() {
    DirectedGraph<string, double> g(1000000000);

    // Случай 1: пустой граф -> ошибка
    bool threw = false;
    try {
        g.DFS("A");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: один узел
    g.addVertex("A");
    auto o1 = g.DFS("A");
    assert(o1.size() == 1 && o1[0] == "A");

    // Случай 3: несколько вершин без рёбер
    g.addVertex("B");
    g.addVertex("C");
    auto o2 = g.DFS("A");
    assert(o2.size() == 1 && o2[0] == "A");

    // Случай 4: простой путь A->B->C
    g.addEdge("A", "B", 1.0);
    g.addEdge("B", "C", 1.0);
    auto o3 = g.DFS("A");
    // Для стека ожидаем поведение схожее с рекурсивным DFS: A, B, C
    assert(o3.size() == 3 && o3[0] == "A" && o3[1] == "B" && o3[2] == "C");

    // Случай 5: ветвящийся граф
    g.addVertex("D");
    g.addVertex("E");
    g.addEdge("A", "C", 1.0);
    g.addEdge("B", "D", 1.0);
    g.addEdge("C", "E", 1.0);
    auto o4 = g.DFS("A");
    assert(o4.size() == 5);
    assert(o4[0] == "A");
    // Множество остальных вершин должно соответствовать
    vector<string> rest(o4.begin() + 1, o4.end());
    sort(rest.begin(), rest.end());
    vector<string> expected = { "B","C","D","E" };
    sort(expected.begin(), expected.end());
    assert(rest == expected);

    // Случай 6: граф с циклом A->B, B->A
    DirectedGraph<string, double> g2(1000000000);
    g2.addVertex("A"); g2.addVertex("B");
    g2.addEdge("A", "B", 1.0); g2.addEdge("B", "A", 1.0);
    auto o5 = g2.DFS("A");
    assert(o5.size() == 2);

    cout << "test_dfs passed\n";
}

// Test 5: Bellman-Ford — минимум 5 случаев:
// - пустой граф (ошибка)
// - один узел (дистанция 0)
// - граф без рёбер (INF для остальных)
// - граф с отрицательным ребром, но без отрицательного цикла
// - граф с отрицательным циклом (проверяем вывод)
void test_bellman_ford() {
    DirectedGraph<string, double> g(1000000000);

    // Случай 1: пустой граф -> ошибка
    bool threw = false;
    try {
        g.BellmanFord("A");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: один узел
    g.addVertex("A");
    {
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        g.BellmanFord("A");
        cout.rdbuf(old);
        string out = oss.str();
        // В выводе должен быть "A : 0" или "A : 0\n" — проверим наличие "A" и "0"
        assert(out.find("A") != string::npos);
        assert(out.find("0") != string::npos);
    }

    // Случай 3: несколько вершин, но без рёбер
    g.addVertex("B"); g.addVertex("C");
    {
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        g.BellmanFord("A");
        cout.rdbuf(old);
        string out = oss.str();
        // A должна присутствовать, а у других расстояние не определено (INF или inf)
        assert(out.find("A") != string::npos);
        bool foundINF = (out.find("INF") != string::npos) ||
            (out.find("inf") != string::npos) ||
            (out.find("∞") != string::npos);
        assert(foundINF);
    }

    // Случай 4: граф со взвешенными рёбрами, отрицательное ребро, но без цикла
    g.addEdge("A", "B", 5.0);
    g.addEdge("A", "C", 2.0);
    g.addEdge("C", "B", -3.0); // путь A->C->B  = -1
    {
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        g.BellmanFord("A");
        cout.rdbuf(old);
        string out = oss.str();
        // Ожидаем, что B имеет отрицательное расстояние (-1)
        assert(out.find("B") != string::npos);
        assert(out.find("-1") != string::npos || out.find("-1.0") != string::npos);
    }

    // Случай 5: добавить отрицательный цикл: B->A с вес -10 создаёт цикл A->C->B->A (сумма < 0)
    g.addEdge("B", "A", -10.0);
    {
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        g.BellmanFord("A");
        cout.rdbuf(old);
        string out = oss.str();
        // Алгоритм печатает сообщение об отрицательном цикле
        assert(out.find("Обнаружен отрицательный цикл") != string::npos);
    }

    // Случай 6: Большой граф — тест производительности/корректности:
    // Построим граф из 50 вершин в цепочку и убедимся, что расстояния возрастают.
    DirectedGraph<int, double> big(1000000000);
    const int N = 50;
    for (int i = 0; i < N; ++i) big.addVertex(i);
    for (int i = 0; i < N - 1; ++i) big.addEdge(i, i + 1, 1.0);
    {
        ostringstream oss;
        streambuf* old = cout.rdbuf(oss.rdbuf());
        big.BellmanFord(0);
        cout.rdbuf(old);
        string out = oss.str();
        // Проверим, что последняя вершина N-1 имеет расстояние N-1
        string needle = to_string(N - 1);
        assert(out.find(needle) != string::npos);
    }

    cout << "test_bellman_ford passed\n";
}

// Test 6: комбинированные / граничные случаи (удаление вершины при наличии рёбер,
// повторное добавление после удаления, большие разреженные графы и т.д.)
void test_edge_cases_and_large_graphs() {
    DirectedGraph<int, double> g(1000000000);

    // Случай 1: удаление вершины, у которой были исходящие/входящие ребра
    g.addVertex(1); g.addVertex(2); g.addVertex(3);
    g.addEdge(1, 2, 1.0); g.addEdge(2, 3, 2.0); g.addEdge(3, 1, 3.0);
    // удаляем вершину 2
    g.removeVertex(2);
    // Теперь вершины 1 и 3 остались; убедимся, что граф корректен (нет ошибок при запросе)
    assert(g.size() == 2);
    assert(g.hasVertex(1) && g.hasVertex(3));

    // Случай 2: повторно добавляем ту же вершину, проверяем, что индексы перестроены
    g.addVertex(4);
    assert(g.hasVertex(4));
    // можно добавить ребро 1->4
    g.addEdge(1, 4, 5.0);
    assert(g.hasEdge(1, 4));

    // Случай 3: тест на большой разреженный граф: 1000 вершин, только 10 ребер
    const int BIG = 1000;
    DirectedGraph<int, double> big(1000000000);
    for (int i = 0; i < BIG; ++i) big.addVertex(i);
    // добавим 10 случайных ребер (последовательных для простоты)
    for (int i = 0; i < 10; ++i) big.addEdge(i, i + 1, 1.0);
    // проверяем, что размеры верные и ребра имеются
    assert(big.size() == BIG);
    for (int i = 0; i < 10; ++i) assert(big.hasEdge(i, i + 1));
    // остальные ребра отсутствуют
    assert(!big.hasEdge(500, 501));

    // Случай 4: добавление большого полного подграфа (50 вершин полностью связаны)
    DirectedGraph<int, double> dense(1000000000);
    const int M = 50;
    for (int i = 0; i < M; ++i) dense.addVertex(i);
    for (int u = 0; u < M; ++u) for (int v = 0; v < M; ++v) if (u != v) dense.addEdge(u, v, 1.0);
    assert(dense.size() == M);
    // Проверим несколько ребер
    assert(dense.hasEdge(0, 1) && dense.hasEdge(10, 20));
    // и что getEdge возвращает 1.0
    assert(dense.getEdge(0, 1) == 1.0);

    // Случай 5: попытка addEdge к несуществующей вершине в большом графе -> исключение
    bool threw = false;
    try { dense.addEdge(0, 9999, 1.0); }
    catch (const runtime_error&) { threw = true; }
    assert(threw);

    cout << "test_edge_cases_and_large_graphs passed\n";
}


// Тестирующая функция для GetNeighbors 
void test_get_neighbors() {
    cout << "Running test_get_neighbors()...\n";

    const double INF = 1000000000;
    DirectedGraph<string, double> g(INF);

    // Case 1: пустой граф -> вызов GetNeighbors должен бросить исключение (вершины нет)
    bool threw = false;
    try {
        auto r = g.GetNeighbors("A");
        (void)r;
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw && "Case1: пустой граф должен вызвать исключение");

    // Case 2: граф из одной вершины -> neighbors пуст
    g.addVertex("A");
    {
        auto n = g.GetNeighbors("A");
        assert(n.empty() && "Case2: одинокая вершина должна возвращать пустой список соседей");
    }

    // Case 3: несколько вершин, но нет рёбер -> neighbors пуст
    g.addVertex("B");
    g.addVertex("C");
    {
        auto n = g.GetNeighbors("A");
        assert(n.empty() && "Case3: вершина без рёбер должна возвращать пустой список");
        // Также проверить для другой вершины
        auto nb = g.GetNeighbors("B");
        assert(nb.empty());
    }

    // Case 7: большой разреженный граф — проверим масштабируемость
    // Создадим DirectedGraph<int,double> и добавим 200 вершин, установим ребра 0->1..10
    DirectedGraph<int, double> big(INF);
    const int N = 200;
    for (int i = 0; i < N; ++i)
        big.addVertex(i);
    for (int i = 1; i <= 10; ++i)
        big.addEdge(0, i, 1.0 * i);

    {
        auto neigh0 = big.GetNeighbors(0);
        // Ожидаем ровно 10 соседей: 1..10
        assert(neigh0.size() == 10);
        for (int i = 1; i <= 10; ++i) {
            // в big вершины представлены как int, поэтому проверяем присутствие
            assert(find(neigh0.begin(), neigh0.end(), i) != neigh0.end());
        }
        // Уверимся, что почти все другие вершины не имеют соседей (например, 50)
        auto neigh50 = big.GetNeighbors(50);
        assert(neigh50.empty());
    }

    cout << "test_get_neighbors passed.\n";
}

// Тестирующая функция для GetWeight
void test_get_weight() {
    cout << "Running test_get_weight()...\n";

    const double INF = 1000000000;
    DirectedGraph<string, double> g(INF);

    // Case 1: пустой граф -> GetWeight должен бросить
    bool threw = false;
    try {
        double w = g.GetWeight("A", "B");
        
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw && "Case1: пустой граф -> GetWeight должен бросить");

    // Case 2: граф из одной вершины -> GetWeight(A,A) должно бросать (ребро отсутствует)
    g.addVertex("A");
    threw = false;
    try {
        double w = g.GetWeight("A", "A");
        
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Case 3: простое направленное ребро A->B
    g.addVertex("B");
    g.addEdge("A", "B", 3.5);
    {
        double w = g.GetWeight("A", "B");
        assert(w == 3.5);
    }

    // Case 4: есть только обратное ребро B->C
    g.addVertex("C");
    g.addEdge("B", "C", 2.0);
    // Проверяем: GetWeight(A,C) — нет ребра A->C => бросит исключение
    threw = false;
    try {
        double w = g.GetWeight("A", "C");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Но GetWeight(B,C) вернёт 2.0
    {
        double w = g.GetWeight("B", "C");
        assert(w == 2.0);
    }

    // Case 5: двунаправленное ребро X <-> Y: веса различны
    g.addVertex("X");
    g.addVertex("Y");
    g.addEdge("X", "Y", 1.0);
    g.addEdge("Y", "X", 4.0);
    {
        double wxy = g.GetWeight("X", "Y");
        double wyx = g.GetWeight("Y", "X");
        assert(wxy == 1.0 && wyx == 4.0);
    }

    // Case 6: попытка GetWeight для несуществующей вершины -> бросит ислючение
    bool threw2 = false;
    try {
        g.GetWeight("NO_SUCH", "A");
    }
    catch (const runtime_error&) {
        threw2 = true;
    }
    assert(threw2);

    // Case 7: большой граф: проверим корректность для цепочки
    DirectedGraph<int, double> big(INF);
    const int M = 100;
    for (int i = 0; i < M; ++i) big.addVertex(i);
    for (int i = 0; i < M - 1; ++i) big.addEdge(i, i + 1, (double)i + 0.5);

    // проверка нескольких значений
    for (int i = 0; i < 10; ++i) {
        double w = big.GetWeight(i, i + 1);
        assert(w == (double)i + 0.5);
    }
    // проверка отсутствующего направления (i+1 -> i)
    bool threw3 = false;
    try {
        big.GetWeight(5, 4);
    }
    catch (const runtime_error&) {
        threw3 = true;
    }
    assert(threw3);

    cout << "test_get_weight passed.\n";
}

// Одна тестирующая функция, минимум 5 случаев, assert-only проверки.
void test_bellman_ford_vector_one_function() {
    cout << "Запускаю test_bellman_ford_vector_one_function()...\n";
    const double INF = 1000000000;

    
    // Case 1: пустой граф — вызов с несуществующей вершиной должен бросить исключение
    
    {
        DirectedGraph<string, double> g(INF);
        bool threw = false;
        try {
            auto res = g.BellmanFord("A"); // ожидаем исключение "Вершина не найдена"
        }
        catch (const runtime_error&) {
            threw = true;
        }
        // Проверяем, что исключение действительно было брошено
        assert(threw);
    }

    
    // Case 2: граф из одной вершины — расстояние до себя = 0
    
    {
        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        auto res = g.BellmanFord("A");
        // должно быть ровно одна вершина и расстояние 0
        assert(res.size() == 1);
        assert(res[0] == 0.0);
    }

    
    // Case 3: несколько вершин, но нет рёбер — только стартовая 0, остальные INF
    
    {
        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        // нет рёбер
        auto res = g.BellmanFord("A");
        assert(res.size() == 3);
        // проверяем: индекс 0 -> "A" (добавлена первой) = 0
        assert(res[0] == 0.0);
        // остальные должны быть недостижимы (INF)
        assert((res[1]) == INF);
        assert((res[2]) == INF);
    }

    
    // Case 4: отрицательные веса, но без отрицательного цикла
    // Пример: A->B:5, A->C:2, C->B:-3 => A->B через C = -1
    
    {
        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.addEdge("A", "B", 5.0);
        g.addEdge("A", "C", 2.0);
        g.addEdge("C", "B", -3.0);
        auto res = g.BellmanFord("A");
        // Ожидаем: A = 0, C = 2, B = -1
        assert(res.size() == 3);
        assert(res[0] == 0.0);    // A
        // Порядок вершин: добавлены A(0),B(1),C(2) — поэтому C индекс 2
        assert(res[2] == 2.0);    // C
        assert(res[1] == -1.0);   // B через C: -1
    }

    
    // Case 5: обнаружение отрицательного цикла — метод должен бросить исключение
    // Построим цикл A->B (1), B->C (-2), C->A (-1) => сумма = -2
    
    {
        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.addEdge("A", "B", 1.0);
        g.addEdge("B", "C", -2.0);
        g.addEdge("C", "A", -1.0);
        bool threw = false;
        try {
            auto res = g.BellmanFord("A");
        }
        catch (const runtime_error&) {
            threw = true;
        }
        assert(threw);
    }

    
    // Case 6: смесь достижимых и недостижимых вершин (разные компоненты)
    
    {
        DirectedGraph<int, double> g(INF);
        g.addVertex(0);
        g.addVertex(1);
        g.addVertex(2);
        g.addVertex(3);
        g.addEdge(0, 1, 1.0);
        g.addEdge(1, 2, 1.0);
        // вершина 3 изолирована
        auto res = g.BellmanFord(0);
        assert(res.size() == 4);
        assert(res[0] == 0.0);   // старт
        assert(res[1] == 1.0);
        assert(res[2] == 2.0);
        assert((res[3]) == INF); // недостижима
    }

    
    // Case 7: большой граф — цепочка из N вершин 
    
    {
        DirectedGraph<int, double> g(INF);
        const int N = 200;
        for (int i = 0; i < N; ++i)
            g.addVertex(i);
        for (int i = 0; i < N - 1; ++i)
            g.addEdge(i, i + 1, 1.0);
        auto res = g.BellmanFord(0);
        assert((int)res.size() == N);
        // проверяем несколько точек
        assert(res[0] == 0.0);
        assert(res[1] == 1.0);
        assert(res[10] == 10.0);
        assert(res[N - 1] == double(N - 1));
    }

    cout << "test_bellman_ford_vector_one_function passed.\n";
}
