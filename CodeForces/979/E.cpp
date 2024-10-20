#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(auto a,auto b){
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
        vector<int> cnt(n+1);
        cir(i,0,n){
            int x;cin>>x;++cnt[x];
        }
        vector<lint> f(n+1),c(n+1);
        c[n]=1;
        math.initfct(n+7);
        auto premin=n;
        cir(i,0,n+1){
            auto sufsum=0ll,sufc=0ll,sufb=0ll;
            for(auto x=cnt[i];x>premin;--x) (sufb+=math.C(cnt[i],x))%=MOD;
            for(auto x=premin;~x;--x){
                (sufsum+=sufc*i)%=MOD;
                const auto lfx=f[x],lcx=c[x];
                (sufb+=math.C(cnt[i],x))%=MOD;
                f[x]=(f[x]*sufb+sufsum*math.C(cnt[i],x))%MOD;
                c[x]=(c[x]*sufb+sufc*math.C(cnt[i],x))%MOD;
                (sufsum+=lfx)%=MOD;
                (sufc+=lcx)%=MOD;
            }
            premin=min(premin,cnt[i]);
            f.resize(premin+1);
            c.resize(premin+1);
        }
        println("{}",f[0]);
    }();
    return 0;
}
