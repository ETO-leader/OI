#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint x;cin>>x;
        const auto fx=x;
        auto pw=1ll;
        while(!(x&1)) (x>>=1),(pw<<=1);
        (pw<<=1);
        if((__int128_t)(pw)*(pw+1)/2<fx+1){
            cout<<pw<<'\n';
        }else if(x>1&&(__int128_t)(x)*(x+1)/2<fx+1){
            cout<<x<<'\n';
        }else{
            cout<<-1<<'\n';
        }
    }();
    return 0;
}
