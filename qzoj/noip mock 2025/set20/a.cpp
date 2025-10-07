#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=1125899906842624ll;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string n;
    cir(i,0,10){
        char c;
        if(!(cin>>c)) break;
        n+=c;
    }
    if(n.size()>2){
        cout<<0<<'\n';
    }else{
        const auto wn=atoi(n.data());
        if(wn==1){
            cout<<2<<'\n';
        }else if(wn==2){
            cout<<6<<'\n';
        }else{
            const auto cx=wn*wn-2;
            const auto cy=(wn*wn+3)/4-2;
            const auto cz=(wn*wn+1)/2-2;
            const auto ck=(wn*wn+3)/4-2;
            auto ans=0ll;
            auto apw=[&](int x){
                auto res=1ll;
                cir(i,0,x) (res<<=1)%=MOD;
                return res;
            };
            (ans+=apw(cx)+apw(cy)+apw(cz)+apw(ck))%=MOD;
            cout<<ans<<'\n';
        }
    }
    return 0;
}
