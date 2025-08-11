#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m,n;cin>>m>>n;
    vector<int> siz(n+1),dfn;
    vector<vector<int>> vx(n+1);
    vector<lint> v(n+1),p(n+1);
    cir(i,1,n+1){
        int f;cin>>v[i]>>p[i]>>f;
        vx[f].emplace_back(i);
    }
    auto dfs=[&](auto __self,int u)->int {
        dfn.emplace_back(u);
        siz[u]=1;
        for(auto&i:vx[u]) siz[u]+=__self(__self,i);
        return siz[u];
    };
    dfs(dfs,0);
    vector<vector<lint>> f(n+2,vector<lint>(m+1,-_infl));
    fill(f[0].begin(),f[0].end(),0ll);
    cir(x,0,n+1){
        const auto i=dfn[x];
        cir(w,0,m+1) f[x+siz[i]][w]=max(f[x+siz[i]][w],f[x][w]);
        cir(w,0,m+1) if(w+v[i]<m+1) f[x+1][w+v[i]]=max(f[x+1][w+v[i]],f[x][w]+v[i]*p[i]);
    }
    cout<<f[n+1][m]<<'\n';
    return 0;
}
