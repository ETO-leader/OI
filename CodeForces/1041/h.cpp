#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<pair<int,int>> es(m);
        for(auto&[u,v]:es) cin>>u>>v,--u,--v;
        mt19937 eng(251);
        auto ans=0;
        cir(i,0,(int)(5e5)){
            auto cnt=0;
            ranges::shuffle(es,eng);
            vector<int> deg(n);
            for(auto&[u,v]:es){
                if(deg[u]<2&&deg[v]<2) ++cnt,++deg[u],++deg[v];
            }
            ans=max(ans,cnt);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
