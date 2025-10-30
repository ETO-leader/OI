#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e8+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint a) const{
        return qpow(a,MOD-2);
    }
    auto init(auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        ifct[n-1]=inv(fct[n-1]);
        for(auto i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    }
    constexpr auto C(auto a,auto b) const{
        return a>b-1&&b>-1?fct[a]*ifct[b]%MOD*ifct[a-b]%MOD:0;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,x,y;cin>>n>>m>>x>>y;
        if((!x)&&(!y)) return cout<<1<<'\n',void();
        math.init(n+m+7);
        auto ans=0ll;
        cir(stp,1,n+m+7){
            // I. lef
            // lef: stp - 1, up: stp - 1, rig: stp - 1, down: stp - 2
            (ans+=math.C(x-1,stp-2)*math.C(m-y,stp-1)%MOD*math.C(n-x,stp-1)%MOD*math.C(y,stp-1))%=MOD;
            // II. up
            // lef: stp - 1, up: stp - 1, rig: stp - 1, down: stp - 1
            (ans+=math.C(x-1,stp-1)*math.C(m-y,stp-1)%MOD*math.C(n-x,stp-1)%MOD*math.C(y,stp-1))%=MOD;
            // III. rig
            // lef: stp, up: stp - 1, rig: stp - 1, down: stp - 1
            (ans+=math.C(x-1,stp-1)*math.C(m-y,stp)%MOD*math.C(n-x,stp-1)%MOD*math.C(y,stp-1))%=MOD;
            // IV. down
            // lef: stp, up: stp, rig: stp - 1, down: stp - 1
            (ans+=math.C(x-1,stp-1)*math.C(m-y,stp)%MOD*math.C(n-x,stp)%MOD*math.C(y,stp-1))%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}

