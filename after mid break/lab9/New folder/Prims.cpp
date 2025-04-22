#include<bits/stdc++.h>
#define pii pair<int, int>

using namespace std;
void prims(unordered_map<int, vector<pii>> &adj, int n, int st)
{
    vector <int> key(n, INT_MAX);
    vector <int> parrent(n, -1);
    vector <bool> mst(n, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    key[st]=0;
    pq.push({key[st],st});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(mst[u]) continue;
        mst[u] = true;
        for(auto &edge: adj[u])
        {
            int v = edge.first;
            int wt = edge.second;
            if (!mst[v] and wt <key[v])
            {
                key[v]=wt;
                parrent[v]=u;
                pq.push({key[v],v});
            }
        }
    }
    int mcost=0;
    char Ar[] = {'A','B','C','D','E','F','G','H','I','J'};
    for(int i=0; i<n; i++){
        if(parrent[i] != -1){
            mcost += key[i];
            cout<< Ar[parrent[i]] <<" - "<< Ar[i] << " (Weight: "<<key[i] <<")\n";
        }
    }
    cout<<"Minimum cost= "<<mcost<<endl;
}

int main(){
    int n=6;
    unordered_map<int, vector<pair<int, int>>> adj;
    adj[0].push_back({1, 1}); // A-B
    adj[0].push_back({2, 2}); // A-C
    adj[1].push_back({0, 1}); // B-A
    adj[1].push_back({2, 3}); // B-C
    adj[2].push_back({0, 2}); // C-A
    adj[2].push_back({1, 3}); // C-B
    adj[2].push_back({3, 4}); // C-D
    adj[2].push_back({4, 5}); // C-E
    adj[2].push_back({5, 6}); // C-F
    adj[3].push_back({2, 4}); // D-C
    adj[3].push_back({4, 7}); // D-E
    adj[4].push_back({2, 4}); // E-C
    adj[4].push_back({3, 7}); // E-D
    adj[4].push_back({5, 8}); // E-F
    adj[5].push_back({2, 6}); // F-C
    adj[5].push_back({4, 8}); // F-E
    adj[9].push_back({6,8});
    cout<<"For Graph A: "<<endl;
    clock_t start = clock();
    prims(adj, n, 0);
    clock_t end = clock();
    double executionTime = (double(end-start)/CLOCKS_PER_SEC)*1000;
    cout<<"Execution Time: "<<executionTime<<"ns"<<endl;

    cout<<"\nFor Graph B:"<<endl;
    adj.clear();
    n=10;
    adj[0].push_back({1,3}); adj[0].push_back({3,4});
    adj[0].push_back({4,4}); adj[1].push_back({4,2});
    adj[1].push_back({5,3}); adj[1].push_back({2,10});
    adj[1].push_back({0,3}); adj[2].push_back({5,6});
    adj[2].push_back({6,1}); adj[2].push_back({1,10});
    adj[3].push_back({7,6}); adj[3].push_back({4,5});
    adj[3].push_back({0,4}); adj[4].push_back({7,2});
    adj[4].push_back({8,1}); adj[4].push_back({5,11});
    adj[4].push_back({0,8}); adj[4].push_back({1,2});
    adj[4].push_back({3,5}); adj[5].push_back({6,2});
    adj[5].push_back({8,3}); adj[5].push_back({9,11});
    adj[5].push_back({1,3}); adj[5].push_back({4,11});
    adj[5].push_back({2,6}); adj[6].push_back({9,8});
    adj[6].push_back({2,1}); adj[6].push_back({5,2});
    adj[7].push_back({3,6}); adj[7].push_back({4,2});
    adj[7].push_back({8,4}); adj[8].push_back({4,1});
    adj[8].push_back({5,3}); adj[8].push_back({9,7});
    adj[9].push_back({8,7}); adj[9].push_back({5,11});
    adj[9].push_back({6,8});

    start = clock();
    prims(adj, n, 0);
    end = clock();
    executionTime = (double(end-start)/CLOCKS_PER_SEC)*1000;
    cout<<"Execution Time: "<<executionTime<<"ns"<<endl;
    return 0;
}
