#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<int>> G,up;
vector<int> h,fc,tg;int ht;
class dsu{
private:
    vector<int> fx;
public:
    int jump(int u,int hx){
        if(h[u]<h[hx]) return u;
        if(fx[u]==u) fx[u]=fc[u];
        tg[u]=true;
        return fx[u]=jump(fx[u],hx);
    }
    void resize(int _n){(*this)=dsu(_n);}
    dsu(int _n=0):fx(_n){
        iota(fx.begin(),fx.end(),0);}
};
void dfs(int u,int f=0){
    fc[u]=f;up[0][u]=f;h[u]=h[f]+1;
    cir(i,1,ht) up[i][u]=up[i-1][up[i-1][u]];
	for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int lca(int u,int v){
    if(u==v) return u;
    if(h[u]<h[v]) swap(u,v);
    cir(i,0,ht) if((1<<i)&(h[u]-h[v])) u=up[i][u];
    if(u==v) return u;
    for(int i=ht-1;~i;--i) if(up[i][u]!=up[i][v])
        u=up[i][u],v=up[i][v];
    return up[0][u];
}
queue<int> pq;dsu ds;
void run(int u,lint&ans){
    while(!pq.empty()&&tg[pq.front()]) pq.pop();
    if(pq.empty()) return;
    int v=pq.front();pq.pop();
    int l=lca(u,v);
    ds.jump(u,l);ds.jump(v,l);
    ans+=(h[u]+h[v]-h[l]*2);
    run(v,ans);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,p;cin>>n>>m>>p;
    G.resize(n+1);ht=log2(n)+2;
    up.assign(ht,vector<int>(n+1));
    h.resize(n+1);fc.resize(n+1);
    tg.resize(n+1);ds.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,0,m){
        int pi;cin>>pi;pq.push(pi);
    }
    lint ans=0;tg[p]=true;
    dfs(p);run(p,ans);
    cout<<ans<<'\n';
    return 0;
}
