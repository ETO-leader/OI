#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxn=30007;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> vis;
    vector<bitset<maxn>> f;
    auto dfs(int u){
        if(vis[u]) return;
        vis[u]=true;
        f[u].set(u);
        for(auto&i:gr[u]){
            dfs(i);f[u]|=f[i];
        }
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
    }
    auto check(){
        cir(i,0,(int)(gr.size())) dfs(i);
        vector<int> ans(gr.size());
        cir(i,0,(int)(gr.size())) ans[i]=f[i].count();
        return ans;
    }
    graph(int _n):gr(_n),vis(_n),f(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    const auto ans=gr.check();
    ranges::copy(ans,ostream_iterator<int>(cout,"\n"));
    return 0;
}
