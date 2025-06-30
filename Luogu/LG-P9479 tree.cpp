#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
auto calc(int n,int m,int k){
    if(!k){
        auto res=1ll;
        cir(i,n,n+m) (res*=(i*2-1))%=MOD;
        return res;
    }
    vector<lint> f(1<<k);
    const auto fs=(1<<k)-1;
    f[0]=1;
    cir(i,n,n+m){
        vector<lint> g(1<<k);
        cir(s,(1<<(k-1)),(1<<k)) (g[(s<<1)&fs]+=f[s])%=MOD;
        cir(s,0,(1<<(k-1))){
            for(auto p=k-2;~p;--p) if((s>>p)&1){
                (g[(s^(1<<p))<<1]+=f[s])%=MOD;
            }
            (g[s<<1]+=f[s]*((i+popcount((uint)(s)))*2-1))%=MOD;
            (g[(s<<1)|1]+=f[s]*(i+popcount((uint)(s))-1))%=MOD;
        }
        f=g;
    }
    return f[0];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,T;cin>>c>>T;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;
        cir(i,0,n-1){
            int f;cin>>f;
        }
        cout<<calc(n,m,k)<<'\n';
    }();
    return 0;
}
