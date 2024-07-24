#include<bits/stdc++.h>
using namespace std;
using ඞ=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(ඞ a,ඞ b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(ඞ x) const{
        return qpow(x,MOD-2);
    }
    auto choose(ඞ a){
        return a>2?a*(a-1)%MOD*(a-2)%MOD*inv(2)%MOD*inv(3)%MOD:0ll;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;vector<ඞ> a(n);
        for(auto&i:a) cin>>i;
        if(n==1) return cout<<0<<'\n',void();
        ranges::sort(a);
        auto ans=math.choose(m+1)%MOD;
        for(auto i:views::iota(1,n)){
            (ans+=MOD-math.choose(a[i]-a[i-1]+1))%=MOD;
        }
        (ans+=MOD-math.choose(a[0]+m-a[n-1]+1))%=MOD;
        (ans*=n*math.inv(m)%MOD)%=MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
