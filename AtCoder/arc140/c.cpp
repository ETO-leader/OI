#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,x;cin>>n>>x;--x;
    vector<int> vis(n);
    vector<int> ans;
    ans.emplace_back(x+1);
    vis[x]=true;
    if(x!=n/2&&x!=n/2-(!(n&1))){
        x=n/2;
        ans.emplace_back(x+1);
        vis[x]=true;
    }
    auto lc=0,rc=0;
    cir(i,0,x) lc+=(!vis[i]);
    cir(i,x+1,n) rc+=(!vis[i]);
    auto stp=0;
    cir(i,1,n+1){
        stp^=1;
        auto nx=((stp^(lc<rc))?x-i:x+i);
        while(nx>-1&&nx<n&&vis[nx]) nx+=((stp^(lc<rc))?-1:1),++i;
        if(nx<0||nx>n-1) break;
        x=nx;
        ans.emplace_back(x+1);
        vis[x]=true;
    }
    cir(i,0,n) if(!vis[i]) ans.emplace_back(i+1);
    for(auto&x:ans) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
