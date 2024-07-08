#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<int>> gr;
struct edge{int u,v;};
auto bfs(int s){
    queue<int> q;q.push(s);
    vector<int> dist(gr.size()),vis(gr.size());
    vis[s]=true;
    while(!q.empty()){
        auto u=q.front();q.pop();
        for(auto&i:gr[u]) if(!vis[i]){
            dist[i]=dist[u]+1;
            vis[i]=true;q.push(i);
        }
    }
    return dist;
}
auto check(int s,const vector<edge>&es){
    auto dist=bfs(s);
    for(const auto&[u,v]:es){
        if(abs(dist[u]-dist[v])!=1) return -1;
    }
    return*max_element(dist.begin(),dist.end())+1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    gr.resize(n);vector<edge> es;
    cir(i,0,n) cir(j,0,n){
        char x;cin>>x;
        if(x=='1'){
            gr[i].push_back(j);
            if(i<j) es.push_back({i,j});
        }
    }
    int ans=-1;
    cir(i,0,n) ans=max(ans,check(i,es));
    cout<<ans<<'\n';
    return 0;
}
