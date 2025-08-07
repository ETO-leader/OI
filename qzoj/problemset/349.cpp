#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=19940417;
constexpr auto psum(lint x){
    return (lint)((__int128_t)(x)*(x+1)*(x*2+1)/6%MOD);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n,m;cin>>n>>m;
    auto ansx=n*n%MOD,ansy=m*m%MOD;
    for(auto x=1ll,r=0ll;x<n+1;x=r+1){
        r=n/(n/x);
        (ansx+=MOD-(n/x)*((x+r)*(r-x+1)/2%MOD)%MOD)%=MOD;
    }
    for(auto x=1ll,r=0ll;x<m+1;x=r+1){
        r=m/(m/x);
        (ansy+=MOD-(m/x)*((x+r)*(r-x+1)/2%MOD)%MOD)%=MOD;
    }
    auto del=n*m%MOD*min(n,m);
    for(auto x=1ll,r=0ll;x<min(n,m)+1;x=r+1){
        r=min(n/(n/x),(m/(m/x)));
        (del+=MOD-m*(n/x)%MOD*((x+r)*(r-x+1)/2%MOD)%MOD)%=MOD;
        (del+=MOD-n*(m/x)%MOD*((x+r)*(r-x+1)/2%MOD)%MOD)%=MOD;
        (del+=(n/x)*(m/x)%MOD*(psum(r)+MOD-psum(x-1)))%=MOD;
    }
    cout<<(ansx*ansy%MOD+MOD-del)%MOD<<'\n';
    return 0;
}
