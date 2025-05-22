#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("player.in");
ofstream ouf("player.ans");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<int>> gr;
    vector<int> fr,vis;
    int cnt;
    void dfs(int u,int f=-1){
        fr[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    }
    void jump(int u){
        while(u>-1&&(!vis[u])) vis[u]=true,++cnt,u=fr[u];
    }
public:
    void link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    void init(int _r){dfs(_r);vis[_r]=true;}
    void flush(){
        fill(vis.begin(),vis.end(),false);
        cnt=0;
    }
    int emplace(int u){
        jump(u);
        return cnt;
    }
    tree(int _n):gr(_n),fr(_n),vis(_n),cnt(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int id,n,k;inf>>id>>n>>k;
    vector<int> p(n);
    for(auto&i:p) inf>>i,--i;
    tree gr(n);
    cir(i,0,n-1){
        int u,v;inf>>u>>v;--u;--v;
        gr.link(u,v);
    }
    vector<vector<int>> siz(n,vector<int>(n));
    cir(i,0,n){
        gr.flush();
        gr.init(p[i]);
        cir(j,0,n) siz[i][(i+j)%n]=gr.emplace(p[(i+j)%n]);
    }
    auto check=[&](int s){
        vector<int> f(n);
        cir(i,0,n) f[i]=siz[s][(s+i)%n];
        cir(r,0,k-1){
            const auto g=f;
            fill(f.begin(),f.end(),-_inf);
            auto las=0;
            cir(i,r+1,n){
                cir(p,las,i){
                    const auto nw=g[p]+siz[(s+p+1)%n][(s+i)%n];
                    if(nw>f[i]) f[i]=nw,las=p;
                }
            }
        }
        return f[n-1];
    };
    auto ans=0;
    cir(i,0,n) ans=max(ans,check(i));
    ouf<<ans<<'\n';
    return 0;
}
