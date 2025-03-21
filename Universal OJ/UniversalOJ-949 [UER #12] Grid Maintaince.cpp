#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> g,imp;
    static constexpr auto ups=21;
    auto udfs(int u,int f=-1)->int{
        for(auto&i:gr[u]) if(i!=f) g[u]=max(g[u],udfs(i,u)+1);
        return g[u];
    }
    auto dfs(int u,int f=-1)->pair<int,int>{
        auto res=pair(-1,u);
        for(auto&i:gr[u]) if(i!=f) res=max(res,dfs(i,u));
        ++res.first;
        return res;
    }
    auto check(int u,int k,int f=-1)->void{
        imp[u]=true;
        for(auto&i:gr[u]) if(g[i]>k-1&&i!=f) check(i,k,u);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto furthest(int u){
        return dfs(u).first;
    }
    auto check(const int k){
        udfs(0);
        check(0,k);
        return accumulate(imp.begin(),imp.end(),0);
    }
    auto diameter(){
        return dfs(dfs(0).second).first;
    }
    tree(int _n):gr(_n),g(_n),imp(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;tree tr(n);
    vector<vector<int>> gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
        tr.link(u,v);
    }
    auto maxdep=tr.furthest(0);
    const auto ad=(tr.check(k)-1)*2;
    if(maxdep<k){
        cout<<(n-1)*2+ad-min(tr.diameter(),k)<<'\n';
    }else{
        cout<<(n-1)*2+ad+k-maxdep*2<<'\n';
    }
    return 0;
}
