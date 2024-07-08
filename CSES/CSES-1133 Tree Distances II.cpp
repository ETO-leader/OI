#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> G;
vector<lint> D,C;
int dfs1(int u,int f=0){
    for(auto&i:G[u]) if(i!=f){
        int d=dfs1(i,u);
        C[u]+=d;D[u]+=D[i]+d;
    }
    return (C[u]+=1);
}
void dfs2(int u,int n,int f=0){
    if(u==1) goto loop;
    D[u]=D[f]+n-C[u]*2;
    loop:for(auto&i:G[u]) if(i!=f) dfs2(i,n,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;D.resize(n+1);
    G.resize(n+1);C.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs1(1);dfs2(1,n);
    cir(i,1,n+1) cout<<D[i]<<' ';
    cout<<'\n';
    return 0;
}