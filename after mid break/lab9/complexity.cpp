#include <bits/stdc++.h>
using namespace std;

#define V 5

int prim(int cost[V][V], vector<pair<int, int>>& mst) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    key[0] = 0;
    int mincost = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        for (int v = 0; v < V; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;
        mincost += key[u];

        for (int v = 0; v < V; v++) {
            if (cost[u][v] && !inMST[v] && cost[u][v] < key[v]) {
                key[v] = cost[u][v];
                mst.push_back({u, v});
            }
        }
    }
    return mincost;
}

int kru(vector<vector<int>>& edges, int n, vector<pair<int, int>>& mst) {
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    });

    vector<int> parent(n, -1);

    auto find = [&](int i) {
        while (parent[i] >= 0)
            i = parent[i];
        return i;
    };

    auto unionSets = [&](int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu != pv) {
            parent[pu] = pv;
            return true;
        }
        return false;
    };

    int mincost = 0;
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (unionSets(u, v)) {
            mst.push_back({u, v});
            mincost += w;
        }
    }

    return mincost;
}

int main() {
    int cost[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    vector<vector<int>> edges = {
        {0, 1, 2}, {1, 2, 3}, {0, 3, 6}, {1, 3, 8},
        {1, 4, 5}, {2, 4, 7}, {3, 4, 9}
    };

    vector<pair<int, int>> mstPrim, mstKruskal;

    auto startPrim = chrono::steady_clock::now();
    int mincostPrim = prim(cost, mstPrim);
    auto endPrim = chrono::steady_clock::now();
    auto durationPrim = chrono::duration_cast<chrono::seconds>(endPrim - startPrim);

    auto startKruskal = chrono::steady_clock::now();
    int mincostKruskal = kru(edges, V, mstKruskal);
    auto endKruskal = chrono::steady_clock::now();
    auto durationKruskal = chrono::duration_cast<chrono::seconds>(endKruskal - startKruskal);

    cout << "Prim's Algorithm:\n";
    for (const auto& edge : mstPrim) {
        cout << edge.first << " - " << edge.second << "\n";
    }
    cout << "Minimum cost: " << mincostPrim << endl;
    cout << "Execution Time: " << durationPrim.count() << " seconds\n\n";

    cout << "Kruskal's Algorithm:\n";
    for (const auto& edge : mstKruskal) {
        cout << edge.first << " - " << edge.second << "\n";
    }
    cout << "Minimum cost: " << mincostKruskal << endl;
    cout << "Execution Time: " << durationKruskal.count() << " seconds\n";

    return 0;
}
