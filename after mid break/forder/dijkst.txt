#include <bits/stdc++.h>
using namespace std;

void Dijkstra(int V, vector<vector<int>>& graph, int source) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visit(V, false);
    dist[source] = 0;

    for (int c = 0; c < V - 1; c++) {
        int u = -1;
        for (int i = 0; i < V; i++) {
            if (!visit[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visit[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !visit[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << ": " << dist[i] << endl;
    }
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 3, 0, 0, 10, 0},
        {1, 0, 1, 7, 5, 0, 2},
        {3, 1, 0, 9, 3, 0, 0},
        {0, 7, 9, 0, 2, 1, 12},
        {0, 5, 3, 2, 0, 2, 0},
        {10, 0, 0, 1, 2, 0, 0},
        {0, 2, 0, 12, 0, 0, 0}
    };

    int V = graph.size();
    int source = 3;

    Dijkstra(V, graph, source);

    return 0;
}
