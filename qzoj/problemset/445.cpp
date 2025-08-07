#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint n,k;cin>>n>>k;
    auto ans=n*k;
    n=min(n,k);
    for(auto x=1ll,r=0ll;x<n+1;x=r+1){
        r=min(n,k/(k/x));
        ans-=(k/x)*((r+x)*(r-x+1)/2);
    }
    cout<<ans<<'\n';
    return 0;
}
