#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<lint> g(n+1);
        g[0]=1;
        vector<int> pre(n+1);
        map<int,lint> f;
        cir(i,1,n+1) pre[i]=a[i-1]^pre[i-1];
        cir(i,1,n+1){
            if(g[i-1]) (f[pre[i-1]]+=g[i-1]*3)%=MOD;
            (g[i]+=f[pre[i]])%=MOD;
            (f[pre[i-1]]+=f[pre[i]]*2)%=MOD;
            f[pre[i]]=0;
        }
        auto ans=g[n];
        for(auto&[las,w]:f) (ans+=w)%=MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
