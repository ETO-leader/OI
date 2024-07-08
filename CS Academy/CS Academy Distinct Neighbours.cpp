#include<bits/stdc++.h>
#define cir(i,a,b) for (int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
auto initc(int n){
    vector<VI> C(n,VI(n));C[0][0]=1;
    cir(i,1,n) cir(j,0,n){
        C[i][j]=C[i-1][j];
        if(j) (C[i][j]+=C[i-1][j-1])%=MOD;
    }
    return C;
}
auto reid(VI&a){
    unordered_map<int,int> id;
    for(auto&i:a) id.insert({i,0});
    int cnx=0;VI cx(a.size()+1);
    for(auto&[a,b]:id) b=++cnx;
    for(auto&i:a) i=id[i],++cx[i];
    return cx;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,stp=0;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    auto cx=reid(a);
    auto C=initc(n*2+7);
    vector<VI> D(2,VI(n+1));
    D[stp][0]=1;
    int prec=0;
    cir(i,0,n){
        if(!cx[i+1]) break;
        prec+=cx[i];
        fill(D[stp^1].begin(),D[stp^1].end(),0);
        cir(k,0,prec+1) if(D[stp][k]){
            cir(t,0,cx[i+1]) cir(l,0,k+1){
                if(l+t>cx[i+1]) break;
                if(l-t>k) continue;
                (D[stp^1][k-l+t]+=
                    D[stp][k]*C[cx[i+1]-1][t]%MOD
                    *C[k][l]%MOD*C[prec-k+1][cx[i+1]-t-l]
                )%=MOD;
            }
        }
        stp^=1;
    }
    cout<<D[stp][0]<<'\n';
    return 0;
}
