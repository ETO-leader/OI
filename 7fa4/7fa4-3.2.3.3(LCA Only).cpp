#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
vector<vector<int>> UP,MxV;
int HT;vector<lint> Hx,H,V;
void dfs(int u,lint w=0,int f=0){
    UP[u][0]=f;MxV[u][0]=max(V[u],V[f]);H[u]=H[f]+1;Hx[u]=Hx[f]+w;
    cir(i,1,HT+1) (UP[u][i]=UP[UP[u][i-1]][i-1]),
        (MxV[u][i]=max(MxV[u][i-1],MxV[UP[u][i-1]][i-1]));
    for(auto&i:G[u]) if(i.v!=f) dfs(i.v,i.w,u);
}
pair<int,int> lca(int u,int v){
    int mx=max(V[u],V[v]);if(u==v) return {u,0};
    if(H[u]<H[v]) swap(u,v);
    for(int i=HT;~i;--i) if(H[UP[u][i]]>=H[v])
        u=UP[u][i],mx=max(mx,MxV[u][i]);
    if(u==v) return {u,mx};
    for(int i=HT;~i;--i) if(UP[u][i]!=UP[v][i])
        u=UP[u][i],v=UP[v][i],mx=max({mx,MxV[u][i],MxV[v][i]});
    return {UP[u][0],max({mx,MxV[u][0],MxV[v][0]})};
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;HT=log2(n)+2;
    UP.assign(n+1,vector<int>(HT+1));
    MxV.assign(n+1,vector<int>(HT+1));
    G.resize(n+1);H.resize(n+1);Hx.resize(n+1);
    V.resize(n+1);
    cir(i,1,n+1) cin>>V[i];
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    dfs(1);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        auto l=lca(u,v);lint a=Hx[u]+Hx[v]-2*Hx[l.first];
        cout<<a<<' '<<l.second<<'\n';
    }
    return 0;
}