#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<tuple<int,int,int,int,int>> a(n);
    for(auto&[xl,xr,yl,yr,col]:a) cin>>xl>>yl>>xr>>yr>>col;
    vector<int> req(n);
    cir(i,0,n) cir(j,0,n) if(i!=j){
        const auto[ixl,ixr,iyl,iyr,ic]=a[i];
        const auto[jxl,jxr,jyl,jyr,jc]=a[j];
        if(ixl==jxr&&(!(iyr<jyl||jyr<iyl))) req[i]|=(1<<j);
    }
    vector<vector<int>> f(1<<n,vector<int>(n,_inf));
    cir(i,0,n) if(!req[i]) f[1<<i][i]=1;
    cir(s,0,(1<<n)) cir(u,0,n) if((s>>u)&1){
        cir(v,0,n) if((!((s>>v)&1))&&((req[v]&s)==req[v])) f[s|(1<<v)][v]=min(f[s|(1<<v)][v],f[s][u]+(get<4>(a[u])!=get<4>(a[v])));
    }
    cout<<*min_element(f[(1<<n)-1].begin(),f[(1<<n)-1].end())<<'\n';
    return 0;
}
