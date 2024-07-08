#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
const string errformat="No solution";
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
auto inv(lint x){return qpow(x,MOD-2);}
void formaterr(unsigned exit_c){
    cout<<errformat<<'\n';
    exit(exit_c);
}
auto modminus(lint a,lint b){
    return ((a-b)%MOD+MOD)%MOD;
}
void inv_matrix(vector<VI>&a){
    const int n=a.size();
    cir(i,0,n){
        int k=i;
        cir(j,i+1,n) if(a[j][i]>a[k][i]) k=j;
        if(k!=i) swap(a[i],a[k]);
        if(!a[i][i]) formaterr(0);
        const auto invi=inv(a[i][i]);
        cir(k,0,n) if(k!=i){
            const auto w=a[k][i]*invi%MOD;
            cir(j,i,n*2)
                a[k][j]=modminus(a[k][j],a[i][j]*w);
        }
        cir(j,0,n*2) (a[i][j]*=invi)%=MOD;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<VI> mat(n,VI(n*2));
    for(auto&i:mat) cir(j,0,n) cin>>i[j];
    cir(i,0,n) mat[i][i+n]=1;
    inv_matrix(mat);
    for(auto&i:mat){
        cir(j,n,n*2) cout<<i[j]<<' ';
        cout<<'\n';
    }
    return 0;
}
