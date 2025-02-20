#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n-1);
    for(auto&i:a) cin>>i;
    auto ans=1ll;
    const auto maxa=*ranges::max_element(a);
    cir(x,2,maxa+1){
        vector<int> c(n-1);
        cir(i,0,n-1){
            while(!(a[i]%x)) a[i]/=x,++c[i];
        }
        if(!(*ranges::max_element(c))) continue;
        const auto s=accumulate(c.begin(),c.end(),0);
        vector pwx(s+1,1ll);
        cir(i,1,s+1) pwx[i]=pwx[i-1]*x%MOD;
        vector<vector<lint>> f(s+1,vector<lint>(2));
        cir(i,1,s+1) f[i][0]=pwx[i];
        f[0][1]=1;
        for(auto&cw:c){
            vector<vector<lint>> nf(s+1,vector<lint>(2));
            cir(w,0,s+1){
                if(w>cw-1){
                    const auto nxt=w==cw;
                    (nf[w-cw][nxt]+=f[w][0]*pwx[w-cw])%=MOD;
                    (nf[w-cw][1]+=f[w][1]*pwx[w-cw])%=MOD;
                }
                if(w+cw<s+1&&cw){
                    (nf[w+cw][0]+=f[w][0]*pwx[w+cw])%=MOD;
                    (nf[w+cw][1]+=f[w][1]*pwx[w+cw])%=MOD;
                }
            }
            f=nf;
        }
        auto sum=0ll;
        for(auto&x:f) (sum+=x[1])%=MOD;
        (ans*=sum)%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
