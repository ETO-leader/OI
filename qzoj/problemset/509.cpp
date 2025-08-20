#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<long double> uf,ug;
    auto init(int u,int f=-1)->long double{
        uf[u]=0;
        for(auto&[v,w]:gr[u]) if(v!=f) uf[u]+=(init(v,u)+w)/(int)(gr[u].size()-(f>-1));
        return uf[u];
    }
    auto dfs(int u,int f=-1,int fw=-1)->void{
        ug[u]=uf[u];
        if(f!=-1){
            if(gr[u].size()>1) ug[u]*=(long double)(gr[u].size()-1)/gr[u].size();
            ug[u]+=((gr[f].size()>1?(ug[f]*(int)(gr[f].size())-(uf[u]+fw))/(int)(gr[f].size()-1):0)+fw)/(int)(gr[u].size());
        }
        for(auto&[v,w]:gr[u]) if(v!=f) dfs(v,u,w);
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(){
        init(0);
        dfs(0);
        return accumulate(ug.begin(),ug.end(),0.0l)/gr.size();
    }
    tree(int _n):gr(_n),uf(_n),ug(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;tree gr(n);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    cout<<fixed<<setprecision(15)<<gr.init()<<'\n';
    return 0;
}
