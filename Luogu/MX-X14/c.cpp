#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
class dsu{
private:
    vector<int> f,val;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        if(u==v) return;
        f[u]=v;
        val[v]^=val[u];
    }
    auto value(auto u){return val[findset(u)];}
    dsu(vector<int> _v):f(_v.size()),val(_v){
        iota(f.begin(),f.end(),0);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;
        vector uv(n+m,1);
        vector<unordered_set<int>> ban(n+m);
        cir(i,0,k){
            int x,y,w;cin>>x>>y>>w;--x;--y;
            uv[x]^=w;
            uv[y+n]^=w;
            ban[x].emplace(y+n);
            ban[y+n].emplace(x);
        }
        set<int> s;
        cir(i,0,n+m) s.emplace(i);
        dsu qwq(uv);
        auto pwx=(lint)(n)*m-k;
        auto dfs=[&](auto __self,int u)->void {
            s.extract(u);
            auto v=-1,lim=n+m;
            if(u>n-1) lim=n;
            else v=n-1;
            for(auto it=s.upper_bound(v);it!=s.end()&&*it<lim;it=s.upper_bound(v)){
                v=*it;
                if(!ban[u].contains(*it)) __self(__self,v),pwx-=(qwq.findset(u)!=qwq.findset(v)),qwq.merge(u,v);
            }
        };
        cir(i,0,n) if(s.contains(i)) dfs(dfs,i);
        cir(i,0,n+m) if(qwq.value(i)) return cout<<0<<'\n',void();
        cout<<(pwx>-1?math.qpow(2,pwx):0)<<'\n';
    }();
    return 0;
}
