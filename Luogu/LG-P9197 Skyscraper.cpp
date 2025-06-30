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
    constexpr auto invfact(auto x) const{return ifct[x];}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,l;cin>>n>>l;
    math.init(n+7);
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    ranges::sort(a);
    vector f(l+1,vector(n+1,vector(2,vector<lint>(2))));
    auto las=a[0];
    f[0][1][0][0]=f[0][1][0][1]=f[0][1][1][0]=1;
    if(n==1) f[0][1][1][1]=1;
    cir(i,1,n){
        const auto h=f;
        for(auto&x:f) for(auto&c:x) for(auto&i:c) fill(i.begin(),i.end(),0);
        cir(ul,0,l+1) cir(g,1,n+1) cir(ll,0,2) cir(lr,0,2) if(h[ul][g][ll][lr]){
            const auto dv=a[i]-las;
            const auto nl=(g*2-ll-lr)*dv+ul;
            if(nl>l) continue;
            (f[nl][g][ll][lr]+=h[ul][g][ll][lr]*(g*2-ll-lr))%=MOD;
            if(g) (f[nl][g-1][ll][lr]+=h[ul][g][ll][lr]*(g-1))%=MOD;
            if(g<n) (f[nl][g+1][ll][lr]+=h[ul][g][ll][lr]*(g+1-ll-lr))%=MOD;
            if(!ll) (f[nl][g][true][lr]+=h[ul][g][ll][lr])%=MOD;
            if(!lr) (f[nl][g][ll][true]+=h[ul][g][ll][lr])%=MOD;
            if(g<n&&(!ll)) (f[nl][g+1][true][lr]+=h[ul][g][ll][lr])%=MOD;
            if(g<n&&(!lr)) (f[nl][g+1][ll][true]+=h[ul][g][ll][lr])%=MOD;
        }
        las=a[i];
    }
    auto ans=0ll;
    cir(v,0,l+1) (ans+=f[v][1][true][true])%=MOD;
    map<int,int> cnt;
    for(auto&i:a) ++cnt[i];
    for(auto&[x,y]:cnt) (ans*=math.invfact(y))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
