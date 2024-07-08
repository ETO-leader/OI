#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint maxk=1e10;
constexpr auto getminp(int x){
    for(auto i=2;i*i<x+1;++i)
        if(!(x%i)) return i;
    return x;
}
auto init_mu(int n){
    vector<int> mu(n);
    mu[1]=1;
    cir(i,2,n){
        const auto minp=getminp(i);
        if(!(i/minp%minp)) continue;
        mu[i]=-mu[i/minp];
    }
    return mu;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    const auto mu=init_mu(sqrt(maxk)+7);
    while(T--){
        int rk;cin>>rk;
        auto counti=[mu](lint n){
            lint res=0;
            for(auto i=1ll;i*i<n+1;++i){
                res+=mu[i]*(n/(i*i));
            }
            return res;
        };
        auto l=0ll,r=maxk,ans=-1ll;
        while(l<r+1){
            const auto mid=(l+r)/2;
            counti(mid)<rk?(l=mid+1):((r=mid-1),(ans=mid));
        }
        cout<<ans<<'\n';
    }
    return 0;
}
