#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class barrett{
private:
    uint64_t m,p;
public:
    auto init(int x){
        m=((__uint128_t)(1)<<64)/x;
        p=x;
    }
    auto mod(uint64_t x){
        return x-(((__uint128_t)(x)*m)>>64)*p;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    uint64_t a,b,x0,y0,x1,y1,n,m;
    cin>>a>>b>>x0>>y0>>x1>>y1>>n>>m;
    barrett mod;
    mod.init(m);
    auto ans=(uint64_t)(0);
    cir(i,2,n+1){
        const auto x2=mod.mod(a*x1+x0*y1);
        const auto y2=mod.mod(b*y1+y0*x1);
        ans+=x2;
        swap(x0,x1);
        swap(y0,y1);
        x1=x2;
        y1=y2;
    }
    cout<<ans%m<<'\n';
    return 0;
}
