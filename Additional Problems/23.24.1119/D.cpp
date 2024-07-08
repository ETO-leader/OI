#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
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
    lint n,m,v;cin>>n>>m>>v;VI a(n);
    for(auto&i:a) cin>>i;
    vector<VI> D(n+1,VI(n+1));
    D[0][0]=1;
    cir(i,1,n+1){
        const auto cst=i*inv(n)%MOD*v%MOD;
        cir(j,0,i){
            (D[i][j]+=D[i-1][j]*((a[i-1]+
                j*v)%MOD)%MOD)%=MOD;
            (D[i][j+1]+=D[i-1][j]*
                cst%MOD*(m-j))%=MOD;
        }
    }
    cout<<accumulate(D[n].begin(),
        D[n].end(),(lint)(0))%MOD<<'\n';
    return 0;
}
