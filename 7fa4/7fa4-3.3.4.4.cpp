#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
vector<vector<multiset<lint>>> G;
vector<int> F;
// Θ(n²) dijkstra,最多用 Θ(n) 次
vector<lint> dijkstra(int u){
    vector<lint> D(G.size(),_inf),vis(G.size());
    const int n=G.size()-1;
    F.clear();F.resize(n+1);
    D[u]=0;
    cir(i,0,n){
        int u=0;lint w=_inf;
        cir(j,1,n+1) if(!vis[j]&&D[j]<w) u=j,w=D[j];
        vis[u]=true;
        cir(j,1,n+1) if(!vis[j]&&!G[u][j].empty()){
            if(D[j]>w+(*G[u][j].begin()))
                D[j]=w+(*G[u][j].begin()),F[j]=u;
        }
    }
    return D;
}
vector<vector<lint>> D;
//Floyd 板子
void floyd(int n){
    cir(i,1,n+1) cir(j,1,n+1)
        D[i][j]=(!G[i][j].empty()?(*G[i][j].begin()):_inf);
    cir(i,1,n+1) D[i][i]=0;
    cir(k,1,n+1) cir(i,1,n+1) cir(j,1,n+1)
        D[i][j]=min(D[i][j],D[i][k]+D[k][j]);
}
set<pair<int,int>> ol;
//一直向 F 找最短路，dij 暴力更新没问题
void runol(int u,int t){
    while(u!=t){
        if(!F[u]) break;
        ol.insert({F[u],u});u=F[u];
    }
}
//在最短路上时的更改：跑 dijkstra
lint change_on_line(int s,int t,int u,int v,lint w){
    auto&uv=G[u][v],&vu=G[v][u];
    uv.erase(uv.find(w));vu.insert(w);
    auto D1=dijkstra(s),D2=dijkstra(t);
    uv.insert(w);vu.erase(vu.find(w));
    return D1[t]+D2[s];
}
//不在最短路的更改：Θ(1)
lint change_off_line(int s,int t,int u,int v,lint w){
    auto disu=D[s][t],disv=D[t][s];
    return min({disv+D[s][v]+D[u][t]+w,disu+D[t][v]
        +D[u][s]+w,D[u][t]+D[s][v]+D[t][v]+D[u][s]+w*2});
}
struct edge_t{int u,v;lint w,d;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    G.assign(n+1,vector<multiset<lint>>(n+1));
    D.assign(n+1,vector<lint>(n+1));
    vector<edge_t> ve(m);
    for(auto&[u,v,w,d]:ve)
        cin>>u>>v>>w>>d,G[u][v].insert(w);
    auto D1=dijkstra(1);runol(n,1);
    auto D2=dijkstra(n);runol(1,n);
    floyd(n);
    lint ans=D1[n]+D2[1];
    for(auto&[u,v,w,d]:ve){
        if(ol.count({u,v})){
            ans=min(ans,change_on_line(1,n,u,v,w)+d);
        }else{
            ans=min(ans,change_off_line(1,n,u,v,w)+d);
        }
    }
    cout<<(ans>=_inf?-1:ans)<<'\n';
    return 0;
}