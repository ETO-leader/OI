#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=2333;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int q;cin>>q;
    const auto c=[](int n,int m){
        vector<vector<lint>> c(n,vector<lint>(m));
        c[0][0]=1;
        cir(i,1,n) cir(j,0,m){
            c[i][j]=c[i-1][j];
            if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
        }
        return c;
    }(MOD,MOD);
    auto prec=c;
    cir(i,0,MOD) cir(j,1,MOD){
        (prec[i][j]+=prec[i][j-1])%=MOD;
    }
    auto lucas=[&](auto __self,lint a,lint b){
        if(a<MOD&&b<MOD) return c[a][b];
        return c[a%MOD][b%MOD]*__self(__self,a/MOD,b/MOD)%MOD;
    };
    auto calc=[&](auto __self,lint a,lint b){
        if(b<0) return (lint)(0);
        if(a<MOD&&b<MOD) return prec[a][b];
        return (__self(__self,a/MOD,b/MOD-1)*prec[a%MOD].back()
            +lucas(lucas,a/MOD,b/MOD)*prec[a%MOD][b%MOD])%MOD;
    };
    cir(i,0,q){
        lint a,b;cin>>a>>b;
        cout<<calc(calc,a,b)<<'\n';
    }
    return 0;
}
