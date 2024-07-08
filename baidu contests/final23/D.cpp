#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI nxt(n+1);
    cir(i,1,n+1) cin>>nxt[i];
    VI vis(n+1);
    function<bool(int)> dfs=[&](int p){
        if(!nxt[p]) return true;
        if(vis[p]) return false;
        vis[p]=true;
        return dfs(nxt[p]);
    };
    int ans=0;
    cir(i,1,n+1){
        fill(vis.begin(),vis.end(),false);
        ans^=i*dfs(i);
    }
    cout<<ans<<'\n';
    return 0;
}
