#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
struct edge{int v,w;};
vector<vector<edge>> G;
struct heapnode{
    int u,w;
    bool operator<(const heapnode&hp) const{
        return w>hp.w;
    }
};
auto dijkstra(vector<heapnode> hp){
    vector<int> D(G.size(),_inf),vis(G.size());
    priority_queue<heapnode> pq;
    for(auto&[u,w]:hp) pq.push({u,w}),D[u]=w;
    while(!pq.empty()){
        auto [u,w]=pq.top();pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto&[v,wi]:G[u]){
            if(vis[v]||D[v]<=w+wi) continue;
            D[v]=w+wi;D[v]=w+wi;
            pq.push({v,w+wi});
        }
    }
    return D;
}
VI pid,idp;
int rundp(int n,int k){
    const int _sz=1<<k;
    vector<VI> D(_sz,VI(n,_inf)),chg(_sz);
    cir(i,0,k) D[1<<i][pid[i]-1]=0;
    cir(s,0,_sz){
        vector<heapnode> vx;
        cir(u,0,n){
            auto&d=D[s][u];
            for(int x=(s&(s-1));x;x=s&(x-1)){
                d=min(d,D[x][u]+D[s^x][u]);
            }
            if(d!=_inf) vx.push_back({u+1,D[s][u]});
        }
        D[s]=dijkstra(vx);D[s].erase(D[s].begin());
    }
    return [&](){
        int res=_inf;
        cir(i,0,k) res=min(res,D[_sz-1][i]);
        return res;
    }();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    G.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    pid.resize(k);idp.resize(n+1);
    vector<bool> isp(n+1);
    cir(i,0,k){
        int p;cin>>p;isp[p]=true;
        pid[i]=p;idp[p]=i;
    }
    cout<<rundp(n,k)<<'\n';
    return 0;
}