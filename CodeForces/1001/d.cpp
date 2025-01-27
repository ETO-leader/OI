#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<lint> f,g,l,r;
    auto dfs(int u,int fr=-1)->void{
        for(auto&i:gr[u]) if(i!=fr){
            dfs(i,u);g[u]+=g[i];
        }
        for(auto&i:gr[u]) if(i!=fr) f[u]=max((f[i]+=(g[u]-g[i])),f[u]);
        l[u]+=g[u];r[u]+=g[u];
        if(r[u]<f[u]){
            f[u]=r[u];
            for(auto&i:gr[u]) if(i!=fr) f[u]+=max(f[i]-r[u],0ll);
            g[u]+=f[u]-r[u];
        }else{
            f[u]=max(f[u],l[u]);
        }
    }
public:
    auto link(auto u,auto v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(auto _l,auto _r){
        l=_l;r=_r;
        dfs(0);return f[0];
    }
    tree(int _n):gr(_n),f(_n),g(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<lint> l(n),r(n);
        cir(i,0,n) cin>>l[i]>>r[i];
        tree tr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            tr.link(u,v);
        }
        println("{}",tr.check(l,r));
    }();
    return 0;
}
