#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
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
        return a>b-1&&b>-1?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        math.init(n+m+7);
        vector<pair<int,int>> x(k);
        for(auto&[a,b]:x) cin>>a>>b;
        x.emplace_back(0,0);
        x.emplace_back(n,m);
        ranges::sort(x,[](auto a,auto b){
            return a.first+a.second<b.first+b.second;
        });
        vector w(k+2,vector<lint>(k+2));
        cir(i,0,k+2) cir(j,i+1,k+2){
            const auto[ai,bi]=x[i];
            const auto[aj,bj]=x[j];
            w[i][j]=math.C(aj-ai+bj-bi,aj-ai);
            cir(k,i+1,j){
                const auto[ak,bk]=x[k];
                (w[i][j]+=MOD-w[i][k]*math.C(aj-ak+bj-bk,aj-ak)%MOD)%=MOD;
            }
        }
        vector<lint> f(k+2);
        for(auto i=k;~i;--i) cir(j,i+1,k+2){
            const auto[ai,bi]=x[i];
            const auto[aj,bj]=x[j];
            if(ai<aj+1&&bi<bj+1) (f[i]+=w[i][j]*(f[j]+((aj-ai)*2+bj-bi)*math.C(n-aj+m-bj,m-bj)%MOD)*2)%=MOD;
        }
        cout<<f[0]*math.inv(math.C(n+m,m))%MOD*math.inv(2)%MOD<<'\n';
    }();
    return 0;
}
