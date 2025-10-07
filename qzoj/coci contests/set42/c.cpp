#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> a(m);
    for(auto&i:a) cin>>i;
    vector<lint> pw(m+7,1ll);
    cir(i,1,m+7) pw[i]=pw[i-1]*n%MOD;
    vector<int> fail(m,-1);
    cir(i,1,m){
        auto vx=fail[i-1];
        while(vx>-1&&(a[vx+1]!=a[i])) vx=fail[vx];
        fail[i]=(a[vx+1]==a[i]?vx+1:-1);
    }
    vector<lint> f(m);
    f[0]=n;
    cir(i,1,m){
        f[i]=((fail[i]>-1?f[fail[i]]:0)+pw[i+1])%MOD;
    }
    for(auto&x:f) cout<<x<<'\n';
    return 0;
}
