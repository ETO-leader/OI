#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        lint b,c,d;cin>>b>>c>>d;
        auto ans=0ll;
        cir(i,0,62) if(d&(1ll<<i)){
            if((!(b&(1ll<<i)))&&(c&(1ll<<i))) return println("-1");
            if(!(b&(1ll<<i))) ans|=(1ll<<i);
        }else{
            if(b&(1ll<<i)&&(!(c&(1ll<<i)))) return println("-1");
            if(b&(1ll<<i)) ans|=(1ll<<i);
        }
        println("{}",ans);
    }();
    return 0;
}
