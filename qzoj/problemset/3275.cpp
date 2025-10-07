#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
namespace __gnu_pbds{
    template<typename _Ty,class comp=less<_Ty>>
    using rbt=tree<_Ty,null_type,comp,rb_tree_tag,tree_order_statistics_node_update>;
}
using __gnu_pbds::rbt;
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> siz,ban;
    auto dfssz(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) siz[u]+=dfssz(v,u);
        return siz[u];
    }
    auto dfsrt(int u,const int tsiz,int f=-1)->int{
        auto umx=-1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])){
            const auto vw=dfsrt(v,tsiz,u);
            if(vw>-1) return vw;
            umx=max(umx,siz[v]);
        }
        if(max(umx,tsiz-siz[u])<tsiz/2+1) return u;
        return -1;
    }
    auto dfsht(int u,int c,vector<int>&cnt,int f=-1)->void{
        cnt.emplace_back(c);
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) dfsht(v,c+w,cnt,u);
    }
    auto divide(int u,const int k){
        const auto tsiz=dfssz(u);
        if(tsiz==1) return 0ll;
        const auto rt=dfsrt(u,tsiz);
        ban[rt]=true;
        rbt<int,less_equal<int>> cnt;
        cnt.insert(0);
        auto res=0ll;
        for(auto&[v,w]:gr[rt]) if(!ban[v]){
            vector<int> vtr;
            dfsht(v,w,vtr);
            for(auto&x:vtr) res+=cnt.order_of_key(k-x+1);
            for(auto&x:vtr) cnt.insert(x);
        }
        for(auto&[v,w]:gr[rt]) if(!ban[v]) res+=divide(v,k);
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto count(const int k){
        return divide(0,k);
    }
    tree(int _n):gr(_n),siz(_n),ban(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    int k;cin>>k;
    cout<<gr.count(k)<<'\n';
    return 0;
}
