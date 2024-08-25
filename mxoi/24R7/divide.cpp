#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("divide.in");
ofstream fcout("divide.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    auto dp=[&](){
        vector<lint> f(n);
        auto mx=0;
        cir(p,0,n){
            mx=max(a[p],mx);
            if(mx<p+2) f[p]=1;
        }
        cir(i,0,n){
            auto mxi=0;
            cir(nxt,i+1,n){
                mxi=max(a[nxt],mxi);
                if(mxi<(nxt-i)+1) (f[nxt]+=f[i])%=MOD;
            }
        }
        return f[n-1];
    };
    cir(i,0,n){
        const auto ax=a;
        a[i]=1;
        fcout<<dp()<<' ';
        a=ax;
    }
    fcout<<'\n';
    return 0;
}
