#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,k;cin>>n>>k;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        const auto avgspc=accumulate(a.begin(),a.begin()+k,0ll)%MOD*math.inv(k)%MOD,
            avgnrm=accumulate(a.begin()+k,a.end(),0ll)%MOD*math.inv(n-k)%MOD;
        const auto expspc=(((n-k+2)/2)*k%MOD)*math.inv(n-k+1)%MOD;
        const auto expnrm=(n-k+1)/2;
        const auto ansa=(avgspc*expspc+avgnrm*expnrm)%MOD;
        const auto ansb=(accumulate(a.begin(),a.end(),0ll)+MOD-ansa)%MOD;
        cout<<ansa<<' '<<ansb<<'\n';
    }();
    return 0;
}
