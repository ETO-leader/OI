#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=1e9+7;
constexpr auto getminp(int x){
    for(auto i=2;i*i<x+1;++i)
        if(!(x%i)) return i;
    return x;
}
auto init_mu(int n){
    vector<int> mu(n);mu[1]=1;
    cir(i,2,n){
        const auto minp=getminp(i);
        if(!(i/minp%minp)) continue;
        mu[i]=-mu[i/minp];
    }
    return mu;
}
auto getdivisor(int x){
    vector<int> divs;
    for(auto i=1;i*i<x+1;++i) if(!(x%i)){
        divs.push_back(i);
        if(x/i!=i) divs.push_back(x/i);
    }
    return divs;
}
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
vector<lint> fct;
auto C(const int a,const int b){
    return fct[a]*inv(fct[b])%MOD*inv(fct[a-b])%MOD;
}
auto init_fct(int n){
    fct.resize(n,1);
    cir(i,2,n) fct[i]=fct[i-1]*i%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;k=n-k;
    vector<int> a(n);
    vector<lint> cnt(m+1),ansi(m+1);
    for(auto&i:a) cin>>i;
    const auto mu=init_mu(m+7);
    init_fct(n+7);
    for(const auto&i:a){
        const auto divs=getdivisor(i);
        for(const auto&d:divs) ++cnt[d];
    }
    cir(w,1,m+1){
        if(cnt[w]<k) continue;
        ansi[w]=C(cnt[w],k)*qpow(m/w-1,cnt[w]-k)%MOD
            *qpow(m/w,n-cnt[w])%MOD;
    }
    cir(i,1,m+1){
        auto ans=0ll;
        for(auto d=i,c=1;d<m+1;d+=i,++c){
            (ans+=ansi[d]*mu[c]+MOD)%=MOD;
        }
        cout<<ans<<' ';
    }
    cout<<'\n';
    return 0;
}
