#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
struct heapnode{
    int u;lint w;
    bool operator<(const heapnode&hp) const{
        return w>hp.w;}
};
struct edge{int v;lint w;};
vector<vector<edge>> G;
VI wx;
bool dijkstra(int x,int y,int v,lint mxw){
    if(mxw<wx[x]) return false;
    vector<lint> D(G.size(),_inf),vis(G.size());
    priority_queue<heapnode> pq;
    pq.push({x,0});
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.u]) continue;
        vis[f.u]=true;
        for(auto&i:G[f.u]){
            if(vis[i.v]||f.w+i.w>=D[i.v]||
                wx[i.v]>mxw) continue;
            pq.push({i.v,f.w+i.w});
            D[i.v]=f.w+i.w;
        }
    }
    return vis[y]&&D[y]<=v;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,v;cin>>n>>m>>v;
    G.resize(n+1);wx.resize(n+1);
    cir(i,1,n+1) cin>>wx[i];
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    lint l=0,r=1145141919810LL,ans=-1;
    while(r>=l){
        lint mid=(l+r)/2;
        dijkstra(1,n,v,mid)?
            ((ans=mid),(r=mid-1)):(l=mid+1);
    }
    if(ans==-1) cout<<"AFK\n";
    else cout<<ans<<'\n';
    return 0;
}
