#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("math.in");
ofstream fcout("math.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=unsigned long long;
class mathbase{
public:
    auto qpow(lint a,auto b,const int p){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
} math;
auto primes(const auto m){
    vector<int> pr;
    auto isprime=[&](auto x){
        for(auto i=2ll;i*i<x+1;++i) if(!(x%i)) return false;
        return true;
    };
    cir(i,2,m+1) if(isprime(i)) pr.push_back(i);
    return pr;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int T;lint m,p;fcin>>T>>m>>p;
    const auto pr=primes(m);
    vector<int> smp;
    const auto sqr=(int)(ceil(sqrtl(m)));
    for(auto&i:pr) if(i<sqr+1) smp.push_back(i);
    const auto k=(int)(smp.size());
    static constexpr auto kx=171;
    vector f(1<<k,vector<lint>(kx));
    vector<unsigned> st(m+1);
    vector<bool> normal(m+1);
    cir(i,1,m+1){
        auto w=i;
        for(auto c=-1;auto&x:smp){
            ++c;
            while(!(w%x)) w/=x,st[i]|=(1<<c);
        }
        if(w==1) normal[i]=true;
    }
    f[0][0]=1;
    cir(i,2,m+1){
        const auto g=f;
        if(normal[i]){
            cir(s,0,(1<<k)) if(!(s&st[i])) cir(x,0,kx-1){
                (f[s|st[i]][x+1]+=g[s][x]*(m/i))%=p;
            }
        }else if(!st[i]){
            for(auto w=i;w<m+1;w+=i){
                cir(s,0,(1<<k)) if(!(s&st[w])) cir(x,0,kx-1){
                    (f[s|st[w]][x+1]+=g[s][x]*(m/w))%=p;
                }
            }
        }
    }
    vector<lint> g(kx);
    cir(s,0,(1<<k)) cir(i,0,kx) (g[i]+=f[s][i])%=p;
    vector<lint> pw(kx+7);
    cir(i,0,kx+1) pw[i]=math.qpow(m,i,p);
    cir(i,0,T){
        lint n;fcin>>n;
        const auto q=min<lint>(n,kx-1);
        const auto prodx=math.qpow(m,n-q,p);
        auto cur=1ull,ans=0ull;
        cir(x,0,q+1){
            (ans+=cur*g[x]%p*pw[q-x]%p*prodx)%=p;
            (cur*=(n%p-x))%=p;
        }
        fcout<<ans<<'\n';
    }
    return 0;
}
