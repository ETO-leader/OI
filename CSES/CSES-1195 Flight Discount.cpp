#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
struct HeapNode{
    int v,tp;lint w;
    inline bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
using VL=vector<lint>;
const lint _inf=1e18+7;
VL dijkstra(int u){
    priority_queue<HeapNode> pq;
    vector<VL> D(2,VL(G.size(),_inf)),vis(2,VL(G.size()));
    pq.push({u,0,0});pq.push({u,1,0});
    D[0][u]=D[1][u]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.tp][f.v]) continue;
        vis[f.tp][f.v]=true;
        for(auto&i:G[f.v]){
            if(!f.tp&&!vis[0][i.v]&&D[0][i.v]>i.w+f.w)
                D[0][i.v]=i.w+f.w,pq.push({i.v,0,i.w+f.w});
            auto use=i.w/(1+!f.tp);
            if(!vis[1][i.v]&&D[1][i.v]>f.w+use)
                D[1][i.v]=f.w+use,pq.push({i.v,1,f.w+use});
        }
    }
    return D[1];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    auto D=dijkstra(1);
    cout<<D[n]<<'\n';
    return 0;
}