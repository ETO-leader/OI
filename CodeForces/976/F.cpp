#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
static constexpr auto maxif=(int)(3.2e7+7);
class mathbase{
private:
    vector<int> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
    auto initfct(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=1ll*fct[i-1]*i%MOD;
        ifct.resize(n);
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=1ll*ifct[i+1]*(i+1)%MOD;
    }
    auto C(auto a,auto b){
        if(a<b) return 0ll;
        return 1ll*fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    auto primes(const auto n){
        vector<int> p,isp(n,true);
        cir(i,2,n){
            if(!isp[i]) continue;
            p.push_back(i);
            for(auto x=i*2;x<n;x+=i) isp[x]=false;
        }
        return p;
    }
} math;
class Min_25{
public:
    auto sieve(const int n,const int k,const int d){
        const auto sqr=(int)(sqrtl(n)+7);
        const auto pr=math.primes(sqr);
        vector<lint> ls(sqr),ge(sqr),val(sqr*2+7);
        const auto pos=[&](const auto p){
            return&(p<sqr?ls[p]:ge[n/p]);
        };
        for(auto i=1ll,p=0ll,c=-1ll;i<n+1;i=p+1){
            p=n/(n/i);
            *pos(n/i)=++c;
            val[c]=n/i;
        }
        vector<lint> f((sqr<<1)+7);
        for(auto c=-1;auto&x:val) f[++c]=x-1;
        for(auto c=-1;auto&p:pr){
            ++c;
            for(auto i=0;1ll*p*p<val[i]+1;++i) (f[i]+=MOD-(f[*pos(val[i]/p)]+MOD-c)%MOD)%=MOD;
        }
        for(auto&i:f) (i*=math.C(k+d,d))%=MOD;
        auto g=[&](auto __self,int nx,int minp)->lint {
            if(nx<2||(minp&&pr[minp-1]>nx)) return 0ll;
            auto res=(f[*pos(nx)]+MOD-math.C(k+d,d)*minp%MOD)%MOD;
            for(auto px=minp;px<(int)(pr.size())&&1ll*pr[px]*pr[px]<nx+1;++px){
                const auto p=pr[px];
                (res+=MOD-math.C(k+d,d))%=MOD;
                for(auto pw=(lint)(p),c=1ll;pw<nx+1;pw*=p,++c){
                    (res+=(__self(__self,nx/pw,px+1)+1)*math.C(k*c+d,k*c))%=MOD;
                }
            }
            return res;
        };
        return (g(g,n,0)+1)%MOD;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.initfct(maxif);
    while(T--) [&](){
        int n,k,d;cin>>n>>k>>d;
        println("{}",Min_25().sieve(n,k,d));
    }();
    return 0;
}
