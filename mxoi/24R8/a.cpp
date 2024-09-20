#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("a.in");
ofstream fcout("a.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=(lint)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
    constexpr auto pref(lint x){
        return (x/2*3+(x&1)*2)%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint l,r;fcin>>l>>r;
    fcout<<((math.qpow(2,r+1)-math.qpow(2,l)-math.pref(r)+math.pref(l-1)+MOD*5)%MOD*math.inv(3))%MOD<<'\n';
    return 0;
}
