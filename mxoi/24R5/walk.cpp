#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("walk.in");
ofstream fcout("walk.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class subneqm{
public:
    auto play(const int n){
        struct edge{int v,w;};
        vector<vector<edge>> gr(n);
        cir(i,0,n){
            int u,v;char c;fcin>>u>>v>>c;--u;--v;
            gr[u].push_back({v,(c=='('?1:-1)});
        }
        vector<int> vis(n);
        auto dfs=[&](auto __self,int u,int w)->bool {
            if(w<0) return false;
            if(vis[u]) return !w;
            vis[u]=true;
            auto res=false;
            for(auto&[v,wx]:gr[u]) res|=__self(__self,v,w+wx);
            return res;
        };
        cir(i,0,n){
            fill(vis.begin(),vis.end(),false);
            if(dfs(dfs,i,0)) return fcout<<"Yes\n",0;
        }
        fcout<<"No\n";
        return 0;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;fcin>>n>>m;
    if(n==m) exit(subneqm().play(n));
    fcout<<"Yes\n";
    return 0;
}
