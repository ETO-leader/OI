#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint l,r;cin>>l>>r;
        vector pl{2,3,5,7};
        auto ans=0ll;
        cir(s,0u,(1u<<4)){
            auto w=1ll;
            cir(i,0,4) if((s>>i)&1) w*=pl[i];
            ans+=((r/w)-((l-1)/w))*((popcount(s)&1)?-1:1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
