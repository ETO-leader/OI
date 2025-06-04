#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("respect.in");
ofstream ouf("respect.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
auto&inf=cin;
auto&ouf=cout;
#endif
using lint=long long;
class bf_tree{
private:
    vector<vector<pair<int,lint>>> gr;
    vector<lint> dep,depth;
    vector<vector<int>> up;
    static constexpr int ups=21;
    void dfs(int u,lint pre=0,int fr=0){
        depth[u]=pre;dep[u]=dep[fr]+1;
        up[0][u]=fr;
        cir(i,1,ups) up[i][u]=up[i-1][up[i-1][u]];
        for(auto&p:gr[u]) if(p.first!=fr){
            dfs(p.first,pre+p.second,u);
        }
    }
    int lca(int u,int v){
        if(dep[u]<dep[v]) swap(u,v);
        cir(i,0,ups) if((dep[u]-dep[v])&(1<<i)) u=up[i][u];
        if(u==v) return u;
        for(int i=ups-1;i>=0;--i) if(up[i][u]!=up[i][v]){
            u=up[i][u];v=up[i][v];
        }
        return up[0][u];
    }
public:
    void link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    void init(){dfs(0);}
    lint cost(int u,int v){
        return depth[lca(u,v)];
    }
    bf_tree(int _n):gr(_n),dep(_n),depth(_n),up(ups,vector<int>(_n)){}
};
class cnt_tree{
private:
    vector<vector<pair<int,lint>>> gr;
    static constexpr int ups=21;
    int dfs(int u,lint&ans,lint depth,int f=-1){
        int ucnt=1;
        for(auto&p:gr[u]){
            int v=p.first;lint w=p.second;
            if(v!=f){
                const int vcnt=dfs(v,ans,depth+w,u);
                ans+=(lint)(ucnt)*vcnt*depth;
                ucnt+=vcnt;
            }
        }
        return ucnt;
    }
public:
    void link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    lint check(){
        lint ans=0ll;
        dfs(0,ans,0);
        return ans;
    }
    cnt_tree(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    if(n<1007){
        bf_tree tr_u(n),tr_v(n),tr_w(n);
        cir(i,0,n-1){
            int u,v;lint w;inf>>u>>v>>w;--u;--v;
            tr_u.link(u,v,w);
        }
        cir(i,0,n-1){
            int u,v;lint w;inf>>u>>v>>w;--u;--v;
            tr_v.link(u,v,w);
        }
        cir(i,0,n-1){
            int u,v;lint w;inf>>u>>v>>w;--u;--v;
            tr_w.link(u,v,w);
        }
        tr_u.init();
        tr_v.init();
        tr_w.init();
        lint ans=0ll;
        cir(i,0,n) cir(j,i+1,n){
            lint a=tr_u.cost(i,j),b=tr_v.cost(i,j),c=tr_w.cost(i,j);
            ans+=max(max(a,b),c);
        }
        ouf<<ans<<'\n';
    }else{
        cnt_tree gr(n);
        cir(i,0,n-1){
            int u,v;lint w;inf>>u>>v>>w;--u;--v;
            gr.link(u,v,w);
        }
        ouf<<gr.check()<<'\n';
    }
    return 0;
}
