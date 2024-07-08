#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;string fr,to;
    cin>>fr>>to;n=fr.size(),m=to.size();
    vector<vector<int>> D(n,vector<int>(m+1,_inf));
    bool Ap=false;D[0][0]=1;
    cir(i,1,m+1) Ap=Ap|(i?fr.front()==to[i-1]:0),D[0][i]=i-Ap;
    cir(i,1,n) cir(j,0,m+1){
        if(!j){D[i][j]=i+1;continue;}
        D[i][j]=min({D[i-1][j-1]+(fr[i]!=to[j-1]),D[i-1][j]+1,D[i][j-1]+1});
    }
    cout<<D[n-1][m]<<'\n';
    return 0;
}