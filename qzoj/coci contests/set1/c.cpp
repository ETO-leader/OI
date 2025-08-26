#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxl=(int)(1e5);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<lint>> pos(n),tl(n);
    vector<int> tp(n);
    cir(i,0,n){
        int c;cin>>c;
        pos[i].resize(c);
        tl[i].resize(c);
        auto cur=0ll;
        for(auto&i:pos[i]) cin>>i;
        cir(x,1,c) tl[i][x]=(cur+=abs(pos[i][x]-pos[i][x-1]));
        if(c==1) pos[i].emplace_back(pos[i][0]),tl[i].emplace_back(0);
        tp[i]=(pos[i][1]>pos[i][0]);
    }
    auto bruteforce=[&](int u,int v){
        if(tl[u].size()<tl[v].size()) swap(u,v);
        auto ntl=tl[v],npos=pos[v];
        auto uposa=[&](lint t){
            const auto lpos=prev(upper_bound(tl[u].begin(),tl[u].end(),t))-tl[u].begin();
            return pos[u][lpos]+(tp[u]?1:-1)*(lpos&1?-1:1)*(t-tl[u][lpos]);
        };
        if(ntl.back()>tl[u].back()){
            while(ntl.back()>tl[u].back()) ntl.pop_back(),npos.pop_back();
            const auto sdir=(tp[v]?1:-1);
            const auto dir=sdir*(ntl.size()&1?1:-1);
            npos.emplace_back(npos.back()+(tl[u].back()-ntl.back())*dir);
            ntl.emplace_back(tl[u].back());
        }
        auto cnt=0;
        auto uxpos=ntl;
        for(auto&i:uxpos) i=uposa(i);
        cir(i,1,(int)(npos.size())) if((i&1)==tp[v]){
            const auto s=uxpos[i-1],t=uxpos[i];
            cnt+=(s>npos[i-1]-1&&t<npos[i]+1);
        }else{
            const auto s=uxpos[i-1],t=uxpos[i];
            cnt+=(s<npos[i-1]+1&&t>npos[i]-1);
        }
        return cnt;
    };
    map<pair<int,int>,int> ans;
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        if(tl[u].size()<tl[v].size()) swap(u,v);
        auto sign=make_pair(min(u,v),max(u,v));
        if(ans.count(sign)){
            cout<<ans[sign]<<'\n'; 
        }else{
            auto uans=0;
            uans=bruteforce(u,v);
            ans[sign]=uans;
            cout<<uans<<'\n';
        }
    }
    return 0;
}
