#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        lint n,m;cin>>n>>m;
        if(n>60){
            cout<<0<<'\n';
        }else{
            vector<lint> f(62);
            cir(i,0,62) f[i]=max<lint>(min(m-(1ll<<i)+1,(1ll<<i)),0);
            cir(i,0,n-1){
                const auto g=f;
                ranges::fill(f,0);
                for(auto w=61;~w;--w) cir(v,w+1,62){
                    (f[v]+=g[w]*(max<lint>(min(m-(1ll<<v)+1,(1ll<<v)),0)%MOD))%=MOD;
                }
            }
            cout<<accumulate(f.begin(),f.end(),0ll)%MOD<<'\n';
        }
    }();
    return 0;
}
