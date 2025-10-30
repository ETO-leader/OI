#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
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
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    constexpr auto C(auto a,auto b) const{
        return a>b-1&&b>-1?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
    constexpr auto fact(int x) const{return fct[x];}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    math.init(n+7);
    vector<int> a(n);
    for(auto&x:a) cin>>x,--x;
    vector<vector<int>> v(n),vx(n);
    cir(i,0,n) if(a[i]>-1){
        v[a[i]].emplace_back(i);
        vx[a[i]].emplace_back(i);
        vx[i].emplace_back(a[i]);
    }
    vector<int> vis(n);
    auto cover=[&](auto __self,int u){
        if(vis[u]) return;
        vis[u]=true;
        for(auto&x:vx[u]) __self(__self,x);
    };
    cir(i,0,n) if(a[i]<0) cover(cover,i);
    auto xcnt=0;
    cir(i,0,n) if(!vis[i]) ++xcnt,cover(cover,i);
    auto count=[&](auto __self,int u)->int {
        auto res=1;
        for(auto&x:v[u]) res+=__self(__self,x);
        return res;
    };
    vector<lint> f(n+1);
    f[0]=1;
    cir(i,0,n) if(a[i]<0){
        const auto x=count(count,i);
        for(auto w=n-1;~w;--w) (f[w+1]+=f[w]*x)%=MOD;
    }
    const auto ucnt=ranges::count(a,-2);
    auto ans=(xcnt*math.qpow(n,ucnt))%MOD;
    cir(i,1,ucnt+1) (ans+=f[i]*math.qpow(n,ucnt-i)%MOD*math.fact(i-1))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
