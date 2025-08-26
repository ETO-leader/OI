#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<lint>> w(2,vector<lint>(n));
    auto sum=0ll;
    cir(i,0,2){
        cir(x,0,n){
            lint a,b;cin>>a>>b;
            sum+=b;
            w[i][x]=a-b;
        }
    }
    vector<vector<lint>> f(m+1,vector<lint>(5,_infl));
    auto g=f;
    f[0][0]=0;
    cir(p,0,n){
        swap(f,g);
        for(auto&x:f) fill(x.begin(),x.end(),_infl);
        cir(i,0,m+1){
            cir(ls,0,5) cir(ns,0,4){
                const auto adc=__builtin_popcount(ns&(ls^3));
                if(i+adc>m) continue;
                f[i+adc][ns]=min(f[i+adc][ns],g[i][ls]+(ns&1?w[0][p]:0)+(ns&2?w[1][p]:0));
            }
            cir(ls,0,4){
                if(i+1>m) continue;
                f[i+1][4]=min(f[i+1][4],g[i][ls]+w[0][p]+w[1][p]);
            }
            f[i][4]=min(f[i][4],g[i][4]+w[0][p]+w[1][p]);
        }
    }
    auto ans=_infl;
    for(auto&x:f) for(auto&i:x) ans=min(ans,i+sum);
    cout<<ans<<'\n';
    return 0;
}
