#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr lint _inf=2e18;
struct edge_t{int u,v;lint w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;VI stx(n),iqt(n);
    lint ans=0,cx=0;
    vector<edge_t> es(m);
    for(auto&[u,v,w]:es){
        cin>>u>>v>>w;--u;--v;
    }
    stx[0]=1;
    stringstream ansx;
    cir(i,0,n*n) if(!stx[n-1]){
        auto nt=_inf;
        for(auto&[u,v,w]:es) if(stx[u]^stx[v]){
            if(stx[u]) swap(u,v);
            nt=min(nt,iqt[v]+w);
        }
        if(nt-ans){
            if(cx) ansx<<'\n';
            for(auto&i:stx) ansx<<i;
            ansx<<' '<<nt-ans;
            ++cx;
        }
        auto cpx=iqt,cpst=stx;
        for(auto&[u,v,w]:es) if(cpst[u]^cpst[v]){
            if(cpst[u]) swap(u,v);
            auto ak=cpx[v]+w;
            if(nt==ak) stx[u]=true,iqt[u]=nt;
        }
        ans=nt;
    }
    if(ans>1e18) cout<<"inf\n";
    else cout<<ans<<' '<<cx<<'\n'<<ansx.str()<<'\n';
    return 0;
}
