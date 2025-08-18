#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,a,b;cin>>n>>a>>b;
    vector<int> w(n);
    for(auto&i:w) cin>>i;
    vector<vector<vector<vector<int>>>> f(n,vector<vector<vector<int>>>(n,vector<vector<int>>(n,vector<int>(n,_inf))));
    vector<vector<int>> g(n,vector<int>(n,_inf));
    cir(i,0,n) f[i][i][i][i]=0,g[i][i]=a;
    cir(len,2,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        cir(x,l,r+1) cir(y,l,r+1) cir(p,l+1,r+1) f[l][r][x][y]=min(f[l][r][x][y],f[l][p-1][x][y]+g[p][r]);
        if(r) cir(x,l,r) cir(y,l,r){
            const auto nx=(w[x]<w[r]?r:x);
            const auto ny=(w[y]>w[r]?r:y);
            f[l][r][nx][ny]=min(f[l][r][nx][ny],f[l][r-1][x][y]);
        }
        if(r) f[l][r][r][r]=min(f[l][r][r][r],g[l][r-1]);
        cir(x,l,r+1) cir(y,l,r+1) g[l][r]=min(g[l][r],f[l][r][x][y]+(w[y]-w[x])*(w[y]-w[x])*b+a);
    }
    cout<<g[0][n-1]<<'\n';
    return 0;
}
