#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> uin,uout;
    auto dfs(int u,int&c,int f=-1)->void{
        uin[u]=++c;
        for(auto&v:gr[u]) if(v!=f) dfs(v,c,u);
        uout[u]=c;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(auto r){
        auto c=-1;dfs(r,c);
    }
    auto is_anciestor(int u,int v){
        return uin[u]-1<uin[v]&&uout[v]-1<uout[u];
    }
    tree(int n):gr(n),uin(n),uout(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    auto urt=-1;
    map<int,int> id;
    vector<pair<int,int>> es(n);
    for(auto&[u,v]:es){
        cin>>u>>v;--u;--v;
        id.emplace(u,0);
        if(v>-1) id.emplace(v,0);
        if(v<0) urt=u;
    }
    auto c=-1;
    for(auto&[a,b]:id) b=++c;
    for(auto&[u,v]:es) if(v>-1){
        gr.link(id[u],id[v]);
    }
    gr.init(id[urt]);
    int q;cin>>q;
    cir(i,0,q){
        int u,v;cin>>u>>v;--u;--v;u=id[u];v=id[v];
        cout<<(gr.is_anciestor(v,u)?2:gr.is_anciestor(u,v)?1:0)<<"\n";
    }
    return 0;
}
