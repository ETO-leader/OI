#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<vector<int>> gr(n),dgr(n);
        cir(i,0,n) if(i+a[i]>-1&&i+a[i]<n){
            gr[i].emplace_back(i+a[i]);
            gr[i+a[i]].emplace_back(i);
            dgr[i].emplace_back(i+a[i]);
        }
        vector<int> lnk(n);
        [&](this auto __self,int u){
            if(lnk[u]) return;
            lnk[u]=true;
            for(auto&x:gr[u]) __self(x);
        }(0);
        vector<int> lnkcirc(n);
        vector<int> vis(n);
        cir(i,0,n) [&](this auto __self,int u)->bool {
            if(vis[u]==-1) return lnkcirc[u]=true;
            if(vis[u]) return lnkcirc[u];
            vis[u]=-1;
            for(auto&x:dgr[u]) if(__self(x)) lnkcirc[u]=true;
            vis[u]=1;
            return lnkcirc[u];
        }(i);
        ranges::fill(vis,false);
        auto lasvis=-1;
        [&](this auto __self,int u){
            if(vis[u]) return;
            lasvis=u;
            vis[u]=true;
            for(auto&x:dgr[u]) __self(x);
        }(0);
        const auto gz=ranges::count(vis,true);
        const auto ncir=n-ranges::count(lnkcirc,true);
        const auto ns=ranges::count(lnk,true);
        auto xcnt=0ll;
        cir(i,0,n) xcnt+=(vis[i]&&lnkcirc[i]);
        auto ans=0ll;
        if(lnkcirc[0]){
            ans=gz*(ncir+n+1);
        }else{
            ans=(n-gz)*(n*2+1);
            [&](this auto __self,int u,int f=-1)->int {
                auto res=1;
                for(auto&x:gr[u]) if(x!=f) res+=__self(x,u);
                if(vis[u]) ans+=(n*2+1-res-(n-ncir));
                return res;
            }(lasvis);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
