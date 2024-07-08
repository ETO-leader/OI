#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint MOD=1e9+7;
lint qpow(lint tp,lint t){
    lint ret=1;
    while(t){
        if(t&1) (ret*=tp)%=MOD;
        (tp*=tp)%=MOD;t>>=1;
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m,cnt=0,c;cin>>n>>m;
    cir(i,0,n) cir(j,0,n) cin>>c,cnt+=c;
    cout<<qpow(cnt,m)<<endl;
    return 0;
}