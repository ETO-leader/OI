#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit{
private:
    vector<int> w;
    constexpr auto lowbit(auto u) const{return u&(-u);}
public:
    auto update(int u,int wx){
        for(++u;u<(int)(w.size());u+=lowbit(u)) w[u]+=wx;
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res+=w[u];
        return res;
    }
    bit(int _n):w(_n+7){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> dfn,rdfn;
    auto dfs(int u,auto&cnt,int f=-1)->void{
        dfn[u]=++cnt;
        for(auto&i:gr[u]) if(i!=f) dfs(i,cnt,u);
        rdfn[u]=cnt;
    }
public:
    auto link(auto u,auto v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto c=-1;dfs(0,c);
    }
    auto info(auto u){return pair(dfn[u],rdfn[u]);}
    tree(int _n):gr(_n),dfn(_n),rdfn(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
    }();
    return 0;
}
