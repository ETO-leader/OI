#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#if defined(ONLINE_JUDGE)
ifstream inf("clock.in");
ofstream ouf("clock.out");
#define cin inf
#define cout ouf
#endif
using lint=long long;
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;valarray<lf> d(60,n),l(n);
    cir(i,1,n) cin>>d[i];
    for(auto&i:l) cin>>i;
    lint a,b;cin>>a>>b;
    auto tl=abs(a-b);
    auto c=l;c/=d;
    cir(i,0,n-1) c[i+1]=min(c[i+1],c[i]*d[i]);
    vector<lf> ax;
    cir(i,0,n) ax.push_back(tl%(int)(d[i])),tl/=d[i];
    vector f(n+1,vector<lf>(2));
    for(auto i=n-1;~i;--i) cir(x,0,2){
        const auto wx=ax[i]+x;
        f[i][x]=min(f[i+1][0]+c[i]*wx,f[i+1][1]+c[i]*(d[i]-wx));
    }
    cout<<fixed<<setprecision(15)<<f[0][0]*numbers::pi*2<<'\n';
    return 0;
}
