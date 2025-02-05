#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("square.in");
ofstream ouf("square.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=19260817;
static constexpr auto maxn=(int)(1e7+7);
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
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;inf>>T;
    vector<int> mu(maxn);
    vector<lint> p;
    bitset<maxn> isnp;
    cir(i,2,maxn+1) if(!isnp[i]){
        p.push_back(i);
        for(auto j=1ll*i*i;j<maxn;j+=i) isnp[j]=true;
    }
    vector<lint> fct(maxn,1);
    cir(i,2,maxn) fct[i]=fct[i-1]*i%MOD;
    vector<lint> pprod(maxn,1);
    for(auto&i:p){
        auto cur=i;
        while(cur<maxn){
            auto prod=math.inv(i);
            for(auto x=cur;x<maxn;x+=cur) (prod*=i*i%MOD)%=MOD,(pprod[x]*=prod)%=MOD;
            cur*=i;
        }
    }
    cir(i,1,maxn) (pprod[i]*=pprod[i-1])%=MOD;
    while(T--) [&](){
        int n;inf>>n;
        ouf<<math.qpow(fct[n],n*2)%MOD*math.inv(pprod[n]*pprod[n]%MOD)%MOD<<'\n';
    }();
    return 0;
}
