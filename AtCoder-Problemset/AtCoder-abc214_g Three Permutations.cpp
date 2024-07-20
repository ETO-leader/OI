#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,lint b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x) const{
        return qpow(x,MOD-2);
    }
    auto registerfct(int n){
        fct.resize(n,1);ifct.resize(n);
        cir(i,1,n) fct[i]=(fct[i-1]*i)%MOD;
        cir(i,0,n) ifct[i]=inv(fct[i]);
    }
    auto fact(int x) const{return fct[x];}
    auto C(int a,int b) const{
        if(a<0||b<0||a<b) return 0ll; 
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> p(n),q(n);
    for(auto&i:p) cin>>i,--i;
    for(auto&i:q) cin>>i,--i;
    vector<int> nxt(n);
    cir(i,0,n) nxt[p[i]]=q[i];
    math.registerfct(n*2+7);
    vector<bool> vis(n);
    auto pres=0;
    vector<lint> f(n+7);f[0]=1;
    cir(i,0,n) if(!vis[i]){
        auto len=0;
        for(auto u=i;!vis[u];u=nxt[u]) ++len,vis[u]=true;
        if(len==1){
            for(auto x=(++pres);x;--x) (f[x]+=f[x-1])%=MOD;
            continue;
        }
        vector<lint> g(pres+len+3);
        cir(x,0,pres+1) cir(c,0,len+1){
            (g[x+c]+=f[x]*(math.C(len*2-c,c)+math.C(len*2-c-1,c-1)))%=MOD;
        }
        ranges::copy(g,f.begin());
        pres+=len;
    }
    auto ans=0ll;
    cir(i,0,n+1) (ans+=((i&1)?MOD-f[i]*math.fact(n-i)%MOD:f[i]*math.fact(n-i)%MOD))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
