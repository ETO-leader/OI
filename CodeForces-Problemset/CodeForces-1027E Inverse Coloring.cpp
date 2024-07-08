#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<VI> D(n,VI(n+1));
    cir(i,0,n) D[i][i+1]=1;
    cir(i,1,n){
        cir(j,1,i+1) cir(k,i-j+1,i+1)
            (D[i][j]+=D[k-1][min(j,k)])%=MOD;
        (D[i][i+1]+=D[i][i])%=MOD;
    }
    auto w=D[n-1];
    for(int i=n;i;--i)
        ((w[i]+=MOD)-=w[i-1])%=MOD;
    cout<<[&](){
        lint res=0;
        cir(i,1,n+1) cir(j,1,n+1)
            (res+=(w[i]*w[j]*(i*j<k)))%=MOD;
        return (res*2)%MOD;
    }()<<'\n';
    return 0;
}
