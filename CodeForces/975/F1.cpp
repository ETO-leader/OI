#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b,const int p){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x,const int p){return qpow(x,p-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,p;cin>>n>>p;
        vector f(n,vector(n,vector<lint>(2)));
        auto check=[&](){
            cir(len,1,n+1) cir(l,0,n-len+1){
                const auto r=l+len-1;
                // Not forced to right
                // 1. Forced to right next step
                if(l) (f[l-1][r][1]+=f[l][r][0]*(n-(r-l+1)))%=p;
                // 2. Not Forced to right next step
                if(l) (f[l-1][r][0]+=f[l][r][0]*(n-(r-l+1)))%=p;
                // Forced to right
                // 1. Forced to right next step
                if(r<n-1) (f[l][r+1][1]+=f[l][r][1]*(n-(r-l+1)))%=p;
                // 2. Not forced to right next step
                if(r<n-1) (f[l][r+1][0]+=f[l][r][1])%=p;
            }
        };
        vector ans{math.qpow(n,n,p)};
        cir(len,1,n+1){
            ranges::fill(f,vector(n,vector<lint>(2)));
            cir(i,0,n-len+1) f[i][i+len-1][0]=f[i][i+len-1][1]=1;
            check();
            auto prod=1ll;
            cir(i,0,len) (prod*=(n-max(i+1,len-i)+1))%=p;
            ans.push_back(f[0][n-1][0]*prod%p);
        }
        for(auto i=n;i;--i){
            cir(nxt,i+1,n+1) (ans[i]+=(p-1)*ans[nxt]%p*(nxt-i+1))%=p;
        }
        cir(i,1,n+1) (ans[0]+=(p-ans[i]))%=p;
        for(auto&i:ans) print("{} ",i);
        println("");
    }();
    return 0;
}
