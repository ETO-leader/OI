#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n,k;cin>>n>>k;
    auto ans=n+k-1;
    for(auto i=2ll,r=0ll;i<min(n,k)+1;i=r+1){
        r=min(n/(n/i),k);
        ans+=(n/i)*(r-i+1);
    }
    for(auto i=2ll,r=0ll;i<min(n-1,k)+1;i=r+1){
        r=min((n-1)/((n-1)/i),k);
        ans+=((n-1)/i)*(r-i+1);
    }
    cout<<ans%MOD<<'\n';
    return 0;
}
