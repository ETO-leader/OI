#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e4+7);
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
        for(auto&x:ifct) x=inv(x); 
    }
    constexpr auto C(auto a,auto b) const{
        if(a<0||b<0||a-b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.init(MOD);
    while(T--) []{
        int n,m;cin>>n>>m;
        auto C=[&](auto __self,int a,int b){
            if(a<MOD&&b<MOD) return math.C(a,b);
            return __self(__self,a/MOD,b/MOD)*math.C(a%MOD,b%MOD)%MOD;
        };
        cout<<C(C,n,m)<<'\n';
    }();
    return 0;
}
