#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class failed_signal{};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> uf,vis,dep;
    auto dfs(int u,int udep,int f=-1)->void{
        uf[u]=f;dep[u]=++udep;
        if(udep>(int)(gr.size())+7) throw failed_signal();
        for(auto&i:gr[u]) if(i!=f) dfs(i,udep,u);
    }
    auto lca(int u,int v){
        while(u>-1) vis[u]=true,u=uf[u];
        while(!vis[v]) v=uf[v];
        ranges::fill(vis,false);
        return v;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){dfs(0,0);}
    auto dis(int u,int v){
        return dep[u]+dep[v]-dep[lca(u,v)]*2;
    }
    auto getedges(){
        vector<pair<int,int>> ans;
        cir(i,0,(int)(gr.size())) for(auto&x:gr[i]) if(i<x) ans.emplace_back(i,x);
        return ans;
    }
    tree(int _n):gr(_n),uf(_n),vis(_n),dep(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector s(n,vector(n,vector<int>(n)));
        cir(u,0,n-1){
            cir(j,1,n-u){
                string us;cin>>us;
                const auto v=u+j;
                cir(k,0,n) s[u][v][k]=s[v][u][k]=(us[k]=='1');
            }
        }
        auto build=[&](auto __self,int u,int f,int&cnt,tree&tr)->void {
            if(cnt>n) return;
            cir(v,0,n) if(v!=u&&v!=f&&s[v][f][u]){
                tr.link(u,v);++cnt;
                __self(__self,v,u,cnt,tr);
            }
        };
        vector<pair<int,int>> ans;
        cir(v,1,n) [&]{
            tree utr(n);
            utr.link(0,v);
            auto ec=1;
            build(build,0,v,ec,utr);
            build(build,v,0,ec,utr);
            if(ec!=n-1) return;
            try{
                utr.init();
                vector dis(n,vector<int>(n));
                cir(i,0,n) cir(j,0,n) dis[i][j]=utr.dis(i,j);
                cir(u,0,n) cir(v,u+1,n) cir(k,0,n) if((s[u][v][k]&&dis[u][k]!=dis[v][k])||((!s[u][v][k])&&dis[u][k]==dis[v][k])) return;
                ans=utr.getedges();
            }catch(failed_signal){}
        }();
        cout<<(ans.empty()?"No":"Yes")<<'\n';
        for(auto&[u,v]:ans) cout<<u+1<<' '<<v+1<<'\n';
    }();
    return 0;
}
