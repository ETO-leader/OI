#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class trie{
private:
    vector<array<int,2>> tr;
    static constexpr auto b=30;
    int cnt;
public:
    auto insert(const uint x){
        auto u=0;
        for(auto i=b;~i;--i){
            const auto w=(x>>i)&1;
            if(!tr[u][w]) tr[u][w]=++cnt;
            u=tr[u][w];
        }
    }
    auto query(const uint x){
        auto u=0;auto res=0u;
        for(auto i=b;~i;--i){
            const auto w=(x>>i)&1;
            if(tr[u][w^1]) u=tr[u][w^1],res|=(1<<i);
            else u=tr[u][w];
        }
        return res;
    }
    trie(auto _n):tr(_n*(b+1)),cnt(0){}
};
class tree{
private:
    vector<vector<pair<int,uint>>> gr;
    auto dfs(int u,trie&tr,uint cur=0,int f=-1)->uint{
        tr.insert(cur);
        auto res=tr.query(cur);
        for(auto&[v,w]:gr[u]) if(v!=f) res=max(res,dfs(v,tr,cur^w,u));
        return res;
    }
public:
    auto link(int u,int v,uint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto check(){
        trie tr(gr.size());
        return dfs(0,tr);
    }
    tree(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree tr(n);
    cir(i,0,n-1){
        int u,v;uint w;cin>>u>>v>>w;--u;--v;
        tr.link(u,v,w);
    }
    cout<<tr.check()<<'\n';
    return 0;
}
