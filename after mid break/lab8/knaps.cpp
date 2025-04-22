#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int P[6] = {60, 50, 70, 80, 30, 20};
    int wt[6] = {5, 3, 4, 6, 2, 1};
    int m = 15;
    int n = 6;
    int K[n + 1][m + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= m; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                K[i][w] = max(P[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    cout << "Maximum Survival Value: " << K[n][m] << endl;

    int w = m;
    cout << "Items included:" << endl;
    for (int i = n; i > 0 && w > 0; i--) {
        if (K[i][w] != K[i - 1][w]) {
            cout << "Item " << i << " -> Value: " << P[i - 1] << ", Weight: " << wt[i - 1] << "kg" << endl;
            w -= wt[i - 1];
        }
    }

    return 0;
}
