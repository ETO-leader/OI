#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto lowbit(auto x){return x&(-x);}
constexpr auto kth_ancestor(int x,int y,int k){
    if(!k) return pair(x,y);
    if(!x) return pair(x,y-k);
    if(!y) return pair(x-k,y);
    return lowbit(x)>lowbit(y)?
        kth_ancestor(x,y-min(lowbit(y),k),k-min(lowbit(y),k)):
        kth_ancestor(x-min(lowbit(x),k),y,k-min(lowbit(x),k));
}
constexpr auto is_ancestor(int x,int y,int qx,int qy){
    const auto dis=qx-x+qy-y;
    return dis>-1&&kth_ancestor(qx,qy,dis)==pair(x,y);
}
constexpr auto lca(int x,int y,int qx,int qy){
    auto l=0,r=x+y,ans=-1;
    while(l-1<r){
        const auto mid=(l+r)/2;
        const auto[a,b]=kth_ancestor(x,y,mid);
        is_ancestor(a,b,qx,qy)?((r=mid-1),(ans=mid)):(l=mid+1);
    }
    return kth_ancestor(x,y,ans);
}
constexpr auto distance(int x,int y,int ux,int uy){
    const auto[qx,qy]=lca(x,y,ux,uy);
    return (int64_t)(x)+y+ux+uy-qx*2-qy*2;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<int,int>> u(n);
    for(auto&[x,y]:u) cin>>x>>y;
    mt19937 rng(random_device().operator()());
    auto ans=numeric_limits<int64_t>::max();
    cir(i,0,6){
        const auto c=uniform_int_distribution<int>(0,n-1)(rng);
        const auto[x,y]=u[c];
        auto l=0,r=x+y,bans=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            const auto[ux,uy]=kth_ancestor(x,y,mid);
            auto cnt=n;
            for(auto&[qx,qy]:u) cnt-=is_ancestor(ux,uy,qx,qy);
            cnt<n/2+1?((r=mid-1),(bans=mid)):(l=mid+1);
        }
        const auto[ux,uy]=kth_ancestor(x,y,bans);
        auto uans=(int64_t)(0);
        for(auto&[x,y]:u) uans+=distance(x,y,ux,uy);
        ans=min(ans,uans);
    }
    cout<<ans<<'\n';
    return 0;
}
