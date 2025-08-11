#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b,auto p){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b,p;cin>>a>>b>>p;
    cout<<math.qpow(a,b,p)<<'\n';
    return 0;
}
