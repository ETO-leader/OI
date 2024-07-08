#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
struct HeapNode{
    int v;lint w;
    inline bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
const lint _inf=1e18+7;
vector<lint> dijkstra(int u=1){
    priority_queue<HeapNode> pq;
    vector<lint> D(G.size(),_inf),vis(G.size());
    pq.push({u,0});D[u]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.v]) continue;
        vis[f.v]=true;
        for(auto&i:G[f.v]){
            if(!vis[i.v]&&D[i.v]>f.w+i.w){
                D[i.v]=f.w+i.w;pq.push({i.v,D[i.v]});
            }
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    auto D=dijkstra(1);
    cir(i,1,n+1) cout<<D[i]<<' ';
    cout<<'\n';
    return 0;
}