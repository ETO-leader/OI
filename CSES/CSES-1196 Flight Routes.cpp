#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
struct HeapNode{
    int u;lint w;
    bool operator<(const HeapNode&gp) const{
        return w>gp.w;
    }
};
vector<vector<lint>> solve(int k){
    vector<vector<lint>> D(G.size());
    priority_queue<HeapNode> pq;
    pq.push({1,0});
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(D[f.u].size()>=k) continue;
        D[f.u].push_back(f.w);
        for(auto&i:G[f.u]){
            if(D[i.v].size()<k) pq.push({i.v,f.w+i.w});
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;G.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    auto Ans=solve(k);
    for(auto&i:Ans[n]) cout<<i<<' ';
    cout<<'\n';
    return 0;
}