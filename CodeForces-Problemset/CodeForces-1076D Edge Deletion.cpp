#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v,id;lint w;};
vector<vector<edge>> G;
struct HeapNode{
    int v;lint w;
    bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
set<int> ont;
const lint _inf=1e18+7;
//dijkstra 建立最短路树
void dijkstra(int n){
    priority_queue<HeapNode> pq;
    pq.push({1,0});
    vector<lint> D(n+1,_inf),vis(n+1);
    D[1]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.v]) continue;
        vis[f.v]=true;
        bool tagx=false;
        for(auto&i:G[f.v]){
            if(D[i.v]+i.w==D[f.v]&&(!tagx))
                ont.insert(i.id),tagx=true;
            if(!vis[i.v]&&f.w+i.w<D[i.v])
                D[i.v]=f.w+i.w,pq.push({i.v,f.w+i.w});
        }
    }
}
vector<vector<pair<int,int>>> Tr;
struct edge_t{int u,v;lint w;};
priority_queue<pair<int,int>,vector<pair<int,int>>
    ,greater<pair<int,int>>> pq;
//求出最短路树深度
void dfs(int u,int h=0,int f=0){
    for(auto&i:Tr[u]) if(i.first!=f)
        pq.emplace(h+1,i.second),dfs(i.first,h+1,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<edge_t> ve(m);
    G.resize(n+1);Tr.resize(n+1);
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({v,i,w});
        G[v].push_back({u,i,w});
        ve[i]={u,v,w};
    }
    dijkstra(n);
    for(auto i:ont){
        auto&x=ve[i];
        Tr[x.u].push_back({x.v,i});
        Tr[x.v].push_back({x.u,i});
    }
    dfs(1);
    int rx=min(k,n-1);
    stringstream ss;
    //保留最短路树即可
    cir(i,0,rx){
        ss<<pq.top().second+1<<' ';pq.pop();
    }
    cout<<rx<<'\n'<<ss.str()<<'\n';
    return 0;
}
