#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class basic_math{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
vector<vector<int>> gr;
auto dfs(int u,int qs,int f=-1){
    auto sumf=0ll,sumg=0ll;
    if(qs&(1<<u)) return pair(0ll,0ll);
    for(auto&i:gr[u]) if(i!=f){
        auto[fi,gi]=dfs(i,qs,u);
        (sumf+=fi)%=MOD;(sumg+=gi)%=MOD;
    }
    const auto deg=(lint)(gr[u].size());
    return pair(
        math.inv(MOD+deg-sumf),
        (deg+sumg)*math.inv(MOD+deg-sumf)%MOD
    );
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,u;cin>>n>>q>>u;--u;
    gr.resize(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    vector<lint> f(1<<n);
    cir(s,0,(1<<n)){
        f[s]=((__builtin_popcount(s)&1)?
            1:MOD-1)*dfs(u,s).second%MOD;
    }
    cir(i,0,q){
        int k;cin>>k;
        auto qs=0;
        cir(i,0,k){
            int x;cin>>x;qs|=(1<<(x-1));
        }
        auto ans=0ll;
        for(auto s=qs;s;s=(s-1)&qs) (ans+=f[s])%=MOD;
        cout<<ans<<'\n';
    }
    return 0;
}
