#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f,siz;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto size(int u){
        return siz[findset(u)];
    }
    // v -> u
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        siz[u]+=siz[v];
        f[v]=u;
    }
    dsu(int _n):f(_n),siz(_n,1){iota(f.begin(),f.end(),0);}
};
class tree{
private:
    vector<vector<pair<int,uint>>> gr;
    vector<unordered_map<uint,int64_t>> cnt;
    vector<uint> upre;
    dsu cc;
    int64_t ans;
    auto dfs(int u,uint pre,int s,int f=-1)->void{
        ans+=cnt[s][pre];
        ++cnt[s][pre];
        upre[u]=pre;
        for(auto&[v,w]:gr[u]) if(v!=f) dfs(v,pre^w,s,u); 
    }
public:
    auto merge(int u,int v,uint w){
        if(cc.size(u)<cc.size(v)) swap(u,v);
        const auto uf=cc.findset(u),vf=cc.findset(v);
        for(auto&[a,b]:cnt[vf]) ans-=b*(b-1)/2;
        dfs(v,upre[u]^w,uf);
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
        cc.merge(u,v);
    }
    auto cost() const{return ans;}
    tree(int _n):gr(_n),cnt(_n),upre(_n),cc(_n),ans(0){
        cir(i,0,_n) cnt[i][0]=1;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int64_t> ans(n);
    vector<tuple<int,int,uint>> es(n-1);
    for(auto&[u,v,w]:es) cin>>u>>v>>w,--u,--v;
    vector<int> ord(n-1);
    for(auto&i:ord) cin>>i,--i;
    tree gr(n);
    for(auto i=n-2;~i;--i){
        const auto[u,v,w]=es[ord[i]];
        gr.merge(u,v,w);
        ans[i]=gr.cost();
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
