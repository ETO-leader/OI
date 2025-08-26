#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("prefix.in");
ofstream ouf("prefix.out");
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
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
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    lint n,p;inf>>n>>p;
    auto sl=p,ans=p;
    auto prefix_sum=[&](auto x){
        return (math.qpow(p,x+1)+MOD-1)*math.inv(p-1)%MOD;
    };
    auto update=[&](auto l,auto r,auto x){
        (ans+=(prefix_sum(r-1)+MOD-prefix_sum(l-2))*(p-1)%MOD*x)%=MOD;
    };
    for(;sl<n+1;sl*=p){
        const auto lw=sl/p+1;
        update(lw,sl,sl%MOD);
    }
    const auto lw=sl/p+1;
    update(lw,n,sl%MOD);
    ouf<<ans*math.inv(math.qpow(p,n))%MOD<<'\n';
    return 0;
}
