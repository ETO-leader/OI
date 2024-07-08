#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<VI> c(n,VI(n));
    for(auto&i:c) for(auto&j:i) cin>>j;
    const int _sz=1<<n;
    VI D(_sz),C(_sz,1);
    cir(i,0,_sz) cir(u,0,n) cir(v,(u+1),n)
        if(((1<<u)&i)&&((1<<v)&i))
            (C[i]*=(c[u][v]+1))%=MOD;
    D=C;
    cir(i,0,_sz){
        const int ns=i^(i&(-i));
        for(int sx=ns;sx;sx=((sx-1)&ns))
            ((D[i]-=C[sx]*D[i^sx]%MOD)+=MOD)%=MOD;
    }
    cout<<D[_sz-1]<<'\n';
    return 0;
}
