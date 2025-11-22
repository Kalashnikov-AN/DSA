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


// Тест 1: тестирование операций с вершинами (addVertex, removeVertex, hasVertex, size)
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

    cout << "test_vertex_operations passed\n";
}

// Тест 2: тестирование операций с рёбрами (addEdge, removeEdge, hasEdge, getEdge)
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
    try {
        g.getEdge("A", "B");
    }
    catch (const runtime_error&) {
        threw2 = true; 
    }
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

// Тест 3: BFS 
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
    g.addVertex("D");
    g.addVertex("E");
    g.addEdge("A", "C", 1.0); // уже установлено? повторно — безопасно
    g.addEdge("B", "D", 1.0);
    g.addEdge("C", "E", 1.0);
    auto order4 = g.BFS("A");
    // BFS посетит уровни: A, (B,C), (D,E) — порядок между B и C зависит от индексов вершин.
    assert(order4.size() == 5);
    assert(order4[0] == "A");
    assert(order4[1] == "B");
    assert(order4[2] == "C");
    assert(order4[3] == "D");
    assert(order4[4] == "E");

    // Случай 6: граф с циклом (A->B, B->A)
    DirectedGraph<string, double> g2(1000000000);
    g2.addVertex("A");
    g2.addVertex("B");
    g2.addEdge("A", "B", 1.0);
    g2.addEdge("B", "A", 1.0);
    auto order5 = g2.BFS("A");
    // BFS должен посетить A и B ровно по одному разу
    assert(order5.size() == 2);
    assert(order5[0] == "A" && order5[1] == "B");

    cout << "test_bfs passed\n";
}

// Тест 4: DFS
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
    // A, B, C
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
    assert(o4[1] == "C");
    assert(o4[2] == "E");
    assert(o4[3] == "B");
    assert(o4[4] == "D");

    // Случай 6: граф с циклом A->B, B->A
    DirectedGraph<string, double> g2(1000000000);
    g2.addVertex("A");
    g2.addVertex("B");
    g2.addEdge("A", "B", 1.0);
    g2.addEdge("B", "A", 1.0);
    auto o5 = g2.DFS("A");
    assert(o5.size() == 2);

    cout << "test_dfs passed\n";
}

