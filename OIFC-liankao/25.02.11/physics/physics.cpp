#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("physics.in");
ofstream ouf("physics.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(auto a,auto b){
        if(a<b) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    string s;inf>>s;
    const auto n=(int)(s.size());
    math.init(n+7);
    const auto cntz=count(s.begin(),s.end(),'?');
    const auto cntn=count(s.begin(),s.end(),'+');
    auto ans=0ll;
    vector<lint> suf(n+7),sufx(n+7);
    cir(i,0,cntz+1) suf[i]=math.C(cntz,i);
    cir(i,0,cntz+1) sufx[i]=math.C(cntz-1,i);
    for(auto i=n+5;~i;--i) (suf[i]+=suf[i+1])%=MOD;
    for(auto i=n+5;~i;--i) (sufx[i]+=sufx[i+1])%=MOD;
    cir(i,0,n) if(s[i]=='-'){
        (ans+=suf[max<int>(i+1-cntn,0)])%=MOD;
    }else if(s[i]=='?'){
        (ans+=sufx[max<int>(i+1-cntn,0)])%=MOD;
    }
    ouf<<ans<<'\n';
    return 0;
}
