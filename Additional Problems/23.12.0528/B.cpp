#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
VI dfn,scc,low;
class dsu{
private:
    VI f;
public:
    int findset(int x){
        return f[x]==x?x:(f[x]=findset(f[x]));
    }
    void merge(int x,int y){
        f[findset(x)]=findset(y);}
    dsu(int x):f(x){
        iota(f.begin(),f.end(),0);}
};
struct edge{int v,id,imp;size_t rev;};
vector<vector<edge>> G;
void tarjan(int u,int f,int&dc){
    dfn[u]=low[u]=++dc;
    for(auto&[v,id,imp,r]:G[u]){
        if(id==f) continue;
        if(!dfn[v]){
            tarjan(v,id,dc);
            if(dfn[u]<low[v])
                imp=(G[v][r].imp)=true;
            low[u]=min(low[u],low[v]);
        }else{
            low[u]=min(low[u],dfn[v]);
        }
    }
}
void dfs(int u,int nodeid){
    scc[u]=nodeid;
    for(auto&[v,id,imp,r]:G[u]){
        if(imp||scc[v]) continue;
        dfs(v,nodeid);
    }
}
vector<VI> T,upx;
VI up,dw,hx,treeid;
int ht;
void abort(int exitcode){
    cout<<"No\n";exit(exitcode);
}
void redfs(int u,int tid,int f=0){
    upx[u][0]=f;hx[u]=hx[f]+1;treeid[u]=tid;
    cir(i,1,ht) upx[u][i]=upx[upx[u][i-1]][i-1];
    for(auto&i:T[u]) if(i!=f) redfs(i,tid,u);
}
int lca(int u,int v){
    if(u==v) return u;
    if(hx[u]<hx[v]) swap(u,v);
    cir(i,0,ht) if((1<<i)&(hx[u]-hx[v])) u=upx[u][i];
    if(u==v) return u;
    for(int i=ht-1;~i;--i) if(upx[u][i]!=upx[v][i])
        u=upx[u][i],v=upx[v][i];
    return upx[u][0];
}
void addqry(int s,int t){
    int l=lca(s,t);
    dw[s]++,dw[l]--;
    up[t]++,up[l]--;
}
pair<int,int> chkstate(int u,int f=0){
    int dx=dw[u],ux=up[u];
    for(auto&i:T[u]) if(i!=f){
        auto [_d,_u]=chkstate(i,u);
        dx+=_d;ux+=_u;
    }
    if(ux&&dx) abort(0);
    return {dx,ux};
}
void resize_all(int n){
    G.resize(n+1);dfn.resize(n+1);
    scc.resize(n+1);low.resize(n+1);
}
void resize_tree(int n){
    T.resize(n+1);up.resize(n+1);
    dw.resize(n+1);ht=log2(n)+2;hx.resize(n+1);
    upx.assign(n+1,VI(ht));treeid.resize(n+1);
}
struct edge_t{int u,v;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    vector<edge_t> E(m);
    resize_all(n);
    cir(i,0,m){
        auto&[u,v]=E[i];cin>>u>>v;
        G[u].push_back({v,i,false,G[v].size()});
        G[v].push_back({u,i,false,G[u].size()-1});
    }
    int scccnt=0,cnx=0;
    cir(i,1,n+1) if(!dfn[i]) tarjan(i,-1,scccnt);
    cir(i,1,n+1) if(!scc[i]) dfs(i,++cnx);
    resize_tree(cnx);
    dsu ds(cnx+1);
    for(auto&[u,v]:E){
        u=scc[u],v=scc[v];
        if(ds.findset(u)==ds.findset(v)) continue;
        ds.merge(u,v);
        T[u].push_back(v);T[v].push_back(u);
    }
    cir(i,1,cnx) if(!treeid[i]) redfs(i,i);
    cir(i,0,q){
        int u,v;cin>>u>>v;
        u=scc[u];v=scc[v];
        if(treeid[u]!=treeid[v]) abort(0);
        addqry(u,v);
    }
    chkstate(1);
    cout<<"Yes\n";
    return 0;
}
