#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    vector<int> uf(n);
    cir(i,1,n) cin>>uf[i],--uf[i];
    for(auto i=n-1;i;--i) a[uf[i]]+=a[i];
    vector<lint> f(n+1),g(n+1);
    cir(i,0,n){
        const auto g=gcd(a[i],a[0]);
        if(a[0]/g<n+1) ++f[a[0]/g];
    }
    for(auto x=n;x;--x) for(auto v=x*2;v<n+1;v+=x) f[v]+=f[x];
    for(auto x=n;x;--x) if(f[x]==x){
        g[x]=1;
        for(auto v=x*2;v<n+1;v+=x) (g[x]+=g[v])%=MOD;
    }
    println("{}",g[1]);
    return 0;
}
