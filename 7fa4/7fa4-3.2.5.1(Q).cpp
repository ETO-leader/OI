#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> D,G;
vector<int> A,C;
void dfs1(int u,int f=0){
    for(auto&i:D[u]) i=C[u];
    for(auto&i:G[u]) if(i!=f){
        dfs1(i,u);
        cir(j,1,D[u].size()) D[u][j]+=D[i][j-1]; 
    }
}
void dfs2(int u,int f=0){
    auto k=D[u].size()-1;
    for(int i=k;~i;--i){
        D[u][i]+=(i>0?D[f][i-1]:0)-
            (i>1&&u!=1?D[u][i-2]:0);
    }
    A[u]=D[u][k];
    for(auto&i:G[u]) if(i!=f) dfs2(i,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;C.resize(n+1);
    G.resize(n+1);A.resize(n+1);
    D.assign(n+1,vector<int>(k+1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,1,n+1) cin>>C[i];
    dfs1(1);dfs2(1);
    cir(i,1,n+1) cout<<A[i]<<'\n';
    return 0;
}