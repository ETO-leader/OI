#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define CIRCLE {cout<<(++cnt)<<'\n'<<u;\
    for(auto&j:A) cout<<' '<<j;\
    cout<<'\n';exit(0);}
using namespace std;
vector<vector<int>> G;
vector<int> vis;
deque<int> A;int cnt;
bool dfs(int u){
    if(vis[u]==1) return false;
    if(vis[u]==-1){
        vis[u]=2;A.push_front(u),++cnt;
        return true;
    }
    vis[u]=-1;
    for(auto&i:G[u]) if(dfs(i)){
        if(vis[u]==2) CIRCLE;
        ++cnt;A.push_front(u);return true;
    }
    return vis[u]=1,false;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    G.resize(n+1);vis.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    cir(i,1,n+1) if(!vis[i]) dfs(i);
    cout<<"IMPOSSIBLE\n";
    return 0;
}