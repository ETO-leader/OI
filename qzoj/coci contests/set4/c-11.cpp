#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector<vector<int>> a(n,vector<int>(n));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<pair<int,pair<int,int>>> x;
    cir(i,0,n) cir(j,0,n){
        if(i+1<n) x.push_back(make_pair(a[i][j]+a[i+1][j],make_pair(i*n+j,(i+1)*n+j)));
        if(j+1<n) x.push_back(make_pair(a[i][j]+a[i][j+1],make_pair(i*n+j,i*n+j+1)));
    }
    sort(x.begin(),x.end(),greater<pair<int,pair<int,int>>>());
    int ans=0;
    vector<bool> vis(n*n);
    function<void(int,int,int)> dfs=[&](int u,int c,int w){
        if(c==k){ans=max(ans,w);return;}
        if(u==(int)(x.size())) return;
        if(w+x[u].first*(k-c)<ans+1) return;
        int uw=x[u].first,ux=x[u].second.first,vx=x[u].second.second;
        if((!vis[ux])&&(!vis[vx])){
            vis[ux]=true;vis[vx]=true;
            dfs(u+1,c+1,w+uw);
            vis[ux]=false;vis[vx]=false;
        }
        dfs(u+1,c,w);
    };
    dfs(0,0,0);
    long long sum=0;
    for(auto&x:a) for(auto&i:x) sum+=i;
    cout<<sum-ans<<'\n';
    return 0;
}
