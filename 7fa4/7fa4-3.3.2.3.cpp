#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int u,w;};
vector<vector<edge>> G;
vector<vector<int>> UP;
vector<int> H;int HT;
const int _inf=1e9+7;
void dfs(int u,int w=0,int f=0){
    H[u]=H[f]+1;UP[u][0]=f;
    cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
    for(auto&i:G[u]) if(i.u!=f) dfs(i.u,i.w,u);
}
int lca(int u,int v){
    if(u==v) return u;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v])) u=UP[u][i];
    if(u==v) return u;
    for(int i=HT;~i;--i) if(UP[u][i]!=UP[v][i])
        u=UP[u][i],v=UP[v][i];
    return UP[u][0];
}
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
};
struct edge_t{int u,v,w,id;};
using lint=long long;
lint inx(vector<edge_t>&ve,dsu<int>&ds,
    vector<edge_t>&Gr,vector<bool>&ol,
    map<pair<int,int>,int>&es){
    lint cntx=0;
    for(auto&i:ve){
        if(ds.findset(i.u)==ds.findset(i.v)){
            Gr.push_back(i);continue;}
        ds.merge(i.u,i.v);
        G[i.u].push_back({i.v,i.w});
        G[i.v].push_back({i.u,i.w});
        cntx+=i.w;ol[i.id]=true;
        es[{i.u,i.v}]=i.id;
        es[{i.v,i.u}]=i.id;
    }
    return cntx;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    H.resize(n+1);dsu<int> ds(n+1);
    vector<edge_t> ve(m);
    HT=log2(n)+2;UP.assign(n+1,vector<int>(HT+1));
    map<pair<int,int>,int> es;
    int cnt=0;
    for(auto&i:ve) cin>>i.u>>i.v>>i.w,i.id=cnt++;
    auto vx=ve;
    sort(ve.begin(),ve.end(),
        [](edge_t&a,edge_t&b){return a.w<b.w;});
    vector<bool> ol(cnt);
    vector<lint> ans(m);
    vector<edge_t> Gr;
    lint cntx=inx(ve,ds,Gr,ol,es);
    dfs(1);
    dsu<int> du(n+1);
    function<void(int,int,int)> lcmx=[&](int x,int l,int rx){
        if(H[x]<=H[l]) return;
        if(H[du.findset(x)]<=H[l]) return;
        x=du.findset(x);
        ans[es[{x,UP[x][0]}]]=rx;
        du.merge(x,UP[x][0]);
        [&](int _x,int _l,int _rx){lcmx(_x,_l,_rx);}(x,l,rx);
    };
    sort(Gr.begin(),Gr.end(),
        [](edge_t&a,edge_t&b){return a.w<b.w;});
    for(auto&i:Gr){
        auto l=lca(i.u,i.v);
        lcmx(i.u,l,i.w);lcmx(i.v,l,i.w);
    }
    for(auto&i:vx){
        if(!ol[i.id]) cout<<cntx<<'\n';
        else if(ans[i.id])
            cout<<cntx-i.w+ans[i.id]<<'\n';
        else cout<<"inf\n"; 
    }
    return 0;
}
