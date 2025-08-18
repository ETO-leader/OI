#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<vector<int>>> f(n,vector<vector<int>>(n,vector<int>(n,-_inf)));
    cir(i,0,n) cir(c,0,n) f[i][i][c]=(c+1)*(c+1);
    cir(len,2,n+1) cir(l,0,n-len+1) cir(x,0,n-len+1){
        const auto r=l+len-1;
        cir(p,l,r) if(a[p]==a[r]) f[l][r][x]=max(f[l][r][x],f[l][p][x+1]+(p+1<r?f[p+1][r-1][0]:0));
        f[l][r][x]=max(f[l][r][x],f[l][r-1][0]+f[r][r][x]);
    }
    cout<<f[0][n-1][0]<<'\n';
    return 0;
}