// Тестирующая функция для GetNeighbors 
void test_get_neighbors() {

    const double INF = 1000000000;
    DirectedGraph<string, double> g(INF);

    // Случай 1: пустой граф -> вызов GetNeighbors должен бросить исключение (вершины нет)
    bool threw = false;
    try {
        auto r = g.GetNeighbors("A");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: граф из одной вершины -> neighbors пуст
    g.addVertex("A");
    {
        auto n = g.GetNeighbors("A");
        assert(n.empty());
    }

    // Случай 3: несколько вершин, но нет рёбер -> neighbors пуст
    g.addVertex("B");
    g.addVertex("C");
    {
        auto n = g.GetNeighbors("A");
        assert(n.empty());
        // Также проверить для другой вершины
        auto nb = g.GetNeighbors("B");
        assert(nb.empty());
    }

    // Случай 7: большой разреженный граф 
    // добавим 200 вершин, установим ребра 0->1..10
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

    const double INF = 1000000000;
    DirectedGraph<string, double> g(INF);

    // Случай 1: пустой граф -> GetWeight должен бросить исключение
    bool threw = false;
    try {
        double w = g.GetWeight("A", "B");
        
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 2: граф из одной вершины -> GetWeight(A,A) должно бросать (ребро отсутствует)
    g.addVertex("A");
    threw = false;
    try {
        double w = g.GetWeight("A", "A");
        
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Случай 3: простое направленное ребро A->B
    g.addVertex("B");
    g.addEdge("A", "B", 3.5);
    {
        double w = g.GetWeight("A", "B");
        assert(w == 3.5);
    }

    // Случай 4: есть только обратное ребро C->A
    g.addVertex("C");
    g.addEdge("C", "A", 2.0);
    // Проверяем: GetWeight(A,C) — нет ребра A->C => бросит исключение
    threw = false;
    try {
        double w = g.GetWeight("A", "C");
    }
    catch (const runtime_error&) {
        threw = true;
    }
    assert(threw);

    // Но GetWeight(C,A) вернёт 2.0
    {
        double w = g.GetWeight("C", "A");
        assert(w == 2.0);
    }

    // Случай 5: двунаправленное ребро X <-> Y: веса различны
    g.addVertex("X");
    g.addVertex("Y");
    g.addEdge("X", "Y", 1.0);
    g.addEdge("Y", "X", 4.0);
    {
        double wxy = g.GetWeight("X", "Y");
        double wyx = g.GetWeight("Y", "X");
        assert(wxy == 1.0 && wyx == 4.0);
    }

    // Случай 6: попытка GetWeight для несуществующей вершины -> бросит ислючение
    bool threw2 = false;
    try {
        g.GetWeight("test", "A");
    }
    catch (const runtime_error&) {
        threw2 = true;
    }
    assert(threw2);

    // Случай 7: большой граф: проверим корректность для цепочки
    DirectedGraph<int, double> big(INF);
    const int M = 100;
    for (int i = 0; i < M; ++i)
        big.addVertex(i);
    for (int i = 0; i < M - 1; ++i)
        big.addEdge(i, i + 1, (double)i + 0.5);

    // проверка нескольких значений
    for (int i = 0; i < 99; ++i) {
        double w = big.GetWeight(i, i + 1);
        assert(w == (double)i + 0.5);
    }

    cout << "test_get_weight passed.\n";
}

// Тест метода BellmanFord
void test_bellman_ford() {
    const double INF = 1000000000;

    
    // Случай 1: пустой граф — вызов с несуществующей вершиной должен бросить исключение
    
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

    
    // Случай 2: граф из одной вершины — расстояние до себя = 0
    
    {
        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        auto res = g.BellmanFord("A");
        // должно быть ровно одна вершина и расстояние 0
        assert(res.size() == 1);
        assert(res[0] == 0.0);
    }

    
    // Случай 3: несколько вершин, но нет рёбер — только стартовая 0, остальные INF
    
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

    
    // Случай 4: отрицательные веса, но без отрицательного цикла
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
        assert(res[2] == 2.0);    // C
        assert(res[1] == -1.0);   // B через C: -1
    }

    
    // Случай 5: обнаружение отрицательного цикла — метод должен бросить исключение
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

    
    // Случай 6: смесь достижимых и недостижимых вершин 
    
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

    
    // Случай 7: большой граф — цепочка из N вершин 
    
    {
        DirectedGraph<int, double> g(INF);
        const int N = 200;
        for (int i = 0; i < N; ++i)
            g.addVertex(i);
        for (int i = 0; i < N - 1; ++i)
            g.addEdge(i, i + 1, 1.0);
        auto res = g.BellmanFord(0);
        assert(res.size() == N);
        // проверяем несколько точек
        assert(res[0] == 0.0);
        assert(res[1] == 1.0);
        assert(res[10] == 10.0);
        assert(res[N - 1] == double(N - 1));
    }

    cout << "test_bellman_ford passed.\n";
}


/*
Тест метода saveGraphML 
*/
void test_saveGraphML() {
    const double INF = 1000000000;

    //  Случай 1: пустой граф 
    {
        string fname = "test_save_empty.graphml";
        remove(fname.c_str()); 

        DirectedGraph<string, double> g(INF);
        g.saveGraphML(fname);

        // Файл должен существовать и содержать graphml header
        ifstream f(fname);
        assert(f.is_open());
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>()); 
        f.close();

        assert(content.find("<graphml") != string::npos); 
        assert(content.find("<graph") != string::npos);

        //remove(fname.c_str());
    }

    //  Случай 2: один узел 
    {
        string fname = "test_save_one_node.graphml";
        remove(fname.c_str());

        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.saveGraphML(fname);

        ifstream f(fname);
        assert(f.is_open());
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        f.close();

        // Должен присутствовать node n0 и label A
        assert(content.find("node id=\"n0\"") != string::npos);
        assert(content.find("A") != string::npos);

        //remove(fname.c_str());
    }

    //  Случай 3: несколько вершин без рёбер 
    {
        string fname = "test_save_nodes_no_edges.graphml";
        remove(fname.c_str());

        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.saveGraphML(fname);

        ifstream f(fname);
        assert(f.is_open());
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        f.close();

        // Проверим количество появлений "<node"
        size_t pos = 0;
        int nodeCount = 0;
        while ((pos = content.find("<node", pos)) != string::npos) {
            ++nodeCount;
            pos += 5;
        }
        assert(nodeCount == 3);

        // В файле не должно быть тегов <edge> (поскольку нет рёбер)
        assert(content.find("<edge") == string::npos);

        //remove(fname.c_str());
    }

    //  Случай 4: граф с рёбрами и весами 
    {
        string fname = "test_save_edges.graphml";
        remove(fname.c_str());

        DirectedGraph<string, double> g(INF);
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B", 5.5);
        g.saveGraphML(fname);

        ifstream f(fname);
        assert(f.is_open());
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        f.close();

        // Ожидаем наличие edge с source n0 target n1 и вес 5.5
        assert(content.find("<edge") != string::npos);
        assert(content.find("source=\"n0\"") != string::npos);
        assert(content.find("target=\"n1\"") != string::npos);
        assert(content.find("5.5") != string::npos);

        //remove(fname.c_str());
    }

    //  Случай 5: большой граф 
    {
        string fname = "test_save_large.graphml";
        remove(fname.c_str());

        DirectedGraph<int, double> g(INF);
        const int N = 100;
        for (int i = 0; i < N; ++i)
            g.addVertex(i);
        for (int i = 0; i < N - 1; ++i)
            g.addEdge(i, i + 1, 1.0);
        g.saveGraphML(fname);

        // Открываем файл обычным способом
        ifstream f(fname);
        assert(f.is_open());

        // Читаем содержимое в строку
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());

        f.close();

        // Проверка размера 
        assert(content.length() > 1000);

        //  Проверки узлов 
        assert(content.find("<node id=\"n0\"") != string::npos);
        assert(content.find("<node id=\"n10\"") != string::npos);
        assert(content.find("<node id=\"n50\"") != string::npos);
        assert(content.find("<node id=\"n99\"") != string::npos);

        //  Проверки рёбер 
        assert(content.find("<edge isDirected=\"true\" source=\"n0\" target=\"n1\"") != string::npos);
        assert(content.find("<edge isDirected=\"true\" source=\"n10\" target=\"n11\"") != string::npos);
        assert(content.find("<edge isDirected=\"true\" source=\"n50\" target=\"n51\"") != string::npos);
        assert(content.find("<edge isDirected=\"true\" source=\"n98\" target=\"n99\"") != string::npos);

        //remove(fname.c_str());
    }


    //  Случай 6: перезапись файла (save дважды) 
    {
        string fname = "test_save_overwrite.graphml";
        remove(fname.c_str());

        DirectedGraph<string, double> g(INF);
        g.addVertex("X");
        g.saveGraphML(fname);

        // Сохраняем другой граф в тот же файл
        DirectedGraph<string, double> g2(INF);
        g2.addVertex("Y");
        g2.saveGraphML(fname);

        ifstream f(fname);
        assert(f.is_open());
        string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
        f.close();

        // Проверяем, что записался именно новый граф
        assert(content.find("name = \"Y\"") != string::npos);
        assert(content.find("name = \"X\"") == string::npos);

        //remove(fname.c_str());
    }


    cout << "test_saveGraphML passed.\n";
}


