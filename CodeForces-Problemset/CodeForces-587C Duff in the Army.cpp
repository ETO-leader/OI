#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> G,p,up;
vector<vector<VI>> up_t;
VI h;int ht;
VI&mrg(VI&a,VI&b){
    for(auto&i:b) a.push_back(i);
    sort(a.begin(),a.end());
    while(a.size()>10) a.pop_back();
    return a;
}
void make_up_t(int u,int i){
    up[u][i]=up[up[u][i-1]][i-1];
    up_t[u][i]=up_t[up[u][i-1]][i-1];
    mrg(up_t[u][i],up_t[u][i-1]);
}
void dfs(int u,int f=0){
    up[u][0]=f;h[u]=h[f]+1;
    mrg(up_t[u][0],p[f]);
    cir(i,1,ht+1) make_up_t(u,i);
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
auto lca(int u,int v){
    VI res;
    if(u==v) return p[u];
    if(h[v]>h[u]) swap(u,v);
    res=p[u];
    cir(i,0,ht+1) if((h[u]-h[v])&(1<<i)){
        mrg(res,up_t[u][i]);u=up[u][i];
    }
    if(u==v) return res;
    mrg(res,p[v]);
    for(int i=ht;~i;--i) if(up[u][i]!=up[v][i]){
        mrg(res,up_t[u][i]);mrg(res,up_t[v][i]);
        u=up[u][i];v=up[v][i];
    }
    return mrg(res,up_t[u][0]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;G.resize(n+1);
    p.resize(n+1);h.resize(n+1);
    ht=log2(n)+2;up.assign(n+1,VI(ht+1));
    up_t.assign(n+1,vector<VI>(ht+1));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,0,m){
        int ci;cin>>ci;
        p[ci].push_back(i+1);
    }
    cir(i,1,n+1) mrg(p[i],p[0]);
    dfs(1);
    cir(i,0,q){
        int u,v,a;cin>>u>>v>>a;
        auto lx=lca(u,v);
        cout<<min<int>(lx.size(),a)<<' ';
        cir(i,0,min<int>(lx.size(),a))
            cout<<lx[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
