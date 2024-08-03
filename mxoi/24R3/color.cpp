#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
ifstream fcin("color.in");
ofstream fcout("color.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
class tree{
private:
    vector<vector<int>> gr,up;
    vector<int> h;
    static constexpr auto ups=21;
    auto init(int u,int f=0)->void{
        up[u][0]=f;h[u]=h[f]+1;
        cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&i:gr[u]) if(i!=f) init(i,u);
    }
    auto dfs(int u,int f=0)->pair<int,int>{
        auto res=pair(0,u);
        for(auto&i:gr[u]) if(i!=f) res=max(res,dfs(i,u));
        ++res.first;
        return res;
    }
    auto lca(int u,int v){
        if(h[u]<h[v]) swap(u,v);
        cir(i,0,ups) if((h[u]-h[v])&(1<<i))
            u=up[u][i];
        if(u==v) return u;
        for(auto i=ups-1;~i;--i) if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
        return up[u][0];
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto dist(int u,int v){
        return h[u]+h[v]-h[lca(u,v)]*2;
    }
    auto registertree(){init(1);}
    auto diameter(){
        const auto u=dfs(1).second;
        const auto v=dfs(u).second;
        return pair(u,v);
    }
    tree(int _n):gr(_n+1),up(_n+1,vector<int>(ups)),h(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;tree gr(n);
    if(n==1) exit((cout<<0<<'\n',0));
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;gr.insert(u,v);
    }
    gr.registertree();
    const auto[u,v]=gr.diameter();
    auto mxrng=0;
    cir(i,1,n+1) mxrng=max(mxrng,min(gr.dist(i,u),gr.dist(i,v)));
    vector<int> updc(n);
    cir(i,1,n+1) ++updc[max(gr.dist(i,u),gr.dist(i,v))];
    vector<lint> f(n);
    auto cnt=n;
    for(auto i=n-1;i>mxrng-1;--i){
        f[i]=math.qpow(2,cnt+(cnt<n));
        cnt-=updc[i];
    }
    for(int i=n-1;i;--i) (f[i]+=MOD-f[i-1])%=MOD;
    auto ans=0ll;
    cir(i,0,n) (ans+=f[i]*i)%=MOD;
    fcout<<ans%MOD<<'\n';
    return 0;
}
