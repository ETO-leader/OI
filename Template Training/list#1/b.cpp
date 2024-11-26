#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=9901;
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
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    constexpr auto arrsum(lint a,lint n){
        a%=MOD;
        if(a==1) return n;
        return (qpow(a,n)+MOD-1)*inv(a+MOD-1)%MOD;
    }
    auto factors(auto n){
        unordered_map<int,int> res;
        for(auto i=2;i*i<n+1;++i){
            while(!(n%i)) ++res[i],n/=i;
        }
        if(n>1) ++res[n];
        return res;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int a,b;cin>>a>>b;
    const auto fcts=math.factors(a);
    auto ans=1ll;
    for(auto&[p,c]:fcts) (ans*=math.arrsum(p,(lint)(c)*b+1))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
