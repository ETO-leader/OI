#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int _inf=1e9+7;
struct heapnode{
    int u,w;
    bool operator<(const heapnode&x) const{
        return w>x.w;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<VI> G(n+1);
    VI D(n+1,_inf),vis(n+1),deg(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;++deg[u];
        G[v].push_back(u);
    }
    priority_queue<heapnode> pq;
    pq.push({n,0});D[n]=0;
    while(!pq.empty()){
        auto[u,w]=pq.top();pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto&i:G[u]){
            const int wi=D[u]+deg[i]--;
            if(D[i]>wi) pq.push({i,(D[i]=wi)});
        }
    }
    cout<<D[1]<<'\n';
    return 0;
}
