#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class dinic{
private:
    struct edge{
        int v,rev;lint fl;
        edge(auto _v,auto _rv,auto _f):v(_v),rev(_rv),fl(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,lint rst){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl]=gr[u][i];
            if((!fl)||(dist[u]!=dist[v]+1)) continue;
            const auto uf=dfs(v,vx,min(rst,fl));
            res+=uf;fl-=uf;
            gr[v][rev].fl+=uf;
            if(!(rst-=uf)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint f){
        gr[u].emplace_back(v,(int)(gr[v].size()),f);
        gr[v].emplace_back(u,(int)(gr[u].size())-1,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_infl);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<vector<int>> ban(n,vector<int>(m));
    cir(i,0,k){
        int x,y;cin>>x>>y;--x;--y;
        ban[x][y]=true;
    }
    dinic gr(n*m+7);
    const auto s=n*m,t=n*m+1;
    cir(i,0,n) cir(j,0,m){
        ((i&1)^(j&1))?gr.link(s,i*m+j,1):gr.link(i*m+j,t,1);
    }
    cir(i,0,n) cir(j,0,m) if((i&1)^(j&1)){
        if(ban[i][j]) continue;
        if(i-1>-1&&(!ban[i-1][j])) gr.link(i*m+j,(i-1)*m+j,1);
        if(j-1>-1&&(!ban[i][j-1])) gr.link(i*m+j,i*m+j-1,1);
        if(i+1<n&&(!ban[i+1][j])) gr.link(i*m+j,(i+1)*m+j,1);
        if(j+1<m&&(!ban[i][j+1])) gr.link(i*m+j,i*m+j+1,1);
    }
    cout<<gr.flow(s,t)*2<<'\n';
    return 0;
}
