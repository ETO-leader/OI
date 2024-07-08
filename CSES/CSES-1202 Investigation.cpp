#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define res(x) (x).resize(n+1)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
const int MOD=1e9+7;
vector<lint> S,L,C,Dx,vis,T;
struct edge{int v,w;};
vector<vector<edge>> G,CG;
template<typename T>
struct HeapNode{
    int v;T w;
    bool operator<(const HeapNode<T>&hp) const{
        return w>hp.w;
    }
};
void dijkstra(int u){
    priority_queue<HeapNode<lint>> pq;
    pq.push({u,0});Dx[u]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.v]) continue;
        vis[f.v]=true;
        for(auto&i:G[f.v]){
            if(vis[i.v]||i.w+f.w>=Dx[i.v]) continue;
            Dx[i.v]=i.w+f.w;pq.push({i.v,i.w+f.w});
        }
    }
}
void build(int n){
    cir(i,1,n+1) for(auto&j:G[i]){
        if(Dx[j.v]==Dx[i]+j.w) CG[i].push_back(j),T[j.v]++;
    }
}
void dp(int u){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:CG[u]){
        (C[i.v]+=C[u])%=MOD;S[i.v]=min(S[i.v],S[u]+1);
        L[i.v]=max(L[i.v],L[u]+1);
        if(!(--T[i.v])) dp(i.v);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;res(G);res(L);S.resize(n+1,_inf);
    res(vis);res(T);res(CG);res(C);Dx.resize(n+1,_inf);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    dijkstra(1);build(n);S[1]=0;C[1]=1;
    fill(vis.begin(),vis.end(),false);dp(1);
    cout<<Dx[n]<<' '<<C[n]<<' '<<S[n]<<' '<<L[n]<<'\n';
    return 0;
}