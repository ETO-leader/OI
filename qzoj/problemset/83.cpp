#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _infl=(int64_t)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int64_t> a(n);
    for(auto&i:a) cin>>i;
    vector<char> sgn(n);
    for(auto&i:sgn) cin>>i;
    auto extend=[&](auto&x){
        auto c=x;
        for(auto&i:c) x.emplace_back(i);
    };
    extend(a);
    extend(sgn);
    vector<vector<int64_t>> f(n*2,vector<int64_t>(n*2,-_infl)),g(n*2,vector<int64_t>(n*2,_infl));
    cir(i,0,n*2) f[i][i]=g[i][i]=a[i];
    cir(len,2,n+1) cir(l,0,n*2-len+1){
        const auto r=l+len-1;
        cir(p,l,r){
            const auto csgn=sgn[p];
            if(csgn=='+'){
                f[l][r]=max(f[l][r],f[l][p]+f[p+1][r]);
                g[l][r]=min(g[l][r],g[l][p]+g[p+1][r]);
            }else{
                f[l][r]=max({
                    f[l][r],
                    f[l][p]*f[p+1][r],
                    f[l][p]*g[p+1][r],
                    g[l][p]*f[p+1][r],
                    g[l][p]*g[p+1][r]
                });
                g[l][r]=min({
                    g[l][r],
                    f[l][p]*f[p+1][r],
                    f[l][p]*g[p+1][r],
                    g[l][p]*f[p+1][r],
                    g[l][p]*g[p+1][r]
                });
            }
        }
    }
    auto ans=-_infl;
    cir(i,0,n) ans=max(ans,f[i][i+n-1]);
    cout<<ans<<'\n';
    return 0;
}
