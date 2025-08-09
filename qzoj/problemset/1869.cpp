#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,s;cin>>n>>s;
    vector<lint> t(n),c(n);
    cir(i,0,n) cin>>t[i]>>c[i];
    auto sc=accumulate(c.begin(),c.end(),0ll),pre=0ll;
    vector<lint> f(n+1,(lint)(1e18l));
    f[0]=0;
    cir(i,0,n){
        if(i) sc-=c[i-1],pre+=t[i-1];
        const auto w=f[i]+s*sc;
        auto ts=pre,cs=0ll;
        cir(j,i+1,n+1){
            ts+=t[j-1];
            cs+=c[j-1];
            f[j]=min(f[j],w+ts*cs);
        }
    }
    cout<<f[n]<<'\n';
    return 0;
}
