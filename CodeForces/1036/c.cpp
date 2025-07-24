#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto ans=1ll;
        cir(i,0,n-1) if(a[i+1]%a[i]) ans=lcm(ans,a[i]/gcd(a[i],a[i+1]));
        cout<<ans<<'\n';
    }();
    return 0;
}
