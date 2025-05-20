#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<int>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
static constexpr auto maxsc=650;
enum operations{stc_none,stc_push,stc_pop};
class tree{
private:
    static constexpr auto ups=21;
    vector<vector<int>> gr,up;
    vector<operations> tags;
    vector<vector<pair<int,int>>> qry;
    vector<int> ans,dep,uid;
    int qcnt;
    void init(int u,int f=0){
        up[0][u]=f;dep[u]=dep[f]+1;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        for(auto&i:gr[u]) init(i,u);
    }
    void dfs(int u,rbt<int>&spos){
        vector<int> pops,ins;
        if(tags[u]==stc_push) pops.emplace_back(u),spos.insert(u);
        if(tags[u]==stc_pop) ans[uid[u]]=*prev(spos.end()),ins.emplace_back(*prev(spos.end())),spos.erase(prev(spos.end()));
        for(auto&x:qry[u]){
            const auto lc=x.first,id=x.second;
            ans[id]=min<int>(ans[id],spos.order_of_key(lc+1));
        }
        for(auto&i:gr[u]) dfs(i,spos);
        for(auto&x:pops) spos.erase(spos.find(x));
        for(auto&x:ins) spos.insert(x);
    }
    int lca(int u,int v){
        if(dep[u]<dep[v]) swap(u,v);
        cir(i,0,ups) if((dep[u]-dep[v])&(1<<i)) u=up[i][u];
        if(u==v) return u;
        for(auto i=ups-1;~i;--i) if(up[i][u]!=up[i][v]){
            u=up[i][u];v=up[i][v];
        }
        return up[0][u];
    }
public:
    void link(int u,int v,operations op,int id=-1){
        gr[u].emplace_back(v);
        tags[v]=op;
        if(op==stc_pop) uid[v]=id,++qcnt;
    }
    void init(){init(0);}
    void addqry(int u,int v,int id){
        ++qcnt;
        const auto lc=lca(u,v);
        qry[u].emplace_back(lc,id);
        qry[v].emplace_back(lc,id);
    }
    vector<int> check(){
        ans.resize(qcnt,(int)(gr.size())+7);
        auto x=rbt<int,less<int>>();
        dfs(0,x);
        return ans;
    }
    tree(int _n):gr(_n),up(ups,vector<int>(_n)),uid(_n),tags(_n),qry(_n),dep(_n),qcnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n+1);
    auto cnt=0;
    vector<tuple<int,int,int>> qs;
    cir(u,1,n+1){
        string op;cin>>op;
        if(op=="a"){
            int f;cin>>f;
            gr.link(f,u,stc_push);
        }else if(op=="b"){
            int f;cin>>f;
            gr.link(f,u,stc_pop,cnt);
            ++cnt;
        }else{
            int f,v;cin>>f>>v;
            gr.link(f,u,stc_none);
            qs.emplace_back(u,v,cnt);
            ++cnt;
        }
    }
    gr.init();
    for(auto&x:qs) gr.addqry(get<0>(x),get<1>(x),get<2>(x));
    const auto ans=gr.check();
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
