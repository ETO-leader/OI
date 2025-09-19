#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto C(auto a,auto b) const{
        return (a>b-1&&b>-1)?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
    constexpr auto ifact(const auto n) const{
        return ifct[n];
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    math.init(n+7);
    auto ans=0ll;
    cir(i,0,m){
        (ans+=((i&1)?(MOD-1):1)*math.qpow(m-i,n)%MOD*math.C(m,m-i))%=MOD;
    }
    cout<<ans*math.ifact(m)%MOD<<'\n';
    return 0;
}
