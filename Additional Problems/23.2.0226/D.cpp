#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
//p:首项，k:公差，v:最小值
bool out_range(int k){
    return k<0||k>9;
}
lint findnum(lint p,lint k,lint v){
    lint res=p;
    while(res<v){
        if(out_range((p+=k))) return _inf;
        (res*=10)+=p;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint x,ans=_inf;cin>>x;
    cir(i,1,10) cir(j,-9,10)
        ans=min(ans,findnum(i,j,x));
    cout<<ans<<'\n';
    return 0;
}
