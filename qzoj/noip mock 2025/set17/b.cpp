#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<uint64_t> vs(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        vs[u]|=((uint64_t)(1)<<v);
        vs[v]|=((uint64_t)(1)<<u);
    }
    cir(i,0,n) vs[i]|=((uint64_t)(1)<<i);
    vector<pair<uint64_t,int>> vl;
    const auto targetl=min(n,15);
    auto dfsl=[&](auto __self,int u,uint64_t s,int c){
        if(u==targetl) return vl.emplace_back(s,c),void();
        __self(__self,u+1,s,c);
        __self(__self,u+1,s^vs[u],c+1);
    };
    auto ans=_inf;
    auto dfsr=[&](auto __self,int u,uint64_t s,int c){
        if(u==n){
            const auto targets=((uint64_t)(1)<<n)-1;
            const auto lb=lower_bound(vl.begin(),vl.end(),make_pair(targets^s,-1));
            if(lb!=vl.end()&&(lb->first^s)==targets) ans=min(ans,c+lb->second);
            return;
        }
        __self(__self,u+1,s,c);
        __self(__self,u+1,s^vs[u],c+1);
    };
    dfsl(dfsl,0,0,0);
    sort(vl.begin(),vl.end());
    dfsr(dfsr,targetl,0,0);
    cout<<ans<<'\n';
    return 0;
}

