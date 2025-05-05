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
        if(a<b||b<0) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int na,nb,nc;cin>>na>>nb>>nc;
    math.init(na+nb+nc+13);
    vector<lint> f(na+nb+nc+7);
    f[0]=1;
    cir(i,1,(int)(f.size())) (f[i]=f[i-1]*2+MOD*2-math.C(i-1,i-nc-1)-math.C(i-1,nb))%=MOD;
    auto ans=0ll;
    cir(c,0,nb+nc+1) (ans+=math.qpow(3,nb+nc-c)*math.C(c+na-1,c)%MOD*f[c])%=MOD;
    cout<<ans<<'\n';
    return 0;
}
