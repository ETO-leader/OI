#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> dis(n,vector<int>(n));
    for(auto&x:dis) for(auto&i:x) cin>>i;
    auto ans=_infl;
    cir(u,0,n){
        vector<vector<lint>> f(1<<n,vector<lint>(n,_infl));
        f[1<<u][0]=0;
        cir(s,0,(1<<n)) cir(i,0,n) if(s&(1<<i)){
            cir(j,0,n) if(!(s&(1<<j))) f[s|(1<<j)][j]=min(f[s|(1<<j)][j],f[s][i]+dis[i][j]);
        }
        cir(j,0,n) ans=min(ans,f[(1<<n)-1][j]+dis[j][u]);
    }
    cout<<ans<<'\n';
    return 0;
}
