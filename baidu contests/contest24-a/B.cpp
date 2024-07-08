#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
static constexpr auto maxn=(int)(1e7+7);
static constexpr auto MOD=998244353;
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){return qpow(x,MOD-2);}
auto initpr(const int n){
    vector<int> pr;
    bitset<maxn> isnp;
    cir(i,2,n+1){
        if(isnp[i]) continue;
        pr.push_back(i);
        for(auto j=1ll*i*i;j<n+1;j+=i){
            isnp[j]=true;
        }
    }
    return pr;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    auto pr=initpr(n);
    auto rg=1ll;
    for(auto&i:pr){
        auto nw=1ll;
        while(nw<n+1) nw*=i;
        (rg*=(nw/i))%=MOD;
    }
    auto ans=0ll,pre=0ll;
    vector<int> rgx(n+1);
    const auto iv2=inv(2);
    cir(i,1,n+1){
        const auto rgi=(i&1?(rg*inv(i)%MOD):(rgx[i/2]*iv2%MOD));
        rgx[i]=rgi;
        (ans+=(pre+MOD-rgi*(i-1)%MOD))%=MOD;
        (pre+=rgi)%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
