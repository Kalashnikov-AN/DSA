// Автор: Калашников А.Н.

#include "graph.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    DirectedGraph<string, double> g1(9999999.0); // INF = 9999999
    g1.addVertex("A");
    g1.addVertex("B");
    g1.addVertex("C");
    g1.addVertex("D");
    g1.addVertex("E");
    g1.addVertex("F");
    g1.addVertex("G");


    g1.addEdge("A", "B", 4);
    g1.addEdge("A", "G", 4);
    g1.addEdge("F", "A", 8);
    g1.addEdge("B", "C", 5);
    g1.addEdge("C", "E", 7);
    g1.addEdge("C", "D", 3);
    g1.addEdge("E", "D", 3);
    g1.addEdge("E", "F", 3);
    g1.addEdge("G", "F", 7);

    g1.printMatrix();

    vector<string> res = g1.BFS("A");
    cout << "BFS" << endl;
    for (string element : res) {
        std::cout << element << " ";
    }
    cout << endl;

    vector<string> res2 = g1.DFS("A");
    cout << "DFS" << endl;
    for (string element : res2) {
        std::cout << element << " ";
    }
    cout << endl;

    // Кратчайшие пути
    vector<double> minWaytest = g1.BellmanFord("A");
    cout << "BellmanFord" << endl;
    for (double element : minWaytest) {
        std::cout << element << " ";
    }
    cout << endl;

    // Пример использования графа
    DirectedGraph<string, double> g(9999999.0); // INF = 9999999

    // Добавляем вершины
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    // Добавляем рёбра
    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 2);
    g.addEdge("B", "C", 5);
    g.addEdge("B", "D", 10);
    g.addEdge("C", "D", 3);

    g.printMatrix();

    // Обходы
    g.BFS("A");
    g.DFS("A");

    // Кратчайшие пути
    vector<double> minWay = g.BellmanFord("A");
    cout << "BellmanFord" << endl;
    for (double element : minWay) {
        std::cout << element << " ";
    }
    cout << endl;

    // Редактирование ребра
    g.addEdge("B", "D", 1);
    cout << "\nПосле редактирования ребра B->D = 1:\n";
    g.printMatrix();
    g.BellmanFord("A");
    cout << "Running graph tests...\n";
    test_vertex_operations();
    test_edge_operations();
    test_bfs();
    test_dfs();
   // test_bellman_ford();
    test_bellman_ford_vector_one_function();
    test_edge_cases_and_large_graphs();
    test_get_neighbors();
    test_get_weight();
    cout << "All tests passed successfully.\n";
    return 0;
}