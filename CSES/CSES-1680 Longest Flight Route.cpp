#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define IMPOSSIBLE \
    cout<<"IMPOSSIBLE\n",exit(0)
vector<vector<int>> G,CG;
vector<int> vis,D,F,T;
void dfs(int u){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:G[u])
        CG[u].push_back(i),dfs(i),++T[i];
}
void topsort(int u){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:CG[u]){
        if(D[u]+1>D[i]) D[i]=D[u]+1,F[i]=u;
        if(!(--T[i])) topsort(i);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    D.resize(n+1);F.resize(n+1);
    vis.resize(n+1);G.resize(n+1);
    T.resize(n+1);CG.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    dfs(1);
    if(!T[n]) IMPOSSIBLE;
    fill(vis.begin(),vis.end(),false);
    topsort(1);cout<<D[n]+1<<'\n';
    function<void(int)> print=[&](int u){
        if(u==1){cout<<1<<' ';return;}
        auto call=[&](){print(F[u]);};call();
        cout<<u<<' ';
    };
    print(n);cout<<'\n';
    return 0;
}