#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename T,class comp>
    using rbt=tree<T,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
class tree{
private:
    vector<vector<int>> gr;
    vector<pair<int,int>> lfs;
    vector<int> fx,vis,h;
    auto dfs(int u,int dep=0,int f=-1)->void{
        auto isleaf=true;fx[u]=f;h[u]=dep;
        for(auto&i:gr[u]) if(i!=f) isleaf=false,dfs(i,dep+1,u);
        if(isleaf) lfs.emplace_back(dep,u);
    }
    auto remove(int u,int&dsum,rbt<int,greater_equal<int>>&rb){
        while(u>-1&&(!vis[u])) --dsum,rb.insert(h[u]),vis[u]=true,u=fx[u];
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        dfs(0);
        ranges::sort(lfs,greater<pair<int,int>>());
        const auto n=(int)(gr.size());
        auto cnt=n,ans=n;
        rbt<int,greater_equal<int>> rb;
        for(auto&[dep,u]:lfs){
            remove(u,cnt,rb);
            ans=min<int>(ans,cnt+rb.order_of_key(dep));
        }
        return ans;
    }
    tree(int _n):gr(_n),fx(_n),vis(_n),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        tree tr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            tr.link(u,v);
        }
        println("{}",tr.check());
    }();
    return 0;
}
