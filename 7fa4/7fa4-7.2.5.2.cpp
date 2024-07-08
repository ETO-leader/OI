#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int maxk=5e6+7;
static constexpr int MOD=1e9+7;
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
auto init_mu(int n){
    vector<int> mu(n,1),minp(n);
    iota(minp.begin(),minp.end(),0);
    cir(i,2,n){
        const auto p=minp[i];
        for(int j=i;j<n;j+=i)
            minp[j]=min(minp[j],i);
        if(!((i/p)%p)) mu[i]=0;
        else mu[i]=-mu[i/p];
    }
    return mu;
}
template<typename _Ty>
constexpr auto&modf(_Ty&a){
    a+=(a<0?MOD:0);
    a-=(a>MOD-1?MOD:0);
    return a;
}
template<typename _Ty>
constexpr auto qmodf(_Ty a){
    a+=(a<0?MOD:0);
    a-=(a>MOD-1?MOD:0);
    return a;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,k;cin>>T>>k;
    vector<lint> pre(maxk),pw(maxk,1);
    auto mu=init_mu(maxk);
    cir(i,0,maxk) pw[i]=qpow(i,k);
    [&](){
        cir(i,1,maxk){
            auto c=0;
            for(auto w=i;w<maxk;w+=i){
                modf(pre[w]+=pw[i]*mu[++c]);
            }
            if(i) modf(pre[i]+=pre[i-1]);
        }
    }();
    while(T--) [&](){
        int n,m;cin>>n>>m;
        auto ans=0ll;
        for(auto i=1,p=0;i<min(n,m)+1;i=p+1){
            p=min(n/(n/i),m/(m/i));
            (ans+=1ll*(n/i)*(m/i)%MOD*
                qmodf(pre[p]-pre[i-1]))%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
