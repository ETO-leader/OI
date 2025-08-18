#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,p;cin>>n>>p;--p;
    vector<int> d(n),w(n);
    cir(i,0,n) cin>>d[i]>>w[i];
    cir(i,1,n) w[i]+=w[i-1];
    vector<vector<array<int,2>>> f(n,vector<array<int,2>>(n,array<int,2>{_inf,_inf}));
    f[p][p][0]=f[p][p][1]=0;
    cir(len,1,n) cir(l,0,n-len+1){
        const auto r=l+len-1;
        const auto rw=w[n-1]-(w[r]-(l?w[l-1]:0));
        if(l) f[l-1][r][0]=min({f[l-1][r][0],f[l][r][0]+(d[l]-d[l-1])*rw,f[l][r][1]+(d[r]-d[l-1])*rw});
        if(r+1<n) f[l][r+1][1]=min({f[l][r+1][1],f[l][r][0]+(d[r+1]-d[l])*rw,f[l][r][1]+(d[r+1]-d[r])*rw});
    }
    cout<<min(f[0][n-1][0],f[0][n-1][1])<<'\n';
    return 0;
}
