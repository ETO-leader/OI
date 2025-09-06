#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("tree.in");
ofstream ouf("tree.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
using lint=long long;
static constexpr auto ups=21;
class dsu{
private:
    vector<int> f,siz;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto usiz(int u){return siz[findset(u)];}
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        siz[v]+=siz[u];
        f[u]=v;
    }
    dsu(int _n,auto _sz):f(_n),siz(_sz){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        int n;inf>>n;
        vector<int> dep(n);
        vector<vector<int>> up(ups,vector<int>(n)),udep(n),vx(n);
        cir(u,1,n){
            inf>>up[0][u];--up[0][u];
            cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
            dep[u]=dep[up[0][u]]+1;
            udep[dep[u]].emplace_back(u);
            vx[up[0][u]].emplace_back(u);
        }
        udep[0].emplace_back(0);
        vector<lint> a(n+1);
        for(auto&i:a) inf>>i;
        auto ans=0ll;
        vector<int> dfn(n),siz(n);
        [&]{
            auto cnt=-1;
            auto dfsdfn=[&](auto __self,int u)->int {
                dfn[u]=++cnt;siz[u]=1;
                for(auto&i:vx[u]) siz[u]+=__self(__self,i);
                ans+=a[siz[u]];
                return siz[u];
            };
            dfsdfn(dfsdfn,0);
        }();
        auto lcasd=[&](int u,int v){
            for(auto i=ups-1;~i;--i) if(up[i][u]!=up[i][v]) u=up[i][u],v=up[i][v];
            return up[0][u];
        };
        for(auto&x:udep) sort(x.begin(),x.end(),[&](int u,int v){return dfn[u]<dfn[v];});
        vector<vector<pair<int,int>>> mrgt(n);
        cir(d,0,n){
            const auto k=(int)(udep[d].size());
            cir(i,0,k-1) mrgt[dep[udep[d][i]]-dep[lcasd(udep[d][i],udep[d][i+1])]].emplace_back(udep[d][i],udep[d][i+1]);
        }
        dsu qwq(n,siz);
        ouf<<ans<<' ';
        cir(t,1,n){
            for(auto&[u,v]:mrgt[t]){
                ans-=a[qwq.usiz(u)];
                ans-=a[qwq.usiz(v)];
                ans+=a[qwq.usiz(u)+qwq.usiz(v)];
                ans+=a[0];
                qwq.merge(u,v);
            }
            for(auto&v:udep[t-1]) if(qwq.findset(v)==v){
                ans-=a[qwq.usiz(v)];
                ans+=a[0];
            }
            ouf<<ans<<' ';
        }
        ouf<<'\n';
    }();
    return 0;
}
