#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct graph{
    vector<vector<int>> G,UP;
    vector<T> Tin,Tout,Tag;int cnt,HT;
    graph(int n):HT(log2(n)+1),UP(n+1,vector<int>(log2(n)+2)),
        Tin(n+1),Tout(n+1),Tag(n+1),cnt(0),G(n+1){Tout[0]=2*n+20;}
    void dfs(int u,int f=0){
        Tin[u]=++cnt;UP[u][0]=f;
        cir(i,1,HT+1) UP[u][i]=UP[UP[u][i-1]][i-1];
        for(auto&i:G[u]) if(i!=f) dfs(i,u);
        Tout[u]=++cnt;
    }
    inline bool isfa(int u,int v){
        return Tin[u]<=Tin[v]&&Tout[v]<=Tout[u];
    }
    int lca(int u,int v){
        if(isfa(v,u)) return v;
        if(isfa(u,v)) return u;
        for(int i=HT;~i;--i) if(!isfa(UP[u][i],v)) u=UP[u][i];
        return UP[u][0];
    }
    void add(int u,int v,T w){
        int l=lca(u,v);
        Tag[l]-=w;Tag[UP[l][0]]-=w;
        Tag[u]+=w;Tag[v]+=w;
    }
    void insert(int u,int v){
        G[u].push_back(v),G[v].push_back(u);
    }
    T _dfs(int u,int f,vector<T>&ans){
        ans[u]=Tag[u];
        for(auto&i:G[u]) if(i!=f) ans[u]+=_dfs(i,u,ans);
        return ans[u];
    }
    vector<T> solve(){
        vector<T> ret(UP.size());_dfs(1,0,ret);
        return ret;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,Case=0;cin>>T;
    while(T--){
        int n;cin>>n;graph<int> G(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;G.insert(++u,++v);
        }
        G.dfs(1);int q;cin>>q;
        cir(i,0,q){
            int u,v,w;cin>>u>>v>>w;G.add(++u,++v,w);
        }
        auto ans=G.solve();
        cout<<"Case #"<<(++Case)<<":\n";
        cir(i,1,n+1) cout<<ans[i]<<'\n';
    }
    return 0;
}