#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> x(n),y(n);
    cir(i,0,n) cin>>x[i]>>y[i];
    vector<vector<int>> f(n,vector<int>(n,_inf));
    cir(i,0,n) f[i][i]=0;
    cir(len,1,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        cir(p,l,r) if(y[p]==x[p+1]) f[l][r]=min(f[l][r],f[l][p]+f[p+1][r]+x[l]*y[p]*y[r]);
    }
    cout<<f[0][n-1]<<'\n';
    return 0;
}
