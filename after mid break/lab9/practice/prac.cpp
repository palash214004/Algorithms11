#include <bits/stdc++.h>
using namespace std;

// Graph A details
const int nA = 6; // Number of nodes in Graph A
const int ROWS_A = 8;
const int COLS_A = 4;
int E_A[ROWS_A][COLS_A] = {
    {0, 0, 0, 0},
    {0, 1, 1, 2}, // A--1--B
    {0, 2, 1, 3}, // A--2--C
    {0, 4, 3, 4}, // C--4--D
    {0, 7, 4, 5}, // D--7--E
    {0, 5, 3, 4}, // C--5--D
    {0, 6, 2, 6}, // C--6--F
    {0, 8, 5, 6}  // E--8--F
};
int Cost_A[nA][nA] = {
    {0, 1000, 2, 1000, 1000, 1000},
    {1000, 0, 1000, 4, 1000, 6},
    {2, 1000, 0, 1000, 7, 1000},
    {1000, 4, 1000, 0, 1000, 8},
    {1000, 1000, 7, 1000, 0, 1000},
    {1000, 6, 1000, 8, 1000, 0}
};

// Graph B details
const int nB = 7; // Number of nodes in Graph B
const int ROWS_B = 16;
const int COLS_B = 4;
int E_B[ROWS_B][COLS_B] = {
    {0, 0, 0, 0},
    {0, 3, 1, 2}, // A--3--B
    {0, 4, 1, 4}, // A--4--D
    {0, 5, 2, 3}, // B--5--C
    {0, 6, 2, 5}, // B--6--E
    {0, 8, 3, 6}, // C--8--F
    {0, 2, 4, 5}, // D--2--E
    {0, 7, 4, 7}, // D--7--H
    {0, 4, 5, 6}, // E--4--F
    {0, 5, 5, 8}, // E--5--I
    {0, 6, 6, 9}  // F--6--J
};
int Cost_B[nB][nB] = {
    {0, 3, 0, 4, 0, 0, 0},
    {3, 0, 5, 0, 6, 0, 0},
    {0, 5, 0, 0, 0, 8, 0},
    {4, 0, 0, 0, 2, 0, 7},
    {0, 6, 0, 2, 0, 4, 5},
    {0, 0, 8, 0, 4, 0, 6},
    {0, 0, 0, 7, 5, 6, 0}
};

int t[nA][3], near[nA];

// Prim's Algorithm
int Prims(int Cost[][nA], int nodes) {
    int minCost = 0;
    fill(near, near + nodes, 0);

    // Find the first edge with minimum cost
    int u = 0, v = 0, minEdge = INT_MAX;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (Cost[i][j] != 0 && Cost[i][j] < minEdge) {
                minEdge = Cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    // Initialize MST with the first edge
    t[0][0] = u; t[0][1] = v; minCost += minEdge;
    near[u] = near[v] = 1;

    // Add remaining edges to MST
    for (int i = 1; i < nodes - 1; i++) {
        int nextU = -1, nextV = -1, nextMinEdge = INT_MAX;
        for (int j = 0; j < nodes; j++) {
            if (near[j]) {
                for (int k = 0; k < nodes; k++) {
                    if (!near[k] && Cost[j][k] && Cost[j][k] < nextMinEdge) {
                        nextMinEdge = Cost[j][k];
                        nextU = j;
                        nextV = k;
                    }
                }
            }
        }
        t[i][0] = nextU; t[i][1] = nextV; minCost += nextMinEdge;
        near[nextV] = 1;
    }
    return minCost;
}

// Kruskal's Algorithm
struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSet(int parent[], int rank[], int u, int v) {
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

int Kruskal(int E[][COLS_A], int rows, int nodes) {
    vector<Edge> edges;
    for (int i = 1; i < rows; i++) {
        edges.push_back({E[i][2] - 1, E[i][3] - 1, E[i][1]});
    }

    sort(edges.begin(), edges.end(), compare);

    int parent[nodes], rank[nodes], minCost = 0;
    for (int i = 0; i < nodes; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int edgeCount = 0;
    for (Edge edge : edges) {
        if (edgeCount == nodes - 1) break;
        int u = find(parent, edge.u);
        int v = find(parent, edge.v);
        if (u != v) {
            t[edgeCount][0] = edge.u;
            t[edgeCount][1] = edge.v;
            minCost += edge.weight;
            edgeCount++;
            unionSet(parent, rank, u, v);
        }
    }
    return minCost;
}

int main() {
    cout << "Prim's Algorithm - Graph A:\n";
    int costA = Prims(Cost_A, nA);
    for (int i = 0; i < nA - 1; i++) {
        cout << "Edge: " << t[i][0] + 1 << " - " << t[i][1] + 1 << "\n";
    }
    cout << "Total Cost: " << costA << "\n\n";

    cout << "Kruskal's Algorithm - Graph A:\n";
    costA = Kruskal(E_A, ROWS_A, nA);
    for (int i = 0; i < nA - 1; i++) {
        cout << "Edge: " << t[i][0] + 1 << " - " << t[i][1] + 1 << "\n";
    }
    cout << "Total Cost: " << costA << "\n\n";

    cout << "Prim's Algorithm - Graph B:\n";
    int costB = Prims(Cost_B, nB);
    for (int i = 0; i < nB - 1; i++) {
        cout << "Edge: " << t[i][0] + 1 << " - " << t[i][1] + 1 << "\n";
    }
    cout << "Total Cost: " << costB << "\n\n";

    cout << "Kruskal's Algorithm - Graph B:\n";
    costB = Kruskal(E_B, ROWS_B, nB);
    for (int i = 0; i < nB - 1; i++) {
        cout << "Edge: " << t[i][0] + 1 << " - " << t[i][1] + 1 << "\n";
    }
    cout << "Total Cost: " << costB << "\n";

    return 0;
}

