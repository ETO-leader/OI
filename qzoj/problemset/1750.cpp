#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class tree{
private:
    static constexpr auto ups=21;
    vector<vector<int>> gr;
    vector<vector<int>> up;
    vector<int> uin,uout,cnt;
    int ucnt;
    auto dfs(int u,int&c,int f=0)->void{
        uin[u]=++c;up[0][u]=f;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        for(auto&v:gr[u]) if(v!=f) dfs(v,c,u);
        uout[u]=c;
    }
    auto is_anciestor(int u,int v){
        return uin[u]-1<uin[v]&&uout[v]-1<uout[u];
    }
    auto lca(int u,int v){
        if(is_anciestor(u,v)) return u;
        if(is_anciestor(v,u)) return v;
        for(auto i=ups-1;~i;--i) if(!is_anciestor(up[i][u],v)) u=up[i][u];
        return up[0][u];
    }
    auto calc(int u,int f=-1)->pair<int,int64_t>{
        auto res=(int64_t)(0);
        auto uc=cnt[u];
        for(auto&i:gr[u]) if(i!=f){
            auto[c,d]=calc(i,u);
            uc+=c;res+=d;
        }
        if(~f){
            if(!uc) res+=ucnt;
            else if(uc==1) ++res;
        }
        return make_pair(uc,res);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){
        auto c=-1;dfs(0,c);
    }
    auto maketag(int u,int v){
        ++ucnt;
        ++cnt[u];++cnt[v];
        cnt[lca(u,v)]-=2;
    }
    auto calc(){
        return calc(0).second;
    }
    tree(int n):gr(n),uin(n),uout(n),up(ups,vector<int>(n)),cnt(n),ucnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.init();
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.maketag(u,v);
    }
    cout<<gr.calc()<<'\n';
    return 0;
}
