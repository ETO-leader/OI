#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    vector b(n,vector<lint>(n));
    for(auto&i:b) for(auto&j:i) cin>>j;
    vector<lint> f(1<<n,-_infl);
    f[0]=0;
    auto cost=[&](int u,int v,int i){
        return max({
            a[u],a[v],a[i],
            b[u][v],b[v][i],b[u][i],
            b[u][i]*b[v][i]*b[u][v]
        });
    };
    cir(s,0,(1<<n)){
        if(__builtin_popcount(s)%3) continue;
        cir(i,0,n) if(!(s&(1<<i))){
            cir(j,0,i) if(!(s&(1<<j))){
                cir(k,0,j) if(!(s&(1<<k))){
                    const auto ns=s|(1<<i)|(1<<j)|(1<<k);
                    f[ns]=max(f[ns],f[s]+cost(i,j,k));
                }
            }
        }
    }
    cout<<f[(1<<n)-1]<<'\n';
    return 0;
}
