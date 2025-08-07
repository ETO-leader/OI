#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=10000;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    auto pw=1,cnt=1,cur=1;
    auto ans=0;
    cir(i,0,n){
        if(!cur) cur=(++cnt),(pw*=2)%=MOD;
        --cur;
        (ans+=pw)%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
