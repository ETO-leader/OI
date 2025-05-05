#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
static constexpr auto maxn=(int)(5e6+7);
class mathbase{
private:
    vector<lint> fct,ifct;
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
    constexpr auto A(auto a,auto b) const{
        return fct[a]*ifct[a-b]%MOD;
    }
    constexpr auto C(auto a,auto b) const{
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<lint> f(maxn);
    math.init(maxn+7);
    f[0]=1;
    cir(i,2,maxn) (f[i]=f[i-1]*(i*4)%MOD*(i-1)+f[i-2]*((lint)(i-1)*(i-1)%MOD)%MOD*(i*8))%=MOD;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        cout<<math.A(n,k)*math.C(n,k)%MOD*math.qpow(2,k)%MOD*f[n-k]%MOD<<'\n';
    }();
    return 0;
}
