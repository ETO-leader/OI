#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;lint s;cin>>n>>s;
        vector<lint> a(n);
        for(auto&x:a) cin>>x;
        vector f(n,array<lint,2>());
        auto mn=[&](auto w){return w>s*2-1?s:max(w-s,0ll);};
        auto mx=[&](auto w){return w-mn(w);};
        f[1][0]=mn(a[1])*a[0];
        f[1][1]=mx(a[1])*a[0];
        cir(i,2,n-1){
            f[i][0]=min({
                f[i-1][0]+mx(a[i-1])*mn(a[i]),
                f[i-1][1]+mn(a[i-1])*mn(a[i]),
            });
            f[i][1]=min({
                f[i-1][0]+mx(a[i-1])*mx(a[i]),
                f[i-1][1]+mn(a[i-1])*mx(a[i]),
            });
        }
        auto ans=min(f[n-2][0]+mx(a[n-2])*a[n-1],f[n-2][1]+mn(a[n-2])*a[n-1]);
        cout<<ans<<'\n';
    }();
    return 0;
}
