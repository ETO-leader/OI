#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,r;cin>>n>>r;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<lint>> f(n+1,vector<lint>(n-1,-_infl));
    vector<vector<int>> fr(n+1,vector<int>(n-1));
    cir(i,0,n-1) f[0][i]=0;
    cir(i,1,n+1){
        // lw < w
        [&]{
            auto pmx=-_infl;
            auto fmx=-1;
            cir(w,0,n-1){
                const auto fw=pmx-a[(w+1-(i-1)*r%n+n)%n];
                const auto uw=f[i-1][w]+a[(w-(i-1)*r%n+n)%n];
                if(f[i][w]<fw){
                    f[i][w]=fw;
                    fr[i][w]=fmx;
                }
                if(uw>pmx){
                    pmx=uw;
                    fmx=w;
                }
            }
        }();
        // lw == w
        [&]{
            cir(w,0,n-1){
                const auto fw=f[i-1][w]+a[(w-(i-1)*r%n+n)%n]-a[(w+1-(i-1)*r%n+n)%n];
                if(f[i][w]<fw){
                    f[i][w]=fw;
                    fr[i][w]=w;
                }
            }
        }();
        // lw > w
        [&]{
            auto pmx=-_infl;
            auto fmx=-1;
            for(auto w=n-2;~w;--w){
                const auto fw=pmx+a[(w-(i-1)*r%n+n)%n];
                const auto uw=f[i-1][w]-a[(w+1-(i-1)*r%n+n)%n];
                if(f[i][w]<fw){
                    f[i][w]=fw;
                    fr[i][w]=fmx;
                }
                if(uw>pmx){
                    pmx=uw;
                    fmx=w;
                }
            }
        }();
    }
    auto p=max_element(f[n].begin(),f[n].end())-f[n].begin();
    cout<<f[n][p]<<'\n';
    vector<int> ans(n+1);
    for(auto i=n;i;--i){
        ans[i]=p+1;
        p=fr[i][p];
    }
    ans[0]=p+1;
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
