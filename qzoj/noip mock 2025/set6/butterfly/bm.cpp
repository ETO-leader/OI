#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
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
class berlekamp_massey{
public:
    auto solve(vector<lint> a){
        auto p=vector<lint>(),las=vector<lint>();
        auto k=-1ll,delta=0ll;
        for(auto i=-1;auto&x:a){
            ++i;
            auto nw=0ll;
            cir(j,0,(int)(p.size())){
                (nw+=p[j]*a[i-j-1])%=MOD;
            }
            if(nw==x) continue;
            if(k<0){
                k=i;
                delta=(x+MOD-nw)%MOD;
                p.resize(i+1);
                continue;
            }
            const auto w=(x+MOD-nw)*math.inv(delta)%MOD;
            const auto np=p;
            if(p.size()<las.size()+(i-k)) p.resize(las.size()+(i-k));
            (p[i-k-1]+=w)%=MOD;
            cir(j,0,(int)(las.size())){
                p[i+j-k]=(p[i+j-k]-w*las[j]%MOD+MOD)%MOD;
            }
            if((int)(np.size())-i<(int)(las.size())-k){
                las=np;k=i;
                delta=(x+MOD-nw)%MOD;
            }
        }
        for(auto&i:p) i=(MOD-i)%MOD;
        p.insert(p.begin(),1);
        return p;
    }
};
int main(){
    int n;cin>>n;
    vector<lint> a(n);
    for(auto&i:a) cin>>i;
    const auto x=berlekamp_massey().solve(a);
    auto s=0ll;
    cir(i,0,(int)(x.size())){
        (s+=a[20-i]*x[i])%=MOD;
    }
    clog<<"SUM = "<<s<<'\n';
    for(auto&i:x) clog<<i<<' ';
    clog<<'\n';
}
