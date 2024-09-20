#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("b.in");
ofstream fcout("b.out");
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
    int n,m;fcin>>n>>m;vector<int> b(m);
    for(auto&i:b) fcin>>i,--i;
    auto cirsize=[&](auto __self,int p,vector<int>&vis)->int {
        if(vis[p]) return 0;
        vis[p]=true;
        return __self(__self,b[p],vis)+1;
    };
    map<int,lint> cntc;
    vector<int> idw;
    [&](){
        vector<int> vis(m);
        cir(i,0,m) if(!vis[i]){
            const auto siz=cirsize(cirsize,i,vis);
            cntc[siz]+=siz;
        }
        idw.resize(cntc.size());
        for(auto c=-1;auto&[a,b]:cntc) idw[++c]=a;
    }();
    const auto k=(int)(cntc.size());
    vector<lint> c(1<<k);
    cir(s,0,(1<<k)){
        auto vc=0ll;
        cir(i,0,k) if(s&(1<<i)) vc+=cntc[idw[i]];
        c[s]=math.qpow(vc,n);
    }
    auto ans=0ll;
    for(int s=(1<<k)-1;s;--s){
        for(auto ns=(s-1)&s;ns;ns=((ns-1)&s)){
            const auto bc=__builtin_popcount(s^ns);
            (c[s]+=c[ns]*(bc&1?MOD-1:1))%=MOD;
        }
        auto g=1ll;
        cir(i,0,k) if(s&(1<<i)) g=lcm(g,idw[i]);
        (ans+=c[s]*(g%MOD))%=MOD;
    }
    fcout<<ans*math.inv(math.qpow(m,n))%MOD<<'\n';
    return 0;
}
