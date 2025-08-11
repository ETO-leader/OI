#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
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
    vector<pair<int,int>> es(m);
    for(auto&[u,v]:es){
        cin>>u>>v,--u;--v;
        qwq.merge(u,v);
    }
    map<int,vector<int>> siz;
    cir(i,0,n) siz[qwq.findset(i)].emplace_back(i);
    cout<<siz.size()<<'\n';
    for(auto&[a,b]:siz){
        cout<<b.size()<<' ';
        for(auto&x:b) cout<<x+1<<' ';
        cout<<'\n';
    }
    return 0;
}
