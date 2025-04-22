#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> in_degree, order;
vector<vector<int>> graph;

void topologicalSort() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) q.push(v);
        }
    }
}

int main() {
    cin >> n >> m;
    graph.resize(n);
    in_degree.resize(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        in_degree[v]++;
    }

    topologicalSort();

    if (order.size() == n) {
        for (int task : order) {
            cout << task << " ";
        }
    } else {
        cout << "Cycle detected, no valid order exists.";
    }

    return 0;
}

/*
7node
9edge
0 1
0 2
1 5
1 2
2 3
5 4
5 3
6 1
6 5
*/
