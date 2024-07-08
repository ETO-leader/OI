#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct item{int id,w;};
using lint=long long;
vector<vector<int>> G,UP;
struct quary{int tp;lint x;};
vector<list<quary>> T;
vector<list<item>> qr;
vector<int> H;
vector<lint> ans;
int HT;
void dfs(int u,int f=0){
    UP[0][u]=f;H[u]=H[f]+1;
    cir(i,1,HT+1) UP[i][u]=UP[i-1][UP[i-1][u]];
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int lca(int u,int v){
    if(u==v) return u;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v])) u=UP[i][u];
    if(u==v) return u;
    for(int i=HT;~i;--i) if(UP[i][u]!=UP[i][v])
        u=UP[i][u],v=UP[i][v];
    return UP[0][u];
}
void ins(vector<lint>&v,quary&q){v[q.tp]+=q.x;}
void insert(int u,quary q){
    T[u].push_back(q);}
void build_tag(int u,int v,int tp,lint x){
    auto l=lca(u,v);insert(UP[0][l],{tp,-x});
    insert(u,{tp,x});insert(v,{tp,x});insert(l,{tp,-x});
}
void redfs(int u,int f,vector<lint>&vx){
    list<lint> lst;
    for(auto&i:qr[u]) lst.push_back(vx[i.w]);
    for(auto&i:T[u]) ins(vx,i);
    for(auto&i:G[u]) if(i!=f) redfs(i,u,vx);
    auto it=qr[u].begin();
    for(auto&i:lst) ans[it->id]=vx[it->w]-i,++it;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k,q;cin>>n>>m>>k>>q;
    G.resize(n+1);T.resize(n*2+1);HT=log2(n)+2;
    UP.assign(HT+1,vector<int>(n+1));
    T.resize(n+1);H.resize(n+1);ans.resize(q);
    qr.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);
    cir(i,0,m){
        int u,v,tp;lint w;cin>>u>>v>>tp>>w;
        build_tag(u,v,tp,w);
    }
    vector<lint> bx(k+1);
    cir(i,0,q){
        int u,tp;cin>>u>>tp;
        qr[u].push_back({i,tp});
    }
    redfs(1,0,bx);
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}