#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k,x,y;cin>>n>>k>>x>>y;
        vector<lint> a(n),b(n),c(n),d(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        for(auto&i:c) cin>>i;
        for(auto&i:d) cin>>i;
        vector<vector<pair<int,int>>> sl(1<<k);
        cir(i,0,n){
            auto invs=0,oks=0;
            cir(p,0,k) if(!((a[i]>>p)&1)){
                if((y>>p)&1) invs|=1<<p;
                else oks|=1<<p;
            }
            sl[invs].emplace_back(oks,c[i]);
        }
        cir(i,0,n){
            auto invs=0,oks=0;
            cir(p,0,k) if((b[i]>>p)&1){
                if((y>>p)&1) oks|=1<<p;
                else invs|=1<<p;
            }
            sl[invs].emplace_back(oks,d[i]);
        }
        vector<lint> f(1<<k,_infl);
        f[0]=0;
        auto ans=_infl;
        vector<lint> vals(1<<k,_infl);
        vector<vector<pair<int,int>>> info(1<<k);
        cir(s,0,(1<<k)){
            info[s].reserve(1<<(k-popcount((uint)(s))));
            for(auto&[v,w]:sl[s]) vals[v]=min<lint>(vals[v],w);
            const auto lst=((1<<k)-1)^s;
            cir(i,0,k) if(s&(1<<i)){
                for(auto&[v,w]:info[s^(1<<i)]) vals[v&lst]=min<lint>(vals[v&lst],w);
            }
            for(auto ns=lst;~ns;ns=(ns?((ns-1)&lst):-1)) if(vals[ns]!=_infl){
                info[s].emplace_back(ns,vals[ns]);
                f[s|ns]=min(f[s|ns],f[s]+vals[ns]);
                vals[ns]=_infl;
            }
            auto ok=true;
            cir(i,0,k) if(!(s&(1<<i))) ok&=(((x>>i)&1)==((y>>i)&1));
            if(ok) ans=min(ans,f[s]);
        }
        cout<<(ans==_infl?-1:ans)<<'\n';
    }();
    return 0;
}
