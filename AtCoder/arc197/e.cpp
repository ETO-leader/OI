#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){return qpow(a,MOD-2);}
} math;
class lagrange{
public:
    static auto solve(vector<lint> a,vector<lint> xi,lint x){
        auto ans=0ll;
        cir(i,0,(int)(a.size())){
            auto prod=a[i];
            cir(j,0,(int)(a.size())) if(i!=j) (prod*=(x-xi[j]+MOD)*math.inv(xi[i]-xi[j]+MOD)%MOD)%=MOD;
            (ans+=prod)%=MOD;
        }
        return ans;
    }
};
constexpr auto sumId1(lint x){
    return x*(x+1)/2%MOD;
}
constexpr auto sumId2(lint x){
    return lagrange::solve({1,5,14,30,55},{1,2,3,4,5},x);
}
constexpr auto sumId3(lint x){
    return lagrange::solve({1,9,36,100,225,441,784},{1,2,3,4,5,6,7},x);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint n,h,w;cin>>n>>h>>w;
        if(n*2>h||n*2>w) return cout<<0<<'\n',void();
        const auto P=(h-n*2+2)*(h-n*2+1)/2%MOD;
        const auto K=w-n*2+2;
        const auto A=(K*K%MOD*(w-n*2+1)%MOD+(K*K*2-K*2)%MOD*sumId1(w-n*2+1)+(1+MOD-K*4%MOD)%MOD*sumId2(w-n*2+1)+sumId3(w-n*2+1)*2)%MOD;
        const auto D=(w-n*2+2)*(w-n*2+1)/2%MOD;
        const auto C=h-n*2+2;
        const auto B=(C*C%MOD*(h-n*2+1)%MOD+(C*C*2-C*2)%MOD*sumId1(h-n*2+1)+(1+MOD-C*4%MOD)%MOD*sumId2(h-n*2+1)+sumId3(h-n*2+1)*2)%MOD;
        clog<<P<<' '<<D<<' '<<' '<<A<<' '<<B<<'\n';
        cout<<(P*A%MOD+D*B%MOD+MOD-A*B%MOD)%MOD<<'\n';
    }();
    return 0;
}
