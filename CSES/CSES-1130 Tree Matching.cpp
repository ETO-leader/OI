#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<vector<int>> D;
const int _inf=1e9+7;
int dfs(int u,bool fach,int f=0){
    auto&d=D[u][fach];int mn=_inf;
    if(~d) return d;
    d=0;
    for(auto&i:G[u]) if(i!=f){
        auto dx=dfs(i,false,u);d+=dx;
        mn=min(mn,dx-dfs(i,true,u));
    }
    /*return*/ (d=max(d,(!fach?d-mn+1:0)));
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    D.assign(n+1,vector<int>(2,-1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    cout<<dfs(1,false)<<'\n';
    return 0;
}