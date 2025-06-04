#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<pair<int,int>> es(m);
    for(auto&[u,v]:es) cin>>u>>v,--u,--v;
    auto ans=0;
    cir(s,0,(1<<m)){
        vector<int> us(n);
        cir(i,0,m) if(s&(1<<i)){
            const auto[u,v]=es[i];
            us[u]=us[v]=true;
        }
        ans+=ranges::min(us);
    }
    cout<<ans<<'\n';
    return 0;
}
