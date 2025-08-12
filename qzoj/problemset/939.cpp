#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;lint a;cin>>n>>m>>a;
    vector<lint> b(n),c(n),f(n);
    cir(i,0,n) cin>>b[i]>>c[i];
    for(auto&x:f) cin>>x;
    vector<tuple<lint,lint,int,int>> es;
    cir(i,0,n) cir(j,0,m){
        lint d,e;cin>>d>>e;
        es.emplace_back(c[i]+e+f[j],d,i,j);
    }
    sort(es.begin(),es.end());
    auto fl=0ll,cst=0ll;
    for(auto&[w,x,u,v]:es){
        const auto uf=min({x,b[u],a});
        b[u]-=uf;
        a-=uf;
        fl+=uf;
        cst+=w*uf;
    }
    cout<<fl<<' '<<cst<<'\n';
    return 0;
}
