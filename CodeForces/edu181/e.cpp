#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint n,x;cin>>n>>x;
        if(n==1) return cout<<x<<'\n',void();
        if(n*(n+1)/2>x+1) return cout<<0<<'\n',void();
        const auto mxw=x+1-n*(n+1)/2;
        vector f(n+1,vector<lint>(mxw+n));
        cir(i,1,n+1) cir(x,i,mxw+n){
            if(x==i){
                f[i][x]=1;
            }else{
                (f[i][x]=f[i-1][x-1]+f[i][x-i])%=MOD;
            }
        }
        auto ans=0ll;
        cir(c,0,mxw+1){
            (ans+=f[n-1][c+n-1]*(mxw-c+1))%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
