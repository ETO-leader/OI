#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){return qpow(a,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint n,h,w;cin>>n>>h>>w;
        if(n*2>h||n*2>w) return cout<<0<<'\n',void();
        const auto a=h-n*2;
        const auto b=w-n*2;
        const auto ux=(a+1)*(a+2)%MOD*math.inv(2)%MOD;
        const auto vx=(b+1)*(b+2)%MOD*math.inv(2)%MOD;
        const auto uy=a*(a+1)%MOD*(a+2)%MOD*(a+3)%MOD*math.inv(24)%MOD;
        const auto vy=b*(b+1)%MOD*(b+2)%MOD*(b+3)%MOD*math.inv(24)%MOD;
        const auto ans=(
            ux*ux%MOD*vx%MOD*vx%MOD
            +MOD-uy*vy*2%MOD
        )%MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
