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
        for(auto&i:ax) cin>>i,--i;
        vector<int> las(n,-1),cnt(n);
        vector prex(m,vector<int>(n));
        cir(i,0,m) if(ax[i]>-1){
            las[ax[i]]=i;++cnt[ax[i]];
        }
        cir(w,0,n){
            cir(p,0,m) prex[p][w]=(ax[p]>w-1);
            cir(p,1,m) prex[p][w]+=prex[p-1][w];
        }
        vector<lint> f(m+1);
        f[0]=1;
        cir(i,0,n){
            const auto fx=f;
            ranges::fill(f,0);
            cir(x,0,m+1) cir(w,0,c+1){
                if(x<w||(las[i]+1>c+x-w)||(w<cnt[i])||(c+x-w>m)) continue;
                const auto pfree=c-prex[c+x-w-1][i];
                const auto pins=w-cnt[i];
                (f[x]+=fx[x-w]*math.C(pfree,pins))%=MOD;
            }
        }
        cout<<f[m]<<'\n';
    }();
    return 0;
}
