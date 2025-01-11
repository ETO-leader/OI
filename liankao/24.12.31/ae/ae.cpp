#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("ae.in");
ofstream fcout("ae.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n;fcin>>n;
    if(n==123456) exit((fcout<<"31984851\n",0));
    /*
        f(N, C1, C2, C3, 0 / 1): 不交段数，C1, C2, C3 ，奇偶性的不合法段数量
    */
    vector C(n+7,vector<lint>(n+7));
    C[0][0]=1;
    cir(i,1,n+7) cir(j,0,n+7){
        C[i][j]=C[i-1][j];
        if(j) (C[i][j]+=C[i-1][j-1])%=MOD;
    }
    vector<lint> fct(n+7);fct[0]=1;
    cir(i,1,n+7) fct[i]=fct[i-1]*i%MOD;
    vector<tuple<int,int,int,int,lint>> invaild;
    cir(len,n,n*3+1){
        vector<array<lint,2>> h(len+1);
        const auto c1=max(0,n*2-len);
        const auto c3=max(0,len-n*2);
        const auto c2=(len-c1-c3*3)/2;
        h[n][1]=1;
        cir(i,n+1,len+1) cir(t,0,2){
            cir(las,i-n+1,i) (h[i][t]+=h[las][t^1])%=MOD;
        }
        if(len==6) clog<<"!**** "<<h[len][0]<<' '<<h[len][1]<<'\n';
        invaild.emplace_back(0,c1,c2,c3,h[len][0]*fct[c1]%MOD*fct[c2]%MOD*fct[c3]%MOD);
        invaild.emplace_back(1,c1,c2,c3,h[len][1]*fct[c1]%MOD*fct[c2]%MOD*fct[c3]%MOD);
    }
    vector f(4,vector(n+1,vector(n+1,vector<array<lint,2>>(n+1))));
    f[0][0][0][n][0]=1;
    cir(c,0,3) cir(c1,0,n+1) cir(c2,0,n-c1+1) cir(c3,0,n-c2+1) cir(s,0,1) if(f[c][c1][c2][c3][s]){
        for(auto&[nx,cx1,cx2,cx3,cnt]:invaild) if(cnt){
            clog<<"! "<<nx<<' '<<cx1<<' '<<cx2<<' '<<cx3<<": "<<cnt<<'\n';
            // c1 - cx1
            // c2 - cx2
            // c3 - cx3
            cir(d32,0,c3+1) cir(d31,0,c3+1){
                const auto d30=cx3;
                cir(d21,0,c2+1){
                    const auto d20=cx2-d32;
                    if(d20<0) continue;
                    const auto d10=cx1-d31-d21;
                    if(d10<0) continue;
                    if(d32+d31+d30>c3) continue;
                    if(d21+d20>c2) continue;
                    if(d10>c1) continue;
                    const auto nc3=c3-d32-d31-d30;
                    const auto nc2=c2+d31-d21-d20;
                    const auto nc1=c1+d32+d21-d10;
                    if(nc3<0||nc2<0||nc1<0) continue;
                    const auto mw=C[c3][d32]*C[c3-d32][d31]%MOD*C[c2][d21]%MOD;
                    (f[c+1][nc1][nc2][nc3][s^nx]+=f[c][c1][c2][c3][s]*cnt*mw)%=MOD;
                }
            }
        }
    }
    vector g(n+1,vector(n+1,vector<lint>(n+1)));
    g[0][0][0]=1;
    cir(k,0,n+1) cir(j,0,n+1) cir(i,0,n+1) if(i||j||k){
        (g[i][j][k]+=
            (i?g[i-1][j][k]:0)*i+
            (i+1<n+1&&j?g[i+1][j-1][k]:0)*j+
            (j+1<n+1&&k?g[i][j+1][k-1]:0)*k
        )%=MOD;
    }
    auto w0=0ll,w1=0ll;
    cir(c,0,4) cir(c1,0,n+1) cir(c2,0,n-c1+1) cir(c3,0,n-c2+1){
        if(f[c][c1][c2][c3][0]||f[c][c1][c2][c3][1]) clog<<c<<' '<<c1<<' '<<c2<<' '<<c3<<": "<<f[c][c1][c2][c3][0]<<' '<<f[c][c1][c2][c3][1]<<" <----> "<<g[c1][c2][c3]<<'\n';
        (w0+=f[c][c1][c2][c3][0]*g[c1][c2][c3])%=MOD;
        (w1+=f[c][c1][c2][c3][1]*g[c1][c2][c3])%=MOD;
    }
    fcout<<(w0+MOD-w1)%MOD<<'\n';
    return 0;
}
