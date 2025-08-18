#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector<int> a(n*k);
    for(auto&i:a) cin>>i,--i;
    vector<int> vis(n*k),prv(n*k);
    cir(i,0,n*k) prv[a[i]]=i;
    vector f(n*k,vector<int>(n*k,-1));
    auto ans=0;
    vector<int> ord(n*k),ins(n*k);
    cir(i,0,n*k) if(!vis[i]){
        vector<int> x;
        auto p=i;
        while(!vis[p]) x.emplace_back(p),vis[p]=true,p=a[p];
        for(auto&i:x) ins[i]=true;
        cir(i,0,(int)(x.size())) ord[x[i]]=i;
        auto dfs=[&](auto __self,int l,int r){
            if(f[l][r]>-1) return f[l][r];
            if(l==r) return 0;
            f[l][r]=__self(__self,l,a[r]);
            auto v=r%n-n;
            cir(i,0,k) if(v+=n;ins[v]&&v!=r){
                if(ord[r]<ord[l]&&(ord[v]<ord[r]||ord[v]>ord[l])) continue;
                if(ord[r]>ord[l]&&(ord[v]>ord[l]&&ord[v]<ord[r])) continue;
                if(v!=l) f[l][r]=max(f[l][r],__self(__self,l,v)+(prv[v]!=r?__self(__self,prv[v],a[r]):0)+1);
                else f[l][r]=max(f[l][r],(prv[v]!=r?__self(__self,prv[v],a[r]):0)+1);
            }
            return f[l][r];
        };
        auto uans=0;
        cir(i,0,/*(int)(x.size())*/1) uans=max(uans,dfs(dfs,x[i],x[(i+1)%(int)(x.size())]));
        for(auto&i:x) ins[i]=false;
        ans+=uans; 
    }
    cout<<ans<<'\n';
    return 0;
}
