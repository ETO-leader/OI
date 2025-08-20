#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<int>> f(n,vector<int>(n));
    auto value=[&](int l,int r){
        return (l==r)?a[l]:abs(a[r]-a[l])*(r-l+1);
    };
    auto ans=0;
    for(auto len=n;len;--len) cir(l,0,n-len+1){
        const auto r=l+len-1;
        ans=max(ans,f[l][r]+value(l,r));
        cir(p,l,r) f[p+1][r]=max(f[p+1][r],f[l][r]+value(l,p));
        cir(p,l+1,r+1) f[l][p-1]=max(f[l][p-1],f[l][r]+value(p,r));
    }
    cout<<ans<<'\n';
    return 0;
}
