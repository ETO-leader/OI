#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        VI v(n),cnx(n+1),D(n+1),p2(n+1,1);
        for(auto&i:v) (cin>>i),cnx[i]++;
        cir(i,1,n+1) p2[i]=(p2[i-1]<<1)%MOD;
        for(auto&i:p2) (--(i+=MOD))%=MOD;
        for(auto&i:cnx) i=p2[i];
        lint cnxp=(cnx[0]+cnx[1]+cnx[0]*cnx[1])%MOD;
        D[0]=cnx[0];D[1]=(cnx[1]*cnx[0])%MOD;
        cir(i,2,n+1){
            (cnxp+=(D[i-1]*cnx[i]+D[i-2]*cnx[i]))%=MOD;
            D[i]=D[i-1]*cnx[i]%MOD;
        //    cout<<i<<' '<<D[i-1]*cnx[i]+D[i-2]*cnx[i]<<'\n';
        }
        cout<<cnxp<<'\n';
    }
    return 0;
}
