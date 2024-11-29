#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int m;cin>>m;
        vector<vector<int>> fcts(m+1);
        cir(i,1,m+1) for(auto x=i;x<m+1;x+=i) fcts[x].push_back(i);
        vector<lint> f(m+1),cur(m+1),uni(m+1),sum(m+1);
        auto ans=0ll;
        for(auto i=m;i;--i){
            for(auto&x:views::reverse(fcts[i])){
                uni[x]=sum[x]*2%MOD;
                for(auto&w:fcts[i]) if(w>x&&(!(w%x))) (uni[x]+=MOD-uni[w])%=MOD;
                cur[x]=(uni[x]+MOD-(f[x]*2)%MOD)%MOD;
            }
            (++cur[i])%=MOD;
            for(auto&x:fcts[i]){
                (f[x]+=cur[x])%=MOD;(ans+=cur[x])%=MOD;
                for(auto&w:fcts[x]) (sum[w]+=cur[x])%=MOD;
            }
        }
        println("{}",ans);
    }();
    return 0;
}
