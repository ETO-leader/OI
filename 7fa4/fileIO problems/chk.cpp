#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("square.in");
ofstream fcout("square.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=19260817;
static constexpr auto maxn=(int)(1e6+7);
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
    int T;fcin>>T;
    vector<int> mu(maxn);
    vector<lint> p;
    bitset<maxn> isnp;
    cir(i,2,maxn+1) if(!isnp[i]){
        p.push_back(i);
        for(auto j=1ll*i*i;j<maxn;j+=i) isnp[j]=true;
    }
    vector<lint> fct(maxn+1,1);
    cir(i,2,maxn) fct[i]=fct[i-1]*i%MOD;
    while(T--) [&](){
        int n;fcin>>n;
        auto res=1ll;
        for(auto&i:p){
            if(i>n) break;
            auto prod=i;
            while(prod<n+1) (res*=math.qpow(i,1ll*(n/prod)*(n/prod)))%=MOD,prod*=i;
        }
        fcout<<math.qpow(fct[n],n*2)%MOD*math.inv(res*res%MOD)%MOD<<'\n';
    }();
    return 0;
}
