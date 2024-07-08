#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G,CG;
vector<int> D,T,vis;
const int MOD=1e9+7;
void dfs(int u){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:G[u])
        CG[u].push_back(i),++T[i],dfs(i);
}
void dp(int u){
    for(auto&i:CG[u]){
        (D[i]+=D[u])%=MOD;
        if(!(--T[i])) dp(i);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    CG.resize(n+1);D.resize(n+1);
    vis.resize(n+1);T.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    D[1]=1;dfs(1);dp(1);
    cout<<D[n]<<'\n';
    return 0;
}