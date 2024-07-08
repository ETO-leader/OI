#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=1e9+7;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint x){return qpow(x,MOD-2);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        lint x;cin>>x;
        vector<lint> D(x+1),suf(x*2);
        D[x]=suf[x]=1;
        for(int i=x-1;i;--i){
            D[i]=(suf[i+1]-suf[i*2]+MOD)%MOD;
            suf[i]=(suf[i+1]+D[i])%MOD;
        }
        cir(i,1,x+1){
            cout<<D[i]*qpow(2,i/2)%MOD
                *inv(qpow(2,x-1))%MOD<<'\n';
        }
    }
    return 0;
}
