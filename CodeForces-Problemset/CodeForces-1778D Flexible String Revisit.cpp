#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=998244353;
auto diff(auto a,auto b,int len){
    int res=0;
    cir(i,0,len){
        res+=(*a)!=(*b);++a;++b;
    }
    return res;
}
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
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        string x,y;cin>>x>>y;
        const auto k=diff(
            x.begin(),y.begin(),n);
        VI D(n+1);D[n]=1;
        for(int i=n-1;~i;--i){
            D[i]=(n+(n-i)*D[i+1]%MOD
                )%MOD*inv(i)%MOD;
        }
        cout<<accumulate(D.begin(),D.begin()+
            k+1,(lint)(0))%MOD<<'\n';
    }
    return 0;
}
