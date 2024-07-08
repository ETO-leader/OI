#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    string s;cin>>s;
    const auto nw=0b110;
    vector<array<lint,8>> f(k+1);
    f[0][0]=1;
    cir(i,0,n){
        const auto g=f;
        const auto nx=s[i]=='1';
        for(auto&x:f) for(auto&p:x) p=0;
        cir(ki,0,k+1) cir(x,0,8) if(x!=nw){
            const auto nwx=((x<<1)&7)+nx;
            if(nwx!=nw) (f[ki][nwx]+=g[ki][x])%=MOD;
            const auto nwy=((x<<1)&7)+(!nx);
            if(nwy!=nw&&ki+1<k+1) (f[ki+1][nwy]+=g[ki][x])%=MOD;
        }
    }
    auto ans=0ll;
    for(auto&i:f) for(auto&x:i) (ans+=x)%=MOD;
    cout<<ans<<'\n';
    return 0;
}
