#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
private:
    auto initpr(int n){
        vector<int> vis(n),res;
        cir(i,2,n) if(!vis[i]){
            res.emplace_back(i);
            for(auto x=i*2;x<n;x+=i) vis[x]=true;
        }
        return res;
    }
public:
    auto check(lint l,lint r){
        const auto px=initpr(sqrtl(r)+7);
        vector<lint> phi(r-l,1),val(r-l);
        ranges::iota(val,l);
        for(auto&p:px){
            const auto s=(l+p-1)/p*p;
            for(auto i=s;i<r;i+=p){
                auto cnt=0;
                while(!(val[i-l]%p)) val[i-l]/=p,++cnt;
                phi[i-l]*=(p-1);
                cir(c,0,cnt-1) phi[i-l]*=p;
            }
        }
        cir(i,0,r-l) if(val[i]>1) phi[i]*=(val[i]-1);
        auto ans=0u;
        cir(i,l,r) ans+=i%phi[i-l];
        return ans; 
    }
} math;
template<typename _Ty>
auto toInteger(char*x){
    stringstream qwq(x);
    _Ty res;qwq>>res;
    return res;
}
int main(int argc,char*argv[]){
    const auto L=toInteger<lint>(argv[1]),R=toInteger<lint>(argv[2]);
    cout<<math.check(L,R)<<',';
}
