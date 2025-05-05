#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        vector<lint> fct(n+7,1);
        cir(i,1,n+7) fct[i]=fct[i-1]*i%MOD;
        for(auto&i:a) cin>>i;
        map<vector<int>,int> cnt;
        vector<vector<int>> nds{a};
        cir(i,0,n-1){
            for(auto&i:a) cin>>i;
            ++cnt[a];
            nds.emplace_back(a);
        }
        vector<int> sum(n);
        cir(i,0,n) sum[i]=accumulate(nds[i].begin(),nds[i].end(),0);
        vector<int> ord(n);
        iota(ord.begin(),ord.end(),0);
        ranges::sort(ord,[&](auto&a,auto&b){
            return sum[a]==sum[b]?a<b:sum[a]>sum[b];
        });
        vector<int> f(n),dep(n,n+7);
        ord.erase(ord.begin());
        dep[0]=0;
        for(auto&u:ord){
            auto mx=pair(0,0);
            cir(i,0,n) if(nds[u][i]) if(dep[i]<n+7) mx=max(mx,pair(dep[i],i));
            dep[u]=mx.first+1;
            f[u]=mx.second;
        }
        vector mp(n,vector<int>(n));
        cir(i,0,n){
            auto u=i;
            while(u) mp[u][i]=mp[i][u]=1,u=f[u];
            mp[u][i]=mp[i][u]=1;
        }
        if(mp!=nds) return cout<<0<<'\n',void();
        auto ans=1ll;
        for(auto&[a,b]:cnt) (ans*=fct[b])%=MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
