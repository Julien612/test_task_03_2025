#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Чтение данных из файла
bool read_data_from_file(const string& filename, int& n, int& m, vector<vector<int>>& adj, int& start) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла" << endl;
        return false;
    }

    file >> n >> m; // Чтение количества вершин и рёбер

    adj.resize(n); // Инициализация списка смежности

    // Чтение рёбер
    for (int k = 0; k < m; ++k) {
        int i, j;
        file >> i >> j;
        adj[i].push_back(j); // Ненаправленный граф, добавляем в обе стороны
        adj[j].push_back(i);
    }

    file >> start; // Чтение начальной вершины

    file.close();
    return true;
}

// Алгоритм BFS для поиска кратчайших расстояний
vector<int> bfs_shortest_path(const vector<vector<int>>& adj, int start, int n) {
    vector<int> dist(n, -1); // Инициализация расстояний (-1 означает, что вершина недостижима)
    queue<int> q;

    dist[start] = 0; // Расстояние до начальной вершины равно 0
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Обход всех соседей вершины u
        for (int v : adj[u]) {
            if (dist[v] == -1) { // Если вершина v ещё не посещена
                dist[v] = dist[u] + 1; // Обновляем расстояние
                q.push(v); // Добавляем в очередь для дальнейшего обхода
            }
        }
    }

    return dist;
}

// Вывод
void print_distances(const vector<int>& dist, int start) {
    cout << start << ":\n";
    for (size_t i = 0; i < dist.size(); ++i) {
        cout << i << ": ";
        if (dist[i] == -1) {
            cout << "\n";
        } else {
            cout << dist[i] << "\n";
        }
    }
}

int main() {
    string filename = "graph.txt";
    int n, m; // Количество вершин и рёбер
    int start; // Начальная вершина
    vector<vector<int>> adj; // Список смежности

    // Чтение данных из файла
    if (!read_data_from_file(filename, n, m, adj, start)) {
        return 1;
    }
    // Поиск кратчайших расстояний
    vector<int> dist = bfs_shortest_path(adj, start, n);
    // Вывод результатов
    print_distances(dist, start);

    return 0;
}
