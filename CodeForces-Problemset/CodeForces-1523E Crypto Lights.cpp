#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
static constexpr auto maxq=(int)(1e5+7);
class mathbase{
private:
    vector<lint> fct;
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
    }
    auto C(auto a,auto b){
        if(a<b) return 0ll;
        return fct[a]*inv(fct[b])%MOD*inv(fct[a-b])%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;math.initfct(maxq);
    while(T--) [&](){
        int n,k;cin>>n>>k;
        auto ans=1ll;
        cir(i,2,n+1){
            (ans+=math.C(n-1ll*(i-2)*(k-1),i-1)*math.inv(math.C(n,i-1)))%=MOD;
        }
        println(cout,"{}",ans);
    }();
    return 0;
}
