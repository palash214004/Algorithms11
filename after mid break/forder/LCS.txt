#include<bits/stdc++.h>
using namespace std;

void findlcs(const string & x, const string &y){
    int m = x.length();
    int n = y.length();

    vector<vector<int>> p(m+1, vector<int>(n+1, 0));

    for(int i= 1; i<=m; i++){
        for (int j = 1; j<=n; j++){
            if (x[i-1]==y[j-1]){
                p[i][j] = p[i-1][j-1]+1;
            }
            else{
                p[i][j]=max(p[i-1][j],p[i][j-1]);
            }
        }
    }
    string lcs ="";
    int i= m , j=n;
    while (i>0 && j>0){
        if (x[i-1]== y[j-1]){
            lcs= x[i-1]+lcs;
            i--;
            j--;
        }
        else if(p[i-1][j] > p[i][j-1]){
        i--;
        }
        else{
            j--;
        }
    }
    cout<< "L C S :"<< lcs<<endl;
    cout<< "Length OF LCS: "<< p[m][n]<<endl;

}

int main ()
{
    string x,y ;
    cout<< "Enter the 1st string: ";
    cin>>x;
    cout<<"Enter the 2nd string: ";
    cin>>y;
    //lullabybabies
     //skullandbones

    findlcs(x,y);
    return 0;

}
