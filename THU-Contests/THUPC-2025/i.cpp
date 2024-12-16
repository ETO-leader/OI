#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<int> a(n),b(n);
        cir(i,0,n) cin>>a[i]>>b[i];
        const auto bx=13;
        vector<int> f(27);
        f[bx]=1;
        auto ans=0ll;
        cir(i,1,n+1){
            const auto g=f;
            fill(f.begin(),f.end(),0);
            cir(w,0,27){
                const auto rst=w-bx;
                if((i+rst)&1) continue;
                const auto wna=(i+rst)/2,wnb=(i-rst)/2;
                if(a[i-1]>-1&&(wna!=a[i-1]||wnb!=b[i-1])&&(wnb!=a[i-1]||wna!=b[i-1])) continue;
                if(wna<0||wnb<0) continue;
                if(max(wna,wnb)>10&&abs(wna-wnb)>1&&i!=n) continue;
                if(w) (f[w]+=g[w-1])%=MOD;
                if(w<26) (f[w]+=g[w+1])%=MOD;
                if(i==n&&max(wna,wnb)>10&&abs(wna-wnb)>1) (ans+=f[w])%=MOD;
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
