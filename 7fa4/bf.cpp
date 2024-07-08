#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    vector<lint> ans(107);
    ans[0]=1;ans[1]=2;
    cir(i,2,107){
        ans[i]=(i-1)*ans[i-1];
        cir(p,2,i-1){
            if(i==5){
                clog<<(p-1)<<":"<<p<<' '<<i-p<<'\n';
            }
            (ans[i]+=((p-1)*ans[p]%MOD*ans[i-p]))%=MOD;
        }
    }
    while(T--){
        int n;cin>>n;
        cout<<ans[n]<<'\n';
    }
    return 0;
}
