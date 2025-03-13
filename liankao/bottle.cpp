#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("bottle.in");
ofstream ouf("bottle.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
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
    constexpr auto inv(auto w){return qpow(w,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;vector<int> a(n);
    for(auto&i:a) inf>>i;
    for(auto&x:a) x=min(x,a[0]);
    vector<vector<lint>> f(n,vector<lint>(a[0]+1));
    f[0][a[0]]=1;
    vector<lint> ans(n);
    const auto invx=math.inv(n-1);
    vector<lint> suf(a[0]+1,invx);
    vector<lint> sum(a[0]+1);
    sum[a[0]]=invx;
    cir(i,1,n){
        f[i][a[i]]=suf[a[i]];
        cir(w,0,a[i]) f[i][w]=sum[w];
        auto fx=f[i];
        cir(w,0,a[0]+1) (sum[w]+=fx[w]*invx)%=MOD;
        for(auto w=a[0]-1;~w;--w) (fx[w]+=fx[w+1])%=MOD;
        cir(w,0,a[0]+1) (suf[w]+=fx[w]*invx)%=MOD;
    }
    cir(w,0,a[0]+1){
        auto sum=0ll;
        cir(v,0,n) (sum+=(w-min(w,a[v]))*invx)%=MOD;
        cir(i,0,n) (ans[i]+=(sum+MOD-((w-min(w,a[i]))*invx)%MOD)*f[i][w])%=MOD;
    }
    vector<lint> sufx(a[0]+1);
    for(auto i=n-1;~i;--i){
        for(auto w=a[0];~w;--w) (ans[i]+=min(w,a[i])*invx%MOD*sufx[w])%=MOD;
        cir(w,0,a[0]+1) (sufx[w]+=f[i][w])%=MOD;
    }
    for(auto&i:ans) ouf<<i<<'\n';
    return 0;
}
