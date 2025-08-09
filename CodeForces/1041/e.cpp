#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;
        vector<int> val(n);
        for(auto&i:val) cin>>i;
        vector<int> w(n);
        for(auto&i:w) cin>>i;
        vector<unordered_set<int>> cnt(n);
        vector<vector<int>> vx(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
        }
        auto color=[&](auto __self,int u,int c)->void {
            for(auto&i:vx[u]) __self(__self,i,c);
            w[u]=c;
        };
        vector<int> siz(n);
        auto init=[&](auto __self,int u,int f=-1)->int {
            siz[u]=1;
            if(f>-1) vx[u].erase(ranges::find(vx[u],f));
            for(auto&i:vx[u]) siz[u]+=__self(__self,i,u);
            ranges::sort(vx[u].begin(),vx[u].end(),[&](auto&a,auto&b){
                return siz[a]>siz[b];
            });
            return siz[u];
        };
        auto ans=accumulate(val.begin(),val.end(),0ll);
        auto dfs=[&](auto __self,int u)->void {
            unordered_set<int> cap;
            auto x=-1;
            auto emp=false;
            if(!vx[u].empty()){
                __self(__self,vx[u][0]);
                if(cnt[vx[u][0]].empty()) emp=true;
                cnt[u].swap(cnt[vx[u][0]]);
                x=vx[u][0];
            }
            for(auto&i:vx[u]) if(i!=x){
                __self(__self,i);
                for(auto&w:cnt[i]){
                    if(cnt[u].contains(w)) cap.emplace(w);
                    cnt[u].emplace(w);
                }
            }
            if(w[u]) cnt[u].emplace(w[u]);
            if(!cap.size()){
                ans-=val[u];
                if((!w[u])&&cnt[u].size()) w[u]=*cnt[u].begin();
            }else if(cap.size()==1){
                if(w[u]==*cap.begin()||(!w[u])) ans-=val[u];
                if(!w[u]) w[u]=*cap.begin();
            }else{
                if(!w[u]) w[u]=*cap.begin();
            }
            if(!cnt[u].empty()){
                const auto col=w[u];
                if(emp) color(color,x,col);
                for(auto&i:vx[u]) if(i!=x&&cnt[i].empty()) color(color,i,col);
            }
        };
        init(init,0);
        dfs(dfs,0);
        if(cnt[0].empty()) color(color,0,1);
        cout<<ans<<'\n';
        for(auto&i:w) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
