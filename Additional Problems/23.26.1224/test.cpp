#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("string.in");
ofstream fcout("string.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
auto inv(lint x){return qpow(x,MOD-2);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;VI a(n);
    for(auto&i:a) fcin>>i;
    auto cpa=a;
    vector<VI> cst(n*2,VI(n*2));
    cir(p,0,n){
        vector<VI> D(n+1,VI(*max_element(a.begin(),a.end())+1));
        cir(x,0,a[0]+1) D[1][x]=(a[0]-x);
        cir(i,1,n){
            lint pre=0,mpre=0;
            cir(j,1,a[i-1]+1){
                (pre+=D[i][j]*(a[i]+j))%=MOD;
                (mpre+=D[i][j])%=MOD;
            }
            cir(k,0,a[i]+1){
                (D[i+1][k]+=pre-(k*mpre%MOD)+MOD)%=MOD;
            }
        }
        cir(i,1,n+1){
            cst[p][p+i-1]=D[i][0];
        }
        a.push_back(a.front());
        a.erase(a.begin());
    }
    a=cpa;
    lint ans=0;
    cir(p,0,n){
        VI f(n);
        (ans+=cst[p][n+p-1])%=MOD;
        cir(i,0,n) f[i]=cst[p][p+i];
        cir(x,0,n-p){
            cir(px,x+1,n-p){
                (f[px]+=f[x]*cst[p+x+1][p+px])%=MOD;
            }
            (ans+=f[x]*cst[p+x+1][n+p-1])%=MOD;
        }
    }
    fcout<<ans<<'\n';
    return 0;
}
