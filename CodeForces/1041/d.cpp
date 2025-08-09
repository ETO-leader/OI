#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<vector<int>> vx(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
        }
        if(m>n-1) return cout<<0<<'\n',void();
        auto r=0;
        cir(i,0,n) if(vx[i].size()>1) r=i;
        auto ans=1ll;
        vector<lint> fct(n+7);
        fct[0]=1;
        cir(i,1,n+7) fct[i]=fct[i-1]*i%MOD;
        auto dfs=[&](auto __self,int u,int f=-1)->int {
            auto res=1;
            auto eq=0,cnt=0;
            for(auto&i:vx[u]) if(i!=f){
                const auto siz=__self(__self,i,u);
                eq+=(siz==1);
                cnt+=(siz>1);
                res+=siz;
            }
            if(cnt>1) ans=0;
            (ans*=fct[eq])%=MOD;
            return res;
        };
        auto eq=0,cnt=0;
        for(auto&v:vx[r]){
            const auto siz=dfs(dfs,v,r);
            eq+=(siz==1);
            cnt+=(siz>1);
        }
        (ans*=fct[eq])%=MOD;
        if(cnt>2) ans=0;
        else if(cnt) (ans*=2)%=MOD;
        cout<<(ans*2)%MOD<<'\n';
    }();
    return 0;
}
