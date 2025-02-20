#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,p;cin>>n>>m>>p;
    vector C(n+7,vector<lint>(n+7));
    C[0][0]=1;
    cir(i,1,n+7) cir(j,0,n+7){
        C[i][j]=C[i-1][j];
        if(j) (C[i][j]+=C[i-1][j-1])%=p;
    }
    vector<lint> f(n+1),g(n+1);
    f[0]=1;
    cir(i,1,n+1) cir(x,1,i+1) (f[i]+=(i+1)*f[x-1]%p*f[i-x]%p*C[i-1][x-1])%=p;
    cir(i,1,n+1) cir(x,1,i+1) (g[i]+=(i+1)*((f[x-1]*g[i-x]+g[x-1]*f[i-x])%p)%p*C[i-1][x-1]+(C[x][2]+C[i-x+1][2])*f[x-1]%p*f[i-x]%p*C[i-1][x-1])%=p;
    vector h(n+1,vector<lint>(n+1)),r(n+1,vector<lint>(n+1));
    h[0][0]=1;
    cir(i,1,n+1){
        cir(j,0,i){
            h[i][j]=h[i-1][j];
            r[i][j]=r[i-1][j];
            cir(c,1,j+1){
                (h[i][j]+=h[i-c-1][j-c]*C[j][c]%p*f[c])%=p;
                (r[i][j]+=(r[i-c-1][j-c]*f[c]+h[i-c-1][j-c]*g[c])%p*C[j][c])%=p;
            }
        }
        h[i][i]=f[i];
        r[i][i]=g[i];
    }
    println("{}",r[n][m]);
    return 0;
}
