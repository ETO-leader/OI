#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,l,r;cin>>n>>l>>r;
    vector<lint> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    for(auto i=n-2;~i;--i) a[i]+=a[i+1];
    for(auto i=n-2;~i;--i) b[i]+=b[i+1];
    a.emplace_back(0);
    b.emplace_back(0);
    auto check=[&](int w){
        vector f(n+1,vector<lint>(n+1));
        if(b[0]-a[0]<w+1) f[0][0]=1;
        cir(i,0,n+1) cir(j,0,n+1) if(f[i][j]){
            if(i+1<n+1&&b[j]-a[i+1]<w+1) (f[i+1][j]+=f[i][j])%=MOD;
            if(j+1<n+1&&j<i&&b[j+1]-a[i]<w+1) (f[i][j+1]+=f[i][j])%=MOD;
        }
        return f[n][n];
    };
    cout<<(check(r)-check(l-1)+MOD)%MOD<<'\n';
    return 0;
}
