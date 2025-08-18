#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _infl=(int64_t)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int64_t> a(n);
    for(auto&i:a) cin>>i;
    cir(i,1,n) a[i]+=a[i-1];
    vector<vector<int64_t>> f(n,vector<int64_t>(n,_infl));
    vector<vector<int>> opt(n,vector<int>(n));
    cir(i,0,n) f[i][i]=0,opt[i][i]=i;
    cir(len,2,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        cir(p,opt[l][r-1],min(r,opt[l+1][r]+1)){
            const auto uw=f[l][p]+f[p+1][r]+a[r]-(l?a[l-1]:0);
            if(f[l][r]>uw) f[l][r]=uw,opt[l][r]=p;
        }
    }
    cout<<f[0][n-1]<<'\n';
    auto prt=[&](auto __self,int l,int r){
        if(l==r) return;
        __self(__self,l,opt[l][r]);
        __self(__self,opt[l][r]+1,r);
        cout<<l+1<<' '<<r+1<<'\n';
    };
    prt(prt,0,n-1);
    return 0;
}
