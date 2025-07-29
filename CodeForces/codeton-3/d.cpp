#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ans=1ll;
        cir(i,1,n){
            if(a[i-1]%a[i]) return cout<<0<<'\n',void();
            auto w=a[i-1]/a[i];
            vector<int> fctr;
            for(auto x=2;x*x<w+1;++x) if(!(w%x)){
                fctr.emplace_back(x);
                while(!(w%x)) w/=x;
            }
            const auto v=m/a[i];
            if(w>1) fctr.emplace_back(w);
            auto vu=0;
            cir(s,0,(1<<(int)(fctr.size()))){
                auto x=1;
                cir(i,0,(int)(fctr.size())) if((s>>i)&1) x*=fctr[i];
                vu+=((popcount((unsigned)(s))&1)?-1:1)*(v/x);
            }
            (ans*=vu)%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
