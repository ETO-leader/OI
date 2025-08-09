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
    math.init((int)(5e5+9));
    while(T--) [&]{
        int n,m;cin>>n>>m;
        auto f=[&](int v){
            auto res=0ll;
            const auto r=m-v;
            if(r<0) return 0ll;
            cir(j,0,(r/(v+1))+1){
                (res+=(j&1?MOD-1:1)*math.C(n-1,j)%MOD*math.C(r-(v+1)*j+n-2,n-2))%=MOD;
            }
            return res;
        };
        auto g=[&](int v){
            auto res=0ll;
            const auto r=m-v*2;
            if(r<0) return 0ll;
            cir(j,0,(r/(v+1))+1) (res+=(j&1?MOD-1:1)*math.C(n-2,j)%MOD*math.C(r-(v+1)*j+n-3,n-3))%=MOD;
            return res;
        };
        auto ans=0ll;
        const auto ivn=math.inv(n-1);
        cir(i,0,m+1){
            const auto uf=f(i),ug=g(i);
            (ans+=i*(uf+(n-1)*ug%MOD)%MOD+MOD-(uf*ivn%MOD+ug)%MOD*(m-i)%MOD)%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
