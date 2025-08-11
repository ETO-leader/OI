#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e6+3);
class mathbase{
private:
    vector<lint> fct,ifct;
    constexpr auto binom(auto a,auto b) const{
        return a>b-1?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
    auto init(const int n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    auto C(auto a,auto b){
        if(a<MOD&&b<MOD) return binom(a,b);
        return binom(a%MOD,b%MOD)*C(a/MOD,b/MOD)%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.init(MOD);
    while(T--) []{
        int n,l,r;cin>>n>>l>>r;
        const auto c=r-l+1;
        cout<<(math.C(n+c,c)+MOD-1)%MOD<<'\n';
    }();
    return 0;
}
