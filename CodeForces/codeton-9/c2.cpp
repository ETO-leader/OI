#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint x,m;cin>>x>>m;
        auto ans=0ll;
        const auto xlim=1ll<<((int)(ceil(log2(x+1))));
        const auto maxf=m/x;
        const auto sumf=maxf/xlim;
        ans+=sumf*xlim;
        cir(px,0,xlim) ans+=(x*(sumf*xlim)+((x*px)^x)<m+1);
        cir(y,1,min(xlim,m)+1){
            const auto d=x^y;
            ans+=(((bool)(d%x))&&(!(d%y)));
        }
        println("{}",ans-1);
    }();
    return 0;
}
