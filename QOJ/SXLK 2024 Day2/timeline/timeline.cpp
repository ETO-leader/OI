#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("timeline.in");
ofstream ouf("timeline.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=unsigned long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    constexpr auto lowbit(auto x){return x&(-x);}
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,k;inf>>n>>m>>k;
    vector<int> v(1<<n),vu(n);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        vu[u]|=(1<<v);
    }
    cir(s,0,(1<<n)) cir(x,0,n) if(s&(1<<x)) v[s]|=vu[x];
    const auto vaild=[&](auto s,auto t){
        return !(v[t]&s);
    };
    vector<lint> c(1<<n);c[0]=1;
    cir(s,1,1<<n) cir(x,0,n) if(s&(1<<x)){
        c[s]+=c[s^(1<<x)]*(vaild(1<<x,s^(1<<x)));
    }
    vector f(n+1,vector<lint>(1<<n));
    vector g(n+1,vector<lint>(1<<n));
    f[0][0]=g[0][0]=1;
    cir(s,0,(1<<n)) for(auto x=s;x;x=(x-1)&s){
        if(math.lowbit(s)!=math.lowbit(x)) continue;
        if((!vaild(s^x,x))||(!vaild(x,s^x))) continue;
        cir(w,1,n+1) (g[w][s]+=g[w-1][s^x]*c[x])%=MOD;
    }
    cir(s,0,(1<<n)) for(auto x=s;x;x=(x-1)&s){
        const auto limw=popcount((uint)(s));
        cir(r,1,limw+1) if(g[r][x]&&vaild(s^x,x)){
            const auto v=((r&1)?1:MOD-1)*g[r][x]%MOD;
            cir(w,r,limw+1) (f[w][s]+=v*f[w-r][s^x])%=MOD;
        }
    }
    auto fact=[](auto x){
        auto res=1ull;
        cir(i,1,x+1) (res*=i)%=MOD;
        return res;
    };
    auto binom=[fact](auto a,auto b){
        return a>b-1?fact(a)*math.inv(fact(b))%MOD*math.inv(fact(a-b))%MOD:0;
    };
    auto ans=0ull;
    cir(i,1,n+1) (ans+=f[i][(1<<n)-1]*fact(i)%MOD*[&]{
        auto res=0ull;
        cir(x,0,i) (res+=(x&1?MOD-1:1)*fact(i-x+k)%MOD*math.inv(fact(i-x))%MOD*binom(i-1,x))%=MOD;
        return res;
    }())%=MOD;
    ouf<<ans*math.inv(fact(n+k))%MOD<<'\n';
    return 0;
}
