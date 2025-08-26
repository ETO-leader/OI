#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("frac.in");
ofstream ouf("frac.out");
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<uint64_t> a(n),b(n);
    for(auto&i:a) inf>>i;
    for(auto&i:b) inf>>i;
    cir(i,0,q){
        int l,r,x;inf>>l>>r>>x;--l;--r;
        auto ans=0.0;
        auto u=l;
        for(;u+3<r+1;u+=3){
            const auto w=(b[u]+x)*(b[u+1]+x)*(b[u+2]+x);
            ans+=((b[u]+x)*(b[u+1]+x)*a[u+2]+(b[u+1]+x)*(b[u+2]+x)*a[u]+(b[u]+x)*(b[u+2]+x)*a[u+1])/(1.0l*w);
            // ans+=a[u]/(b[u]+x)+a[u+1]/(b[u+1]+x)+a[u+2]/(b[u+2]+x)+a[u+3]/(b[u+3]+x);
        }
        for(;u<r+1;++u) ans+=a[u]/(b[u]+x);
        ouf<<fixed<<setprecision(9)<<ans<<'\n';
    }
    return 0;
}
