#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("b.in");
ofstream ouf("b.out");
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,p;inf>>n>>p;
    vector<int> ls(n),rs(n);
    cir(i,0,n) inf>>ls[i]>>rs[i],--ls[i],--rs[i];
    vector<int> siz(n);
    vector<int> mn(n);
    auto dfs=[&](auto __self,int u){
        if(u<0) return mn[u]=_inf,1ll;
        auto res=1ll;
        (res*=__self(__self,ls[u]))%=p;
        (res*=__self(__self,rs[u]))%=p;
        const auto lsz=(~ls[u])?siz[ls[u]]:0;
        const auto rsz=(~rs[u])?siz[rs[u]]:0;
        (res*=rw)%=p;
        if(lsz&&lsz==rsz) (res*=2)%=p;
        if(lsz==1&&(rsz!=1)) (res*=2)%=p;
        siz[u]=max(lsz,rsz)+1;
        return res;
    };
    ouf<<dfs(dfs,0)<<'\n';
    return 0;
}
