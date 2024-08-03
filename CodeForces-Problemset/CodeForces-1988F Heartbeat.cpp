#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    auto carray(int n,int m){
        vector res(n,vector<lint>(m));
        res[0][0]=1;
        cir(i,1,n) cir(j,0,m){
            res[i][j]=res[i-1][j];
            if(j) (res[i][j]+=res[i-1][j-1])%=MOD;
        }
        return res;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> a(n),b(n),c(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    for(auto&i:c) cin>>i;
    for(auto i:{&a,&b}) i->insert(i->begin(),0);
    c.push_back(0);
    vector f(2,vector(n+7,vector<lint>(n+7)));
    vector fcnt(n+1,vector<lint>(n+1)),gcnt(n+1,vector<lint>(n+1));
    auto nw=0;
    f[nw][1][0]=1;fcnt[0][0]=a[1];gcnt[0][0]=b[1];
    cir(i,1,n+1){
        nw^=1;
        ranges::fill(f[nw],vector<lint>(n+7));
        cir(j,0,i+1) cir(k,0,i){
            (fcnt[i][k]+=f[nw^1][j][k]*a[j+1])%=MOD;
            (gcnt[i][(i-1)-k]+=f[nw^1][j][k]*b[j+1])%=MOD;
            (f[nw][j+1][k+1]+=f[nw^1][j][k])%=MOD;            // New elemant @ pos 1
            (f[nw][j][k]+=f[nw^1][j][k]*(k+1))%=MOD;          // New element @ x pos x+k
            (f[nw][j][k+1]+=f[nw^1][j][k]*(i-1-k))%=MOD;      // New element @ x pos x-k
        }
    }
    vector fx(n+1,vector<lint>(n+1));
    cir(i,0,n+1) cir(j,0,n+1) cir(nxt,0,n-j){
        (fx[i][nxt]+=fcnt[i][j]*c[nxt+j+(bool)(i)])%=MOD;
    }
    auto C=math.carray(n+7,n+7);
    cir(len,1,n+1){
        auto ans=0ll;
        cir(p,0,len) cir(kx,0,n+1){
            (ans+=fx[p][kx]*gcnt[len-p-1][kx]%MOD*C[len-1][p])%=MOD;
        }
        cout<<ans<<' ';
    }
    cout<<'\n';
    return 0;
}
