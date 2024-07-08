#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
struct heapnode{
    int u,fr;lint w;
    bool operator<(const heapnode&x) const{
        return w>x.w;
    }
};
vector<vector<edge>> gr;
auto dijkstra(int c,int k){
    vector<int> cnt(gr.size());
    vector<lint> dist(gr.size());
    vector<unordered_set<int>> vis(gr.size());
    priority_queue<heapnode> pq;
    cir(i,1,c+1) pq.push({i,i,0});
    while(!pq.empty()){
        auto[u,fr,w]=pq.top();pq.pop();
        if(vis[u].count(fr)) continue;
        if((++cnt[u])>k) continue;
        dist[u]=w;vis[u].insert(fr);
        for(auto&[v,wx]:gr[u]) if(cnt[v]<k) if(v!=fr&&(!vis[v].count(fr))){
            pq.push({v,fr,w+wx});
        }
    }
    cir(i,1,(int)(gr.size())) if(cnt[i]<k)
        dist[i]=numeric_limits<lint>::max();
    return dist;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,c,r,k;cin>>n>>m>>c>>r>>k;
    gr.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        gr[u].push_back({v,w});
        gr[v].push_back({u,w});
    }
    auto dist=dijkstra(c,k);
    vector<int> ans;
    cir(i,c+1,n+1) if(dist[i]<r+1){
        ans.push_back(i);
    }
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
