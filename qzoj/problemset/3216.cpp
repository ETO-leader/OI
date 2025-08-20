#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e12l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    cir(tc,0,T) [tc]{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        cir(i,1,n) a[i]+=a[i-1];
        vector<vector<array<lint,2>>> f(n,vector<array<lint,2>>(n,array<lint,2>{_infl,_infl}));
        cir(i,0,n) f[i][i][0]=f[i][i][1]=0;
        cir(len,2,n+1) cir(l,0,n-len+1){
            const auto r=l+len-1;
            cir(p,l,r){
                f[l][r][0]=min({f[l][r][0],f[l][p][1]+f[p+1][r][0]+(r-p)*(a[p]-(l?a[l-1]:0)),f[l][p][0]+f[p+1][r][0]+(p-l+1)*(a[r]-a[p])});
                f[l][r][1]=min(f[l][r][1],f[l][p][1]+f[p+1][r][1]+(r-p)*(a[p]-(l?a[l-1]:0)));
            }
        }
        cout<<"Case #"<<tc+1<<": "<<f[0][n-1][0]<<'\n';
    }();
    return 0;
}
