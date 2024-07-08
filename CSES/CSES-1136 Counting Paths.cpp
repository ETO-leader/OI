#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct graph_tree{
    vector<vector<int>> UP,G;
    vector<T> tags,A;vector<int> H;int HT;
    graph_tree(int n):HT(log2(n)+2){
        UP.assign(n+1,vector<int>(HT));
        G.resize(n+1);H.resize(n+1);
        tags.resize(n+1);A.resize(n+1);
    }
    void init(int u,int f=0){
        UP[u][0]=f;H[u]=H[f]+1;
        cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
        for(auto&i:G[u]) if(i!=f) init(i,u);
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
    void add_path(int u,int v,T w){
        auto l=lca(u,v);
        tags[u]+=w,tags[v]+=w;
        tags[l]-=w,tags[UP[l][0]]-=w;
    }
    int dfs(int u,int f=0){
        A[u]=tags[u];
        for(auto&i:G[u]) if(i!=f) A[u]+=dfs(i,u);
        return A[u];
    }
    void add_edge(int u,int v){
        G[u].push_back(v),G[v].push_back(u);
    }
};
template<typename T>
ostream&operator<<(ostream&os,graph_tree<T>&g){
    cir(i,1,g.A.size()) os<<g.A[i]<<' ';
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;graph_tree<int> G(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;G.add_edge(u,v);
    }
    G.init(1);
    cir(i,0,m){
        int u,v;cin>>u>>v;G.add_path(u,v,1);
    }
    G.dfs(1);cout<<G<<'\n';
    return 0;
}