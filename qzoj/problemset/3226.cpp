#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
private:
    const int p;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,p-2);
    }
    mathbase(auto _p):p(_p){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,p;cin>>n>>p;
    mathbase math(p);
    map<pair<int,int>,lint> bin;
    auto C=[&](int a,int b){
        if(bin.count({a,b})) return bin[{a,b}];
        auto res=1ll;
        auto cntp=0;
        cir(i,0,b){
            auto w=a-i;
            while(!(w%p)) ++cntp,w/=p;
            (res*=w)%=p;
        }
        auto nres=1ll;
        cir(i,1,b+1){
            auto w=i;
            while(!(w%p)) --cntp,w/=p;
            (nres*=w)%=p;
        }
        if(cntp) return bin[{a,b}]=0;
        return bin[{a,b}]=res*math.inv(nres)%p;
    };
    auto dfs=[&](auto __self,int u){
        if(u>n) return make_pair(1ll,0ll);
        const auto[lw,lc]=__self(__self,u*2);
        const auto[rw,rc]=__self(__self,u*2+1);
        return make_pair(lw*rw%p*C(lc+rc,lc)%p,lc+rc+1);
    };
    cout<<dfs(dfs,1).first<<'\n';
    return 0;
}
