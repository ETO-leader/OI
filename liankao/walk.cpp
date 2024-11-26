#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("walk.in");
ofstream fcout("walk.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class invaildcase{};
class tree{
private:
    vector<vector<int>> gr;
    vector<lint> v;
    vector<int> vis;
    auto dfsrt(int u,int&ans,lint&cans,const lint sum,int f=-1)->lint{
        if(vis[u]) throw invaildcase();
        vis[u]=true;
        auto res=v[u];
        auto submax=0ll;
        for(auto&i:gr[u]) if(i!=f){
            const auto w=dfsrt(i,ans,cans,sum,u);
            res+=w;submax=max(submax,w);
        }
        if(max(submax,sum-res)<cans){
            cans=max(submax,sum-res);ans=u;
        }
        return res;
    }
    auto dfs(int u,lint&ans,int f=-1)->lint{
        auto res=0ll;
        for(auto&i:gr[u]) if(i!=f) res+=dfs(i,ans,u);
        ans+=res;
        return res+v[u];
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        auto u=-1;auto c=_infl;dfsrt(0,u,c,accumulate(v.begin(),v.end(),0ll));
        if(!(*min_element(vis.begin(),vis.end()))) throw invaildcase();
        auto ans=0ll;
        dfs(u,ans);
        return ans;
    }
    auto initv(auto x){v=x;}
    tree(int _n):gr(_n),vis(_n){}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,q;fcin>>n>>q;
    vector<lint> v(n);
    for(auto&i:v) fcin>>i;
    vector<pair<int,int>> es(n-1);
    for(auto&[u,v]:es) fcin>>u>>v,--u,--v;
    for(auto&[u,v]:es) if(u>v) swap(u,v);
    auto ans=0ll;
    cir(i,0,q) [&]{
        int a,b,c,d;fcin>>a>>b>>c>>d;--a;--b;--c;--d;
        tree tr(n);
        tr.link(c,d);
        if(a>b) swap(a,b);
        for(auto&[u,v]:es) if(u!=a||v!=b) tr.link(u,v);
        tr.initv(v);
        try{
            ans^=tr.check()*2;
        }catch(invaildcase){}
    }();
    fcout<<ans<<'\n';
    return 0;
}
