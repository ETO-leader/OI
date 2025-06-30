#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
constexpr auto f(auto x,const auto s,auto&pre){
    auto res=pre[x-1];
    return res*(s+MOD-1)%MOD*(s+MOD-x)%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    const auto s=accumulate(a.begin(),a.end(),0ll)%MOD;
    vector<lint> pre(*ranges::max_element(a));
    cir(i,0,(int)(pre.size())) pre[i]=math.inv(s-i);
    cir(i,1,(int)(pre.size())) (pre[i]+=pre[i-1])%=MOD;
    auto ans=0ll;
    cir(i,0,n) (ans+=f(a[i],s,pre))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
