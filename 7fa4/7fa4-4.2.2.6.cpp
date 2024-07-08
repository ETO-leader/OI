#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
using lint=long long;
using VI=vector<lint>;
vector<VI> Cx;
VI fact;
void init_all(int n){
    fact.resize(n,1);
    cir(i,1,n) fact[i]=fact[i-1]*i%MOD;
    Cx.assign(n,VI(n));Cx[0][0]=1;
    cir(i,1,n) cir(j,0,n){
        if(j) Cx[i][j]=Cx[i-1][j-1];
        (Cx[i][j]+=Cx[i-1][j])%=MOD;
    }
}
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint p){return qpow(p,MOD-2);}
lint C(int a,int b){
    return Cx[a][b];
}
lint calculatei(lint a,lint b){
    lint res=0,w=-1;
    cir(i,0,b){
        (res+=(w=-w)*C(b,i)*qpow(b-i,a))%=MOD;
    }
    return (res*inv(fact[b])%MOD+MOD)%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m;cin>>n>>m;init_all(m+7);
    cir(i,1,m+1) cout<<calculatei(n,i)<<' ';
    cout<<'\n';
    return 0;
}
