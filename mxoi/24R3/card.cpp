#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("card.in");
ofstream fcout("card.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
class mathbase{
public:
    template<typename _Ty>
    constexpr auto qpow(_Ty a,_Ty b,const auto mod){
        auto res=_Ty(1);
        while(b){
            if(b&1) (res*=a)%=mod;
            (a*=a)%=mod;b>>=1;
        }
        return res;
    }
    constexpr auto phi(lint x){
        auto res=1ll;
        for(auto w=2ll;w*w<x+1;++w){
            auto pw=1ll,las=0ll;
            while(!(x%w)) las=pw,pw*=w,x/=w;
            res*=(pw-las);
        }
        if(x-1) res*=(x-1);
        return res;
    }
    auto factors(lint x){
        vector<lint> res;
        for(auto w=1ll;w*w<x+1;++w){
            if(!(x%w)){
                res.push_back(w);
                if(w*w<x) res.push_back(x/w);
            }
        }
        sort(res.begin(),res.end());
        return res;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;fcin>>T;
    while(T--) [&](){
        lint n;fcin>>n;
        const auto chk=math.factors(math.phi(n*2-1));
        auto ans=1ll;
        for(auto&i:chk){
            if(math.qpow<__int128_t>(2,i,n*2-1)==1){
                ans=i;break;
            }
        }
        fcout<<ans<<'\n';
    }();
    return 0;
}
