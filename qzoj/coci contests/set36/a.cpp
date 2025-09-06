#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;lint m;cin>>n>>m;
    vector<pair<lint,lint>> rg;
    cir(i,0,n){
        int u,v;cin>>u>>v;--u;--v;
        if(u>v) rg.emplace_back(v,u);
    }
    auto ans=m;
    sort(rg.begin(),rg.end());
    auto las=-1ll;
    for(auto&[l,r]:rg) ans+=max((r-max(las,l))*2,0ll),las=max(las,r);
    cout<<ans<<'\n';
    return 0;
}
