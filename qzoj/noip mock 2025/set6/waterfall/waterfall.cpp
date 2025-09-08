#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("waterfall.in");
ofstream ouf("waterfall.out");
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<vector<int>> vx(n);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        vx[u].emplace_back(v);
        vx[v].emplace_back(u);
    }
    if(m==n-1){
        vector<lint> ans(n);
        static constexpr auto inv2=math.inv(2);
        vector<int> siz(n);
        auto init=[&](auto __self,int u,int f)->int {
            siz[u]=1;
            for(auto&i:vx[u]) if(i!=f) siz[u]+=__self(__self,i,u);
            return siz[u];
        };
        auto dfs=[&](auto __self,int u,int f,lint p)->void {
            ans[u]+=p;
            auto sum=0;
            for(auto&i:vx[u]) if(i!=f) sum+=siz[i];
            for(auto&i:vx[u]) if(i!=f) __self(__self,i,u,(p+(sum-siz[i])*inv2+1)%MOD);
        };
        init(init,0,0);
        dfs(dfs,0,0,1);
        for(auto&x:ans) ouf<<x<<' ';
        ouf<<'\n';
    }else{
        vector<lint> ans(n);
        auto dfs=[&](auto __self,int s,basic_string<int> path,lint p){
            if(s==(1<<n)-1) return;
            if(!(s&(1<<path.back()))){
                s|=(1<<path.back());
                (ans[path.back()]+=p*__builtin_popcount(s))%=MOD;
            }
            vector<int> target;
            for(auto&i:vx[path.back()]) if(!((s>>i)&1)) target.emplace_back(i);
            if(target.empty()){
                auto np=path;
                np.pop_back();
                __self(__self,s,np,p);
            }else{
                auto ivn=math.inv(target.size());
                for(auto&x:target) __self(__self,s,path+x,p*ivn%MOD);
            }
        };
        dfs(dfs,0,basic_string<int>(),1);
        for(auto&x:ans) ouf<<x<<' ';
        ouf<<'\n';
    }
    return 0;
}
