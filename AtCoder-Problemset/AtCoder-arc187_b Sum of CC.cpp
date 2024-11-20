#include<bits/stdc++.h>
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
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<int> premin(n,m+1),sufmax(n,0),precnt(n),sufcnt(n);
    [&]{
        auto pmn=m+1,pcnt=0;
        cir(i,0,n){
            if(a[i]>-1) pmn=min(pmn,a[i]);
            else ++pcnt;
            precnt[i]=pcnt;premin[i]=pmn;
        }
    }();
    [&]{
        auto smx=0,scnt=0;
        for(auto i=n-1;~i;--i){
            if(a[i]>-1) smx=max(smx,a[i]);
            else ++scnt;
            sufcnt[i]=scnt;sufmax[i]=smx;
        }
    }();
    auto ans=0ll;
    cir(i,1,n){
        auto cur=0ll;
        vector<lint> cost(m+1);
        cost[sufmax[i]]=math.qpow(sufmax[i],sufcnt[i]);
        cir(w,sufmax[i]+1,m+1){
            cost[w]=(math.qpow(w,sufcnt[i])+MOD-(w-1?math.qpow(w-1,sufcnt[i]):0))%MOD;
        }
        cir(w,sufmax[i],premin[i-1]){
            (ans+=math.qpow(m-w,precnt[i-1])*cost[w])%=MOD;
        }
    }
    cout<<(ans+math.qpow(m,sufcnt[0]))%MOD<<'\n';
    return 0;
}

