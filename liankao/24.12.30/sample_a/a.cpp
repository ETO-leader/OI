#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("a.in");
ofstream ouf("a.out");
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
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<lint> a(n+1);
    for(auto&i:a) inf>>i;
    vector<lint> b(m+1);
    cir(i,1,m+1) inf>>b[i];
    vector f(m+1,vector<lint>(n+1));
    cir(i,0,n+1) f[0][i]=((i?f[0][i-1]:0)+a[i])%MOD;
    cir(i,1,m+1) cir(w,i,n+1){
        f[i][w]=(math.qpow(f[i-1][w],b[i])+MOD-math.qpow(f[i-1][i-1],b[i]))%MOD;
    }
    vector g(m+1,vector<lint>(n+1));
    g[m][n]=1;
    for(auto i=m;i;--i) for(auto w=n;w>i-1;--w){
        (g[i-1][w]+=g[i][w]*b[i]%MOD*math.qpow(f[i-1][w],b[i]-1))%=MOD;
        (g[i-1][i-1]+=(MOD-1)*g[i][w]%MOD*b[i]%MOD*math.qpow(f[i-1][i-1],b[i]-1))%=MOD;
    }
    const auto ansp=accumulate(a.begin(),a.end(),0ll)%MOD;
    const auto prod=[&]{auto res=1ll;cir(i,1,m+1) (res*=b[i])%=(MOD-1);return res;}();
    cir(i,0,n+1) ouf<<a[i]*[&]{
        auto res=0ll;
        cir(w,i,n+1) (res+=g[0][w])%=MOD;
        return res;
    }()%MOD*math.inv(math.qpow(ansp,prod))%MOD<<'\n';
    return 0;
}
