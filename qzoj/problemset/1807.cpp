#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=(int)(1e8);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> us(n);
    cir(i,0,n){
        auto w=0;
        cir(j,0,m){
            int v;cin>>v;
            (w<<=1)|=v;
        }
        us[i]=w;
    }
    vector<int> f(1<<m);
    f[0]=1;
    for(auto&s:us){
        const auto lf=f;
        fill(f.begin(),f.end(),0);
        cir(ns,0,(1<<m)) if(lf[ns]) for(auto xs=s&(((1<<m)-1)^ns);~xs;xs=(xs?((xs-1)&(s&(((1<<m)-1)^ns))):xs-1)){
            if(!(xs&(xs<<1))) (f[xs]+=lf[ns])%=MOD;
        }
    }
    cout<<accumulate(f.begin(),f.end(),0ll)%MOD<<'\n';
    return 0;
}