/*
  Тест метода loadGraphML
*/
void test_loadGraphML() {
    const double INF = 1000000000;

    //  Случай 1: несуществующий файл (ошибка) 
    {
        string fname = "this_file_does_not_exist.graphml";
        remove(fname.c_str());

        DirectedGraph<string, double> g(INF);
        bool threw = false;
        try {
            g.loadGraphML(fname);
        }
        catch (const runtime_error&) {
            threw = true;
        }
        assert(threw);
    }

    //  Случай 2: пустой файл 
    {
        string fname = "test_load_empty.graphml";
        {
            ofstream f(fname);
        }

        DirectedGraph<string, double> g(INF);
        g.loadGraphML(fname);
        assert(g.size() == 0);

        remove(fname.c_str());
    }

    //  Случай 3: один узел 
    {
        string fname = "test_load_one_node.graphml";
        ofstream f(fname);
        f << "<?xml version=\"1.0\"?>\n";
        f << "<graphml>\n";
        f << "  <graph id=\"G\" edgedefault=\"directed\">\n";
        f << "    <node id=\"n0\" name=\"A\"></node>\n";
        f << "  </graph>\n";
        f << "</graphml>\n";
        f.close();

        DirectedGraph<string, double> g(INF);
        g.loadGraphML(fname);

        assert(g.size() == 1);
        assert(g.hasVertex("A"));
        remove(fname.c_str());
    }

    //  Случай 4: несколько вершин без рёбер  
    {
        string fname = "test_load_nodes_no_edges.graphml";
        ofstream f(fname);
        f << "<?xml version=\"1.0\"?>\n<graphml>\n  <graph id=\"G\" edgedefault=\"directed\">\n";
        for (int i = 0; i < 4; ++i) {
            f << "    <node id=\"n" << i << "\" name=\"V" << i << "\"></node>\n";
        }
        f << "  </graph>\n</graphml>\n";
        f.close();

        DirectedGraph<string, double> g(INF);
        g.loadGraphML(fname);

        assert(g.size() == 4);
        for (int i = 0; i < 4; ++i) {
            assert(g.hasVertex("V" + to_string(i)));
        }
        assert(!g.hasEdge("V0", "V1"));
        remove(fname.c_str());
    }

    //  Случай 5: файл с рёбрами и весами 
    {
        string fname = "test_load_edges.graphml";
        ofstream f(fname);
        f << "<?xml version=\"1.0\"?>\n<graphml>\n";
        f << "  <graph id=\"G\" edgedefault=\"directed\">\n";
        f << "    <node id=\"n0\" name=\"A\"></node>\n";
        f << "    <node id=\"n1\" name=\"B\"></node>\n";
        f << "    <edge isDirected=\"true\" source=\"n0\" target=\"n1\" weight=\"5.5\"></edge>\n";
        f << "  </graph>\n</graphml>\n";
        f.close();

        DirectedGraph<string, double> g(INF);
        g.loadGraphML(fname);

        assert(g.size() == 2);
        assert(g.hasVertex("A"));
        assert(g.hasVertex("B"));
        assert(g.hasEdge("A", "B"));
        assert(g.GetWeight("A", "B") == 5.5);

        remove(fname.c_str());
    }

    //  Случай 6: большой файл 
    {
        string fname = "test_load_large.graphml";
        ofstream f(fname);
        f << "<?xml version=\"1.0\"?>\n<graphml>\n  <graph id=\"G\" edgedefault=\"directed\">\n";
        const int N = 80;

        for (int i = 0; i < N; ++i)
            f << "    <node id=\"n" << i << "\" name=\"n" << i << "\"></node>\n";

        for (int i = 0; i < N - 1; ++i)
            f << "    <edge isDirected=\"true\" source=\"n" << i << "\" target=\"n" << (i + 1)
            << "\" weight=\"1.0\"></edge>\n";

        f << "  </graph>\n</graphml>\n";
        f.close();

        DirectedGraph<string, double> g(INF);
        g.loadGraphML(fname);

        assert(g.size() == N);

        assert(g.hasVertex("n0"));
        assert(g.hasVertex("n10"));

        assert(g.hasEdge("n0", "n1"));
        assert(g.GetWeight("n0", "n1") == 1.0);

        remove(fname.c_str());
    }

    cout << "test_loadGraphML passed.\n";
}



