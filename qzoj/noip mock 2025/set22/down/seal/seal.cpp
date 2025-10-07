#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("seal.in");
ofstream ouf("seal.out");
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<int> a(n);
    for(auto&x:a) inf>>x,--x;
    vector<vector<int>> f(n,vector<int>(n,_inf));
    cir(i,0,n) f[i][i]=0;
    cir(i,0,n-1) f[i+1][i]=0;
    cir(len,2,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        if(a[l]==a[r]) f[l][r]=min(f[l][r],f[l+1][r-1]+r-l-1);
        cir(p,r+1,n) if(a[r]==a[p]) f[l][p]=min(f[l][p],f[l][r]+f[r][p]);
        cir(p,0,l) if(a[p]==a[l]) f[p][r]=min(f[p][r],f[p][l]+f[l][r]);
    }
    auto p=0,ans=0;
    while(p<n){
        for(auto x=n-1;~x;--x){
            if(f[p][x]<_inf){
                ans+=f[p][x];
                p=x+1;
                break;
            }
        }
    }
    ouf<<ans<<'\n';
    return 0;
}
