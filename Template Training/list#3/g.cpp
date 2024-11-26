#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
    constexpr auto inv(lint a){return qpow(a,MOD-2);}
    constexpr auto C(lint a,int b,vector<lint>&inva){
        if(a<b) return 0ll;
        auto cur=1ll;auto cp=0;
        cir(x,0,b){
            if(!((a-x)%MOD)) return 0ll;
            (cur*=((a-x)%MOD))%=MOD;
            (cur*=inva[x+1])%=MOD;
        }
        return cur;
    }
} math;
static constexpr auto maxm=(int)(2e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<lint> fct(maxm,1),ifct(maxm),inv(maxm);
    cir(i,1,maxm) fct[i]=(fct[i-1]*i)%MOD;
    ifct[maxm-1]=math.inv(fct[maxm-1]);
    for(auto i=maxm-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
    cir(i,1,maxm) inv[i]=ifct[i]*fct[i-1]%MOD;
    while(T--) [&]{
        lint n,m;int op;cin>>n>>m>>op;
        if(op) cout<<math.C(n,m,inv)<<'\n';
        else cout<<math.C(n+m-1,m,inv)<<'\n';
    }();
    return 0;
}
