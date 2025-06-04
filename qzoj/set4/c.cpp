#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector a(n,vector<int>(n));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<pair<int,pair<int,int>>> x;
    cir(i,0,n) cir(j,0,n){
        if(i+1<n) x.emplace_back(a[i][j]+a[i+1][j],pair(i*n+j,(i+1)*n+j));
        if(j+1<n) x.emplace_back(a[i][j]+a[i][j+1],pair(i*n+j,i*n+j+1));
    }
    ranges::sort(x,greater<pair<int,pair<int,int>>>());
    auto ans=0;
    vector<bool> vis(n*n);
    auto dfs=[&](auto __self,int u,int c,int w){
        if(c==k) return ans=max(ans,w),void();
        if(u==(int)(x.size())) return;
        if(w+x[u].first*(k-c)<ans+1) return;
        const auto[uw,up]=x[u];
        const auto[ux,vx]=up;
        if((!vis[ux])&&(!vis[vx])){
            vis[ux]=true;vis[vx]=true;
            __self(__self,u+1,c+1,w+uw);
            vis[ux]=false;vis[vx]=false;
        }
        __self(__self,u+1,c,w);
    };
    dfs(dfs,0,0,0);
    auto sum=0ll;
    for(auto&x:a) for(auto&i:x) sum+=i;
    cout<<sum-ans<<'\n';
    return 0;
}
