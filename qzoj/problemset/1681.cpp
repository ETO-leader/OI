#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class acam{
private:
    vector<map<char,int>> v;
    vector<int> fail;
    vector<bool> vis;
    int cnt;
public:
    auto emplace(string s){
        auto u=0;
        for(auto&c:s){
            if(!v[u][c]) v[u][c]=++cnt;
            u=v[u][c];
        }
        return vis[u];
    }
    auto init(){
        queue<int> q;q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&[vx,id]:v[u]){
                if(u){
                    auto x=fail[u];
                    while(x&&(!v[x].count(vx))) x=fail[x];
                    fail[id]=v[x][vx];
                }
                q.emplace(id);
            }
        }
    }
    auto check(string s){
        auto u=0;
        for(auto&c:s){
            while(u&&(!v[u].count(c))) u=fail[u];
            u=v[u][c];
            vis[u]=true;
        }
        vector<vector<int>> vx(cnt+1);
        cir(i,1,cnt+1) vx[fail[i]].emplace_back(i);
        auto dfs=[&](auto __self,int u)->bool {
            auto res=(bool)(vis[u]);
            for(auto&id:vx[u]) res|=__self(__self,id);
            return (bool)(vis[u]=res);
        };
        dfs(dfs,0);
    }
    acam(int _n):v(_n),fail(_n),vis(_n),cnt(0){}
};
static constexpr auto maxl=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        acam ac(maxl);
        vector<string> q(n);
        for(auto&i:q) cin>>i,ac.emplace(i);
        ac.init();
        string s;cin>>s;
        ac.check(s);
        auto ans=0;
        cir(i,0,n) ans+=ac.emplace(q[i]);
        cout<<ans<<'\n';
    }();
    return 0;
}
