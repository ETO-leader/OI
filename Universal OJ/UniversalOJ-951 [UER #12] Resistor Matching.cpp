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
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(auto a,auto b){
        if(a<b) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    auto fact(auto x) const{return fct[x];}
    auto ifact(auto x) const{return ifct[x];}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;n*=2;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    math.init(n+7);
    vector<lint> ivpw(n+7,1);
    const auto inv2=math.inv(2);
    cir(i,1,n+7) ivpw[i]=ivpw[i-1]*inv2%MOD;
    auto check=[&](const auto w){
        vector<lint> lss,grt;
        for(auto&i:a) (i*2<w+1?lss:grt).emplace_back(i);
        ranges::sort(lss,greater<lint>());
        ranges::sort(grt);
        vector<lint> f(n+1);
        f[0]=1;
        for(auto i=-1;auto&x:lss){
            ++i;
            const auto lf=f;
            const auto r=ranges::upper_bound(grt,w-x)-grt.begin();
            cir(x,1,n+1) (f[x]+=lf[x-1]*(r-x+1))%=MOD;
        }
        const auto cl=(int)(lss.size());
        const auto lim=min(n/2,cl);
        vector<lint> g(n+1);
        cir(i,0,lim+1){
            for(auto j=0;i+j*2<cl+1&&i+j<lim+1;++j) (g[i+j]+=f[i]*math.C(cl-i,j*2)%MOD*math.fact(j*2)%MOD*math.ifact(j)%MOD*ivpw[j]%MOD)%=MOD;
        }
        cir(i,0,lim+1) (g[i]*=math.fact(n-i*2)%MOD*math.ifact((n-2*i)/2)%MOD*ivpw[(n-2*i)/2]%MOD)%=MOD;
        for(auto i=lim;~i;--i) cir(j,i+1,lim+1){
            (g[i]+=MOD-math.C(j,i)*g[j]%MOD)%=MOD;
        }
        cir(i,1,n+1) (g[i]+=g[i-1])%=MOD;
        return g;
    };
    set<lint> sw{0};
    cir(i,0,n) cir(j,i+1,n) sw.emplace(a[i]+a[j]);
    vector<lint> ans(n/2+1);
    for(auto&x:sw) if(x!=*sw.rbegin()){
        const auto nxt=*sw.upper_bound(x);
        const auto fx=check(x);
        cir(i,1,n/2+1) (ans[i]+=fx[i-1]*(nxt-x))%=MOD;
    }
    cir(i,1,n/2+1) cout<<ans[i]<<' ';
    cout<<'\n';
    return 0;
}
