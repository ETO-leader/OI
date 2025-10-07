#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.ans");
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,c;inf>>n>>c;vector<int> a(n);
    for(auto&x:a) inf>>x;
    vector<vector<lint>> f(n,vector<lint>(1<<n));
    cir(i,0,n) f[i][1<<i]=1;
    cir(s,0,(1<<n)) cir(u,0,n) if((s>>u)&1){
        cir(v,0,n) if((!((s>>v)&1))&&(int64_t)(a[u])*a[v]<c+1) (f[v][s|(1<<v)]+=f[u][s])%=MOD;
    }
    auto ans=0ll;
    cir(u,0,n) (ans+=f[u][(1<<n)-1])%=MOD;
    ouf<<ans<<'\n';
    return 0;
}
