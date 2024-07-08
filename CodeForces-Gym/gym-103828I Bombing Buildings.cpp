#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(lint)(1e15+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int n;lint x,y;cin>>n>>x>>y;
        vector<int> h(n);
        for(auto&i:h) cin>>i;
        h.insert(h.begin(),0);++n;
        vector<vector<lint>> f(n,vector<lint>(n));
        cir(len,2,n+1) cir(l,0,n-len+1){
            const auto r=l+len-1;
            f[l][r]=_inf;
            if(h[r]<h[l]){
                f[l][r]=f[l][r-1];
            }else{
                cir(i,l+1,r) if(h[i]<h[r]+1){
                    f[l][r]=min(f[l][r],f[l][i-1]+f[i][r-1]+y);
                }
                f[l][r]=min(f[l][r],f[l][r-1]+x);
            }
        }
        cout<<f[0][n-1]<<'\n';
    }();
    return 0;
}
