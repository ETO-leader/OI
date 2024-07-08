#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using lint=long long;
static constexpr auto ups=21;
struct edge{int v;lint w;};
struct qedge{int v,forms;};
vector<vector<edge>> gr;
vector<VI> up;
vector<vector<qedge>> tr;
VI hx,fx,use,siz,cx;
vector<lint> wx,dsiz,fsiz;
auto dfs(int u,int f=0)->void{
    hx[u]=hx[f]+1;up[u][0]=f;
    cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
    for(auto&[v,w]:gr[u]) if(v!=f){
        wx[v]=wx[u]+w;dfs(v,u);
    }
}
auto lca(int u,int v){
    if(hx[u]<hx[v]) swap(u,v);
    cir(i,0,ups) if((hx[u]-hx[v])&(1<<i))
        u=up[u][i];
    if(u==v) return u;
    for(int i=ups-1;~i;--i) if(up[u][i]!=up[v][i])
        u=up[u][i],v=up[v][i];
    return up[u][0];
}
auto dfssz(int u,int f=0){
    if(use[u]) return siz[u]=0;
    siz[u]=1;
    for(auto&[v,w]:gr[u]) if(v!=f) siz[u]+=dfssz(v,u);
    return siz[u];
}
auto dfsrt(int u,const int sizu,int f=0){
    auto res=0,lst=sizu-1,mx=0;
    if(use[u]) return res;
    for(auto&[v,w]:gr[u]) if(v!=f){
        res|=dfsrt(v,sizu,u);
        mx=max(mx,siz[v]);lst-=siz[v];
    }
    if(max(mx,lst)<sizu/2+1) return u;
    return res;
}
auto build(int u,int f=0)->int{
    auto sizu=dfssz(u);
    auto rtu=dfsrt(u,sizu);
    use[rtu]=true;fx[rtu]=f;
    tr[f].push_back({rtu,u});
    for(auto&[v,w]:gr[rtu]) if(!use[v]) build(v,rtu);
    return rtu;
}
auto dist(int u,int v){
    return wx[u]+wx[v]-wx[lca(u,v)]*2;
}
auto update(int u,lint w){
    const auto fr=u;auto lasu=0;
    while(u){
        dsiz[u]+=w*dist(fr,u);
        cx[u]+=w;
        if(lasu) fsiz[lasu]+=w*dist(fr,u);
        lasu=u;u=fx[u];
    }
}
auto calc(int u){
    const auto fr=u;
    auto lasu=u;auto res=dsiz[u];
    while(u=fx[u]){
        res+=dsiz[u]-fsiz[lasu];
        res+=dist(u,fr)*(cx[u]-cx[lasu]);
        lasu=u;
    }
    return res;
}
auto query(int u)->lint{
    auto res=calc(u);
    for(auto&[nxt,fru]:tr[u]){
        if(calc(fru)<res) return query(nxt);
    }
    return res;
}
auto init(int n){
    gr.resize(n+1);tr.resize(n+1);
    up.assign(n+1,VI(ups));dsiz.resize(n+1);
    fsiz.resize(n+1);wx.resize(n+1);cx.resize(n+1);
    siz.resize(n+1);use.resize(n+1);fx.resize(n+1);
    hx.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;init(n);
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;
        gr[u].push_back({v,w});
        gr[v].push_back({u,w});
    }
    dfs(1);
    const auto rt=build(1);
    cir(i,0,q){
        int u;lint w;cin>>u>>w;
        update(u,w);
        cout<<query(rt)<<'\n';
    }
    return 0;
}
