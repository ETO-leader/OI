#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
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
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(auto a,auto b){
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    math.initfct(100007);
    while(T--) [&]{
        int n,c,m;cin>>n>>c>>m;
        vector<int> ax(m);
        for(auto&i:ax) cin>>i;
        vector<lint> f(m+1);
        f[0]=1;
        for(auto i=n-1;~i;--i){
            const auto fx=f;
            ranges::fill(f,0);
            cir(x,0,c+1) cir(w,c-x,m-x+1){
                (f[x+w]+=fx[w]*math.C(c,x))%=MOD;
            }
        }
        cout<<f[m]<<'\n';
    }();
    return 0;
}
