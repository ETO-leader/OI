#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=9901;
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
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b;cin>>a>>b;
    map<int,int> cnt;
    for(auto x=2;x*x<a+1;++x){
        while(!(a%x)) ++cnt[x],a/=x;
    }
    if(a>1) ++cnt[a];
    auto ans=1ll;
    for(auto&[w,c]:cnt){
        (ans*=((math.qpow(w,c*b+1)+MOD-1)*math.inv(w-1)%MOD))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
