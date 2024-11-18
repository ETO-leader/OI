#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("rng.in");
ofstream fcout("rng.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using ulint=unsigned long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<ulint> fct,ifct;
public:
    constexpr auto qpow(ulint a,ulint b){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(ulint x){
        return qpow(x,MOD-2);
    }
    auto fact(const int x){
        while((int)(fct.size())<x+1){
            fct.push_back(fct.back()*fct.size()%MOD);
            ifct.push_back(inv(fct.back()));
        }
        return fct[x];
    }
    auto ifact(const int x){
        return fact(x),ifct[x];
    }
    auto initc(const int n){
        vector<vector<ulint>> C(n,vector<ulint>(n));
        C[0][0]=1;
        cir(i,1,n) cir(j,0,n){
            C[i][j]=C[i-1][j];
            if(j) (C[i][j]+=C[i-1][j-1])%=MOD;
        }
        return C;
    }
    auto C(int a,int b){
        return fact(a)*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    mathbase():fct(1,1),ifct(1,1){}
} math;
class polybase{
private:
    __gnu_pbds::gp_hash_table<int,vector<ulint>> rvx;
    auto change(vector<ulint>&a,int n){
        const auto&rev=rvx[n];
        cir(i,0,n) if(rev[i]>i) swap(a[i],a[rev[i]]);
    }
    vector<vector<ulint>> pwx;
    auto init(){
        pwx.resize(15);
        cir(i,0,15){
            const auto midh=(1<<i);
            const auto wx=math.qpow(omega,(MOD-1)/midh/2);
            pwx[i].resize(midh,1);
            cir(p,1,midh) pwx[i][p]=(pwx[i][p-1]*wx)%MOD;
            rvx[1<<i].resize(1<<i);
            cir(p,0,(1<<i)) rvx[1<<i][p]=(rvx[1<<i][p>>1]>>1)|((1<<(i-1))*(p&1));
        }
    }
    template<const int type>
    auto ntt(vector<ulint>&a,const int n){
        change(a,n);
        for(auto h=2,cnt=0;h<n+1;h<<=1,++cnt){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            // vector<int> pw(midh,1);
            // cir(i,1,midh) pw[i]=(pw[i-1]*wx)%MOD;
            // auto u=1ll;
            const auto&pw=pwx[cnt];
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*pw[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=(a[k+midh]>MOD-1?MOD:0);
                    a[k]+=wk;
                    a[k]-=(a[k]>MOD-1?MOD:0);
                    // (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto iv=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=iv)%=MOD;
        }
    }
    auto fit(vector<ulint>&a){
        while((!a.empty())&&(!a.back())) a.pop_back();
    }
public:
    auto mul(vector<ulint> a,vector<ulint> b){
        const auto n=(1<<((int)(log2(a.size()+b.size()))+1));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);fit(a);
        return a;
    }
    polybase(){init();}
} poly;
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,k;fcin>>n>>k;
    if(n==2){
        auto ans=0ull;
        cir(ax,0,k+1) (ans+=math.C(k,ax)*max(ax,k-ax))%=MOD;
        fcout<<ans<<'\n';
        exit(0);
    }
    vector<ulint> a;
    cir(i,0,(k+n-1)/n) a.push_back(math.ifact(i));
    auto ans=0ll,las=0ll;
    cir(i,(k+n-1)/n,k+1){
        a.push_back(math.ifact(i));
        auto ax=a,bx=a;
        // cir(c,0,n-1){
        //     ax=poly.mul(ax,a);
        //     if((int)(ax.size())>k+1) ax.resize(k+1);
        // }
        for(auto c=0;(1<<c)<n;++c){
            if((n-1)&(1<<c)) bx=poly.mul(bx,ax);
            if((1<<(c+1))<n) ax=poly.mul(ax,ax);
            if(ax.size()>k) ax.resize(k+1);
            if(bx.size()>k) bx.resize(k+1);
        }
        bx.resize(k+1);
        const auto lasx=las;
        las=bx[k]*math.fact(k)%MOD;
        (ans+=(las+MOD-lasx)*i)%=MOD;
    }
    fcout<<ans<<'\n';
    return 0;
}
