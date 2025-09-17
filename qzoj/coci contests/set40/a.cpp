#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    dsu qwq(n);
    vector<pair<int16_t,int16_t>> es(m);
    for(auto&[u,v]:es) cin>>u>>v,--u,--v,qwq.merge(u,v);
    set<int> uc;
    cir(i,0,n) uc.emplace(qwq.findset(i));
    vector<int> cnt(n),ucnt(n);
    cir(i,0,n) ++ucnt[qwq.findset(i)];
    for(auto&[u,v]:es) ++cnt[qwq.findset(u)];
    auto ok=(int)(uc.size()<3);
    for(auto&x:uc){
        ok&=(ucnt[x]*(ucnt[x]-1)/2==cnt[x]);
    }
    cout<<(ok?"DA":"NE")<<'\n';
    return 0;
}
