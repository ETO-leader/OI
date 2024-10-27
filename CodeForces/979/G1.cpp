#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b){
        auto res=(decltype(a))(1);
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    auto initfct(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(auto a,auto b){
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        math.initfct(n+7);
        vector<int> l(n),r(n);
        cir(i,0,n) cin>>l[i]>>r[i];
        vector<int> pl(n),pr(n);
        ranges::iota(pl,0);
        ranges::iota(pr,0);
        ranges::sort(pl,[&](auto&a,auto&b){return l[a]<l[b];});
        ranges::sort(pr,[&](auto&a,auto&b){return r[a]<r[b];});
        vector<lint> cl(n),cr(n);
        cir(i,0,n) cl[pl[i]]=i;
        cir(i,0,n) cr[pr[i]]=i;
        auto ans=0ll;
        cir(i,0,n) cir(j,i+1,n){
            auto l0=l[i],r0=r[i],l1=l[j],r1=r[j];
            if(!(r0<l1||r1<l0)) continue;
            const auto lc=n-1-cl[r0>l1-1?i:j],rc=cr[r0>l1-1?j:i];
            if(r0>l1-1) swap(l0,l1),swap(r0,r1);
            (ans+=(l1-r0)*math.qpow(2,n-2-lc-rc)%MOD*math.C(lc+rc,lc))%=MOD;
        }
        println("{}",ans);
    }();
    return 0;
}
