#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("frac.in");
ofstream ouf("frac.out");
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<double> a(n),b(n);
    for(auto&i:a) inf>>i;
    for(auto&i:b) inf>>i;
    cir(i,0,q){
        int l,r,x;inf>>l>>r>>x;--l;--r;
        auto ans=0.0;
        auto u=l;
        for(;u+4<r+1;u+=4) ans+=a[u]/(b[u]+x)+a[u+1]/(b[u+1]+x)+a[u+2]/(b[u+2]+x)+a[u+3]/(b[u+3]+x);
        for(;u<r+1;++u) ans+=a[u]/(b[u]+x);
        ouf<<fixed<<setprecision(9)<<ans<<'\n';
    }
    return 0;
}
