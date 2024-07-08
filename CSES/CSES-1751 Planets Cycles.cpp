#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> F,vis,siz;
void resiz(int u,int sz){
    siz[u]=sz;
    if(vis[u]!=2) resiz(F[u],sz);
}
int dfs(int u){
    if(siz[u]) return siz[u]+1;
    if(vis[u]==-1){vis[u]=2;return 1;}
    vis[u]=-1;
    auto d=dfs(F[u]);
    if(vis[u]==2) resiz(F[u],d);
    vis[u]=1;siz[u]=d;
    return d+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;siz.resize(n+1);
    F.resize(n+1);vis.resize(n+1);
    cir(i,1,n+1) cin>>F[i];
    dfs(1);
    cir(i,1,n+1) if(!vis[i]) dfs(i);
    cir(i,1,n+1) cout<<siz[i]<<' ';
    cout<<'\n';
    return 0;
}