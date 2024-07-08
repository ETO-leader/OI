#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto ups=21;
struct edge{int v;lint w;};
vector<vector<edge>> G;
vector<vector<int>> up;
vector<basic_string<int>> tsiz;
vector<int> h,siz,use,fx,rks;
vector<lint> val;
auto dfs(int u,int f=0)->void{
    h[u]=h[f]+1;up[0][u]=f;
    cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
    for(auto&[v,w]:G[u]) if(v!=f) val[v]=val[u]+w,dfs(v,u);
}
auto lca(int u,int v){
    if(h[u]<h[v]) swap(u,v);
    cir(i,0,ups) if((h[u]-h[v])&(1<<i))
        u=up[i][u];
    if(u==v) return u;
    for(int i=ups-1;~i;--i) if(up[i][u]!=up[i][v])
        u=up[i][u],v=up[i][v];
    return up[0][u];
}
auto dfssz(int u,int f=0){
    if(use[u]) return siz[u]=0;
    siz[u]=1;
    for(auto&[v,w]:G[u]) if(v!=f) siz[u]+=dfssz(v,u);
    return siz[u];
}
auto dfsrt(int u,const int sizu,int f=0)->int{
    int res=0,frf=sizu-1,mx=0;
    for(auto&[v,w]:G[u]) if(v!=f&&(!use[v])){
        res|=dfsrt(v,sizu,u);
        frf-=siz[v];mx=max(mx,siz[v]);
    }
    if(max(frf,mx)<sizu/2+1) return u;
    return res;
}
auto build(int u,int f=0)->basic_string<int>{
    auto sizx=dfssz(u);
    auto rtu=dfsrt(u,sizx);
    use[rtu]=true;fx[rtu]=f;
    tsiz[rtu].push_back(rks[rtu]);
    for(auto&[v,w]:G[rtu]) if(!use[v]) tsiz[rtu]+=build(v,rtu);
    sort(tsiz[rtu].begin(),tsiz[rtu].end());
    return tsiz[rtu];
}
auto dist(int u,int v){
    return val[u]+val[v]-val[lca(u,v)]*2;
}
struct qry{
    int rk;lint w;
    bool operator<(const qry&q) const{
        return rk<q.rk;
    }
    qry(int _rk,lint _w):rk(_rk),w(_w){}
};
using vqs=vector<qry>;
auto update(int u,vector<vqs>&sga,vector<vqs>&sgb){
    const auto fr=u;
    auto lasu=0;
    while(u){
        sga[u].push_back({rks[fr],dist(fr,u)});
        if(lasu) sgb[lasu].push_back({rks[fr],dist(fr,u)});
        lasu=u;u=fx[u];
    }
}
auto query(vqs&a,int mxk){
    auto upb=lower_bound(a.begin(),a.end(),qry(mxk+1,-1));
    if(upb==a.begin()) return (lint)(0);
    return prev(upb)->w;
}
auto query(int u,int mxk,int mnk,vector<vqs>&sga,vector<vqs>&sgb){
    const auto fr=u;
    auto lasu=0;lint res=0;
    while(u){
        const auto rka=upper_bound(tsiz[u].begin(),
            tsiz[u].end(),mxk)-upper_bound(tsiz[u].begin(),
            tsiz[u].end(),mnk);
        const auto rkb=upper_bound(tsiz[lasu].begin(),
            tsiz[lasu].end(),mxk)-upper_bound(tsiz[lasu].begin(),
            tsiz[lasu].end(),mnk);
        res+=(query(sga[u],mxk)-query(sga[u],mnk)-
            query(sgb[lasu],mxk)+query(sgb[lasu],mnk))+
            (rka-rkb)*dist(fr,u);
        lasu=u;u=fx[u];
    }
    return res;
}
auto init(int n){
    up.assign(ups,vector<int>(n+1));G.resize(n+1);
    h.resize(n+1);siz.resize(n+1);use.resize(n+1);
    val.resize(n+1);fx.resize(n+1);
    rks.resize(n+1);tsiz.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,mxa;cin>>n>>q>>mxa;init(n);
    cir(i,1,n+1) cin>>rks[i];
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    dfs(1);build(1);
    vector<vqs> sga(n+1),sgb(n+1);
    cir(i,1,n+1) update(i,sga,sgb);
    for(auto&i:sga) sort(i.begin(),i.end());
    for(auto&i:sga) cir(p,1,(int)(i.size()))
        i[p].w+=i[p-1].w;
    for(auto&i:sgb) sort(i.begin(),i.end());
    for(auto&i:sgb) cir(p,1,(int)(i.size()))
        i[p].w+=i[p-1].w;
    lint lastans=0;
    cir(i,0,q){
        int u,a,b;cin>>u>>a>>b;
        const auto l=min((a+lastans)%mxa,(b+lastans)%mxa);
        const auto r=max((a+lastans)%mxa,(b+lastans)%mxa);
        cout<<(lastans=query(u,r,l-1,sga,sgb))<<'\n';
    }
    return 0;
}
