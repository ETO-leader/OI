#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<int> vaild;
    cir(u,0,n){
        int x;cin>>x;
        if(x) vaild.emplace_back(u);
    }
    vector<int> target(k);
    for(auto&i:target) cin>>i,--i;
    vector dis(n,vector(n,_infl));
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;--u;--v;
        dis[u][v]=min(dis[u][v],w);
        dis[v][u]=min(dis[v][u],w);
    }
    cir(i,0,n) dis[i][i]=0;
    cir(k,0,n) cir(u,0,n) cir(v,0,n) dis[u][v]=min(dis[u][v],dis[u][k]+dis[k][v]);
    vector<int> type(n);
    for(auto id=-1;auto&x:target){
        ++id;
        cir(u,0,n) if(dis[0][u]+dis[u][x]==dis[0][x]) type[u]|=(1<<id);
    }
    vector f(1<<k,_infl);
    f[0]=0;
    for(auto&u:vaild){
        cir(s,0,(1<<k)) f[s|type[u]]=min(f[s|type[u]],f[s]+1);
    }
    cout<<f[(1<<k)-1]<<'\n';
    return 0;
}
