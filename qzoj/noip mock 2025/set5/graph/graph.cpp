#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("graph.in");
ofstream ouf("graph.out");
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) [&]{
        int n,m,q,p;inf>>n>>m>>q>>p;
        vector<vector<pair<int,lint>>> vx(n);
        vector<int> inc(n);
        cir(i,0,m){
            int u,v;lint w;inf>>u>>v>>w;--u;--v;
            vx[u].emplace_back(v,w);
            ++inc[v];
        }
        auto up=1ll;
        static constexpr auto maxr=(lint)(1.1e17l);
        vector<pair<lint,lint>> vrg;
        while(up<maxr){
            const auto vw=up/(p-1)+1;
            vrg.emplace_back(up,vw*50);
            up=vw*50+1;
        }
        map<pair<lint,lint>,vector<tuple<int,int,lint>>> qs;
        string ans(q,'0');
        cir(i,0,q){
            int x;lint c;inf>>x>>c;--x;
            for(auto&[l,r]:vrg) if(l-1<c&&c-1<r) qs[{l,r}].emplace_back(i,x,c);
        }
        vector<vector<lint>> vals(n);
        vector<int> uinc;
        vector<lint> nval;
        for(auto&[l,r]:vrg) if(!(qs[{l,r}].empty())){
            const auto cv=l/(p-1);
            const auto av=r/(p-1);
            for(auto&x:vals) x.clear();
            uinc=inc;
            auto emplace=[&](vector<lint> xval,int v){
                nval=vals[v];
                for(auto&x:xval) nval.emplace_back(x);
                nval.emplace_back(r+av+7);
                inplace_merge(nval.begin(),nval.begin()+vals[v].size(),nval.end());
                auto las=-_infl;
                vals[v].clear();
                cir(i,0,(int)(nval.size())){
                    if(nval[i]>r+av+3) break;
                    if(nval[i+1]<las+cv) continue;
                    vals[v].emplace_back(nval[i]);
                    las=nval[i];
                }
            };
            auto dfs=[&](auto __self,int u)->void {
                for(auto&[v,w]:vx[u]){
                    auto ux=vals[u];
                    for(auto&c:ux) c+=w;
                    emplace(ux,v);
                    if(!(--uinc[v])) __self(__self,v);
                }
            };
            vals[0].emplace_back(0);
            dfs(dfs,0);
            for(auto&[id,x,c]:qs[{l,r}]){
                auto uans=false;
                for(auto&w:vals[x]) uans|=(w>c-1&&w<p*c/(p-1)+1);
                ans[id]+=uans;
            }
        }
        ouf<<ans<<'\n';
    }();
    return 0;
}
