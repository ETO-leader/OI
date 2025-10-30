#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<pair<lint,lint>> c;
        for(auto x=2;x*x<n+1;++x) if(!(n%x)){
            c.emplace_back(x,0);
            while(!(n%x)) n/=x,++c.back().second;
        }
        if(n>1) c.emplace_back(n,1);
        ranges::sort(c,[&](auto&u,auto&v){
            return u.second>v.second;
        });
        auto pw=1ll;
        auto ans=0ll,las=-1ll;
        for(auto&[a,b]:c){
            if(las>0) ans+=pw*(las-b);
            las=b;
            pw*=a;
        }
        if(las>0) ans+=pw*las;
        cout<<ans<<'\n';
    }();
    return 0;
}
