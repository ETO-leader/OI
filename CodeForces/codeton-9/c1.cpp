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
        cir(y,1,min(xlim,m)+1){
            const auto d=x^y;
            if(d) ans+=((!(x%d))||(!(y%d)));
        }
        println("{}",ans);
    }();
    return 0;
}
