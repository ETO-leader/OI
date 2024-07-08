#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,w;};
struct Nodes{
    int u,v;
    bool operator<(const Nodes&nd) const{
        return v==nd.v?u>nd.u:v>nd.v;
    }
};
template<typename T>
using graph=vector<vector<T>>;
graph<edge> G;
set<int> imp;
const int _inf=1e9+7;
pair<graph<int>,vector<int>> dijkstra(int u){
    int n=G.size();vector<int> D(n,_inf),tops(n);
    vector<bool> vis(n);
    graph<int> Gr(n);priority_queue<Nodes> pq;
    pq.push({u,0});D[u]=0;vis[0]=true;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(f.v>D[f.u]||vis[f.u]) continue;
        vis[f.u]=true;
        for(auto&i:G[f.u]){
            if(D[i.v]>f.v+i.w){
                D[i.v]=f.v+i.w;pq.push({i.v,f.v+i.w});
            }
            if(D[i.v]+i.w==D[f.u]) Gr[i.v].push_back(f.u),tops[f.u]++;
        }
    }
    return make_pair(Gr,tops);
}
void run(int s,int u,pair<graph<int>,vector<int>>&Gr){
    for(auto&i:Gr.first[u]){
        run(s,i,Gr);
        if(Gr.second[i]<=1&&u!=s) imp.insert(u);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    cir(i,1,n+1){auto dij=dijkstra(i);run(i,i,dij);}
    for(auto&i:imp) cout<<i<<' ';
    cout<<(imp.empty()?"No important cities.":"")<<'\n';
    return 0;
}