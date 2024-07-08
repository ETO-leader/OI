#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
struct qnode{int u,w;};
int bfs(int s,int mxw){
    queue<qnode> q;q.push({s,0});
    unordered_set<int> vis;
    int res=0;
    while(!q.empty()&&q.front().w<=mxw){
        auto [u,w]=q.front();q.pop();
        if(vis.count(u)) continue;
        vis.insert(u);res+=u;
        for(auto&i:G[u]) q.push({i,w+1});
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    int q;cin>>q;
    while(q--){
        int u,w;cin>>u>>w;
        cout<<bfs(u,w)<<'\n';
    }
    return 0;
}
