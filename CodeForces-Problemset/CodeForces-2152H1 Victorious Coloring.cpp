#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<vector<pair<int,lint>>> gr(n);
        cir(i,0,n-1){
            int u,v;lint w;cin>>u>>v>>w;--u;--v;
            gr[u].emplace_back(v,w);
            gr[v].emplace_back(u,w);
        }
        int q;cin>>q;
        cir(c,0,q){
            int t;cin>>t;
            auto ans=0ll;
            [&](this auto __self,int u,int f,lint fw)->lint {
                auto s=0ll;
                for(auto&[v,w]:gr[u]) if(v!=f){
                    s+=min(w,__self(v,u,w));
                }
                const auto ad=max<lint>(0,t-fw-s);
                ans+=ad;
                return ad+s;
            }(0,0,0);
            cout<<ans<<'\n';
        }
    }();
    return 0;
}
