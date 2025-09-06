#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k;cin>>n>>k;
        auto ans=1ll;
        cir(i,0,k) (ans*=(i+1))%=MOD;
        if(n!=k) (ans*=(k+1))%=MOD;
        cout<<ans+(k*2==n)<<'\n';
    }();
    return 0;
}
