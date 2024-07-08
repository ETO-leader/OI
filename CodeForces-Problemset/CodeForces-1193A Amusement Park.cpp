#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
constexpr int MOD=998244353;
constexpr lint inv2=(MOD+1)/2;
using VI=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    VI D(1<<n),f(1<<n),g(1<<n),a(m),b(m);
    cir(i,0,m) cin>>a[i]>>b[i],--a[i],--b[i];
    [&](){
        f[0]=MOD-1;g[0]=1;
        cir(i,1,(1<<n)) f[i]=MOD-f[i&(i-1)];
    }();
    cir(i,1,(1<<n)) cir(j,0,m){
        if((i>>a[j]&1)&&(i>>b[j]&1)){
            D[i]=1;break;
        }
    }
    cir(i,1,(1<<n)){
        for(int j=i;j;j=((j-1)&i)) if(!D[j])
            (g[i]+=g[i^j]*f[j])%=MOD;
    }
    cout<<g.back()*m%MOD*inv2%MOD<<'\n';
    return 0;
}
