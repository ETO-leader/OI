#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using ull=unsigned long long;
class dsu{
private:
    VI f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){
        iota(f.begin(),f.end(),0);
    }
};
vector<VI> G;
vector<bool> vis;
vector<ull> a;
vector<pair<int,int>> ans;
auto dfs(int u,int f=0)->ull{
    ull res=a[u];vis[u]=true;
    for(auto&i:G[u]) if(i!=f){
        auto x=dfs(i,u);
        if(!x) ans.push_back({u,i});
        res^=x;
    }
    return res;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;dsu ds(n+1);
    mt19937_64 rnd(time(nullptr));
    G.resize(n+1);a.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        if(ds.findset(u)==ds.findset(v)){
            auto rd=rnd();a[u]^=rd;a[v]^=rd;
        }else{
            G[u].push_back(v);G[v].push_back(u);
            ds.merge(u,v);
        }
    }
    vis.resize(n+1);
    cir(i,1,n+1) if(!vis[i]) dfs(i);
    for(auto&[u,v]:ans) cout<<u<<' '<<v<<'\n';
    return 0;
}
