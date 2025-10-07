#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("grid.in");
ofstream ouf("grid.out");
static constexpr auto _inf=(int)(1e9+7);
class chtholly{
private:
    struct node{
        int l,r;
        pair<int,int> info;
        constexpr auto operator<(const node x) const{
            return l<x.l;
        }
        node(int _l=-1,int _r=-1,pair<int,int> _info={-1,-1}):l(_l),r(_r),info(_info){}
    };
    set<node> qwq;
    auto split(int u){
        auto lb=qwq.lower_bound(node(u));
        if(lb->l==u) return lb;
        --lb;
        const auto[l,r,info]=*lb;
        qwq.erase(lb);
        qwq.emplace(l,u-1,info);
        return qwq.emplace(u,r,info).first;
    }
public:
    auto assign(int l,int r,pair<int,int> info){
        const auto pr=split(r+1),pl=split(l);
        qwq.erase(pl,pr);
        qwq.emplace(l,r,info);
    }
    auto query(int l,int r){
        const auto pr=split(r+1),pl=split(l);
        auto res=make_pair(-1,-1);
        for(auto it=pl;it!=pr;++it) res=max(res,it->info);
        return res;
    }
    chtholly(){qwq.emplace(-_inf,_inf);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<vector<pair<int,int>>> a(n);
    cir(i,0,q){
        int x,l,r;inf>>x>>l>>r;--x;--l;--r;
        a[x].emplace_back(l,r);
    }
    vector<int> f(n),g(n);
    chtholly cute;
    cir(i,0,n){
        auto mx=make_pair(0,-1);
        for(auto&[l,r]:a[i]) mx=max(mx,cute.query(l,r));
        f[i]=mx.first+1;
        g[i]=mx.second;
        for(auto&[l,r]:a[i]) cute.assign(l,r,make_pair(f[i],i));
    }
    auto u=max_element(f.begin(),f.end())-f.begin();
    const auto c=n-f[u];
    vector<int> vis(n);
    while(~u) vis[u]=true,u=g[u];
    ouf<<c<<'\n';
    cir(i,0,n) if(!vis[i]) ouf<<i+1<<' ';
    ouf<<'\n';
    return 0;
}

