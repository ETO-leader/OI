#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> f;
public:
    int findset(int u){
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    void merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
auto mst(const int n,vector<tuple<int,int,lint,lint>> es,vector<int> vis){
    dsu qwq(n);
    sort(es.begin(),es.end(),[&](auto&a,auto&b){return get<2>(a)==get<2>(b)?get<3>(a)<get<3>(b):get<2>(a)>get<2>(b);});
    auto res=0ll;
    for(auto&[u,v,uh,w]:es) if(vis[u]&&vis[v]){
        if(qwq.findset(u)==qwq.findset(v)) continue;
        res+=w;
        qwq.merge(u,v);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<lint> h(n);
    for(auto&i:h) cin>>i;
    vector<tuple<int,int,lint,lint>> es(m);
    vector<vector<int>> vx(n);
    vector<int> vis(n),uin(n);
    for(auto&[u,v,uh,w]:es){
        cin>>u>>v>>w;--u,--v;
        if(h[u]>h[v]-1) vx[u].emplace_back(v);
        if(h[v]>h[u]-1) vx[v].emplace_back(u);
        if(h[u]<h[v]) swap(u,v);
        uh=h[v];
    }
    auto dfs=[&](auto __self,int u)->void {
        if(vis[u]) return;
        vis[u]=true;
        for(auto&i:vx[u]) __self(__self,i);
    };
    dfs(dfs,0);
    cout<<accumulate(vis.begin(),vis.end(),0)<<' '<<mst(n,es,vis)<<'\n';
    return 0;
}
