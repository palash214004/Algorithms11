#include<bits/stdc++.h>
using namespace std;
bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2]<b[2];
}
void makeSet(vector<int> &parent, vector<int> &rank, int n){
    for( int i=0; i<n; i++){
        rank[i]=0;
        parent[i]=i;
    }
}
int findParent(vector<int>&parent, int node){
    if(parent[node]==node)
        return node;
    return parent[node]=findParent(parent, parent[node]);
}
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank){
    u = findParent(parent, u);
    v = findParent(parent, v);
    if(rank[u]<rank[v])
        parent[u]=v;
    else if(rank[v]<rank[u])
        parent[v]=u;
    else {
        parent[v]=u;
        rank[u]++;
    }
}
int main()
{
    int n = 10;
    char Ar[] = {'A','B','C','D','E','F','G','H','I','J'};
    cout<<"For Graph B:"<<endl;
    vector<vector<int>> edges = {
        {0,1,3},{0,3,4},{0,4,4},{1,4,2},{1,5,3},{1,2,10},{2,5,6},{2,6,1},
        {3,7,6},{3,4,5},{4,7,2},{4,8,1},{4,5,11},{5,6,2},{5,8,3},{5,9,11},{6,9,8},{7,8,4},{8,9,7}
    };
    sort(edges.begin(), edges.end(), cmp);
    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent, rank, n);
    int minWeight = 0;
    clock_t start = clock();
    for(int i=0; i<edges.size(); i++){
        int u=findParent(parent, edges[i][0]);
        int v=findParent(parent, edges[i][1]);
        int wt = edges[i][2];
        if(u!=v){
            cout<<Ar[edges[i][0]]<< " -> " <<Ar[edges[i][1]] <<" : " << edges[i][2]<<endl;
            minWeight += wt;
            unionSet(u, v, parent, rank);
        }
    }
    clock_t end = clock();
    double executionTime = (double(end-start)/CLOCKS_PER_SEC)*1000;
    cout<<"Minimum Cost: "<<minWeight<<endl;
    cout<<"Execution Time: "<<executionTime<<"ns"<<endl<<endl;

    n = 6;
    char Ar1[] = {'A','B','C','D','E','F','G','H','I','J'};
    cout<<"For Graph A:"<<endl;
    edges = {
        {0, 1, 1},
        {0, 2, 2},
        {1, 2, 3},
        {2, 3, 4},
        {2, 4, 5},
        {2, 5, 6},
        {3, 4, 7},
        {4, 5, 8}
    };
    sort(edges.begin(), edges.end(), cmp);
    vector<int> Parent(n);
    vector<int> Rank(n);
    makeSet(Parent, Rank, n);
    minWeight = 0;
    start = clock();
    for(int i=0; i<edges.size(); i++){
        int u=findParent(Parent, edges[i][0]);
        int v=findParent(Parent, edges[i][1]);
        int wt = edges[i][2];
        if(u!=v){
            cout<<Ar1[edges[i][0]]<< " -> " <<Ar1[edges[i][1]] <<" : " << edges[i][2]<<endl;
            minWeight += wt;
            unionSet(u, v, Parent, Rank);
        }
    }
    end = clock();
    executionTime = (double(end-start)/CLOCKS_PER_SEC)*1000;
    cout<<"Minimum Cost: "<<minWeight<<endl;
    cout<<"Execution Time: "<<executionTime<<"ns"<<endl;
    return 0;
}
