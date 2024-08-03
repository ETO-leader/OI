#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
static constexpr auto _inflf=1e18l;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector f(n+1,vector<lf>(m+1,_inflf));
    // $ans=n+2\cdot\sum\limits_{i=1}^n\frac{\sum\limits_{j=1}^{i-1}a_j}{a_i}$
    f[0][0]=0;
    auto premx=0;
    cir(i,0,n){
        // $a_{i+1}\le\lceil\frac {m}{n-i}\rceil$
        const auto lim=(m+i)/(n-i);
        cir(j,0,premx+1) cir(w,1,lim+1) if(j+w<m+1){
            f[i+1][j+w]=min(f[i+1][j+w],f[i][j]+1.0l*j/w);
        }
        premx+=lim;
    }
    cout<<fixed<<setprecision(15)<<n+*ranges::min_element(f[n])*2<<'\n';
    return 0;
}
