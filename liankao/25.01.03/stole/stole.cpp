#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("stole.in");
ofstream fcout("stole.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=unsigned long long;
class mathbase{
private:
    const uint p;
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ull;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,p-2);}
    mathbase(uint _p):p(_p){}
};
class lagrange{
public:
    auto solve(vector<lint> a,vector<lint> xi,lint x,const int p){
        auto ans=0ull;
        mathbase math(p);
        cir(i,0,(int)(a.size())){
            auto prod=a[i];
            cir(j,0,(int)(a.size())) if(i!=j) (prod*=(x-xi[j]+p)*math.inv(xi[i]-xi[j]+p)%p)%=p;
            (ans+=prod)%=p;
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,r;uint p;fcin>>n>>r>>p;
    mathbase math(p);
    vector c(n+7,vector<lint>(n+7));
    c[0][0]=1;
    cir(i,1,n+7) cir(j,0,n+7){
        c[i][j]=c[i-1][j];
        if(j) (c[i][j]+=c[i-1][j-1])%=p;
    }
    const auto m=min(n*(n-1)/2,r)+7;
    vector f(n+1,vector<lint>(m+1));
    f[1][0]=1;
    vector g(n+1,vector<lint>(n+1));
    cir(w,1,m+1){
        for(auto&x:g) fill(x.begin(),x.end(),0);
        cir(i,1,n+1) g[i][1]=f[i][w-1]*i%p;
        cir(i,1,n+1) f[i][w]=f[i][w-1];
        cir(a,1,n+1) cir(b,1,n+1) if(a+b<n+1){
            const auto mul=math.qpow(r-w+2,a*b-1)*c[a+b-1][b-1]%p*f[b][w-1]%p*b%p;
            cir(x,1,n) (g[a+b][x+1]+=g[a][x]*mul)%=p;
        }
        cir(a,1,n+1) cir(x,2,n+1) (f[a][w]+=g[a][x]*math.qpow(a,x-2))%=p;
    }
    vector<lint> fx(m),pos(m);
    iota(pos.begin(),pos.end(),1);
    cir(i,0,m) fx[i]=f[n][i+1];
    fcout<<lagrange().solve(fx,pos,r,p)<<'\n';
    return 0;
}
