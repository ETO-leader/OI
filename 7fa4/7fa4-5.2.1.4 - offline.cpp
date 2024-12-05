#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace __gnu_pbds{
    template<typename _Ty,class comp>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
        tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
class tree{
private:
    vector<vector<int>> gr;
    vector<vector<pair<int,int>>> q;
    vector<int> col,siz,ans;
    auto init(int u,int f=-1)->int{
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
        siz[u]=1;
        for(auto&i:gr[u]) siz[u]+=init(i,u);
        return siz[u];
    }
    auto dfs(int u,rbt<int,greater_equal<int>>&cur,map<int,int>&cnt){
        if(gr[u].empty()){
            cur.insert(1);cnt[col[u]]=1;
            for(auto&[k,id]:q[u]) ans[id]=cur.order_of_key(k-1);
            return;
        }
        sort(gr[u].begin(),gr[u].end(),[this](int a,int b){
            return siz[a]>siz[b];
        });
        dfs(gr[u][0],cur,cnt);
        cur.erase(cur.lower_bound(cnt[col[u]]));
        cur.insert(++cnt[col[u]]);
        for(auto&i:gr[u]) if(i!=gr[u][0]){
            rbt<int,greater_equal<int>> rbv;
            map<int,int> cntv;
            dfs(i,rbv,cntv);
            for(auto&[c,x]:cntv){
                cur.erase(cur.lower_bound(cnt[c]));
                cur.insert(cnt[c]+=x);
            }
        }
        for(auto&[k,id]:q[u]) ans[id]=cur.order_of_key(k-1);
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto initcol(auto c){col=c;}
    auto insquery(int u,int k,int id){
        q[u].emplace_back(k,id);
    }
    auto check(){
        init(0);
        rbt<int,greater_equal<int>> rb;
        map<int,int> cnt;
        dfs(0,rb,cnt);
        return ans;
    }
    tree(int _n,int _q):gr(_n),siz(_n),q(_n),ans(_q){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    return 0;
}
