#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,rev,w;
        edge(auto _v,auto _rev,auto _w):v(_v),rev(_rev),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl]=gr[u][i];
            if(dist[u]!=dist[v]+1||(!fl)) continue;
            const auto vw=dfs(v,vx,min(rst,fl));
            fl-=vw;gr[v][rev].w+=vw;res+=vw;
            if(!(rst-=vw)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,int w,bool tri=false){
        gr[u].emplace_back(v,gr[v].size(),w);
        gr[v].emplace_back(u,gr[u].size()-1,w*tri);
    }
    auto flow(int s,int t){
        auto res=0;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
static constexpr auto squ(auto x){return x*x;}
int main() {
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,d;cin>>n>>m>>d;
    d*=d;
    vector<vector<int>> mp(n,vector<int>(m));
    for(auto&x:mp) for(auto&i:x){
        char c;
        cin>>c;
        i=c-'0';
    }
    vector<vector<int>> inc(n,vector<int>(m)),outc(n,vector<int>(m));
    const auto s=0,t=[&]{
        int cnt=0;
        cir(i,0,n) cir(j,0,m) inc[i][j]=++cnt;
        cir(i,0,n) cir(j,0,m) outc[i][j]=++cnt;
        return cnt+1;
    }();
    auto nodein=[&](int x,int y){return inc[x][y];};
    auto nodeout=[&](int x,int y){return outc[x][y];};
    dinic gr(t+1);
    cir(i,0,n) cir(j,0,m) if(mp[i][j]){
        gr.link(nodein(i,j),nodeout(i,j),mp[i][j]);
        cir(ix,0,n) cir(jx,0,m) if(ix!= i||jx!=j){
            if(squ(ix-i)+squ(jx-j)<d+1){
                gr.link(nodeout(i,j),nodein(ix,jx),_inf);
            }
        }
        if (squ(i+1)<d+1||squ(j+1)<d+1||squ(n-i)<d+1||squ(m-j)<d+1){
            gr.link(nodeout(i,j),t,_inf);
        }
    }
    auto cnt=0;
    cir(i,0,n) cir(j,0,m){
        char c;cin>>c;
        if(c=='L'){
            gr.link(s,nodein(i,j),1);
            ++cnt;
        }
    }
    cout<<cnt-gr.flow(s,t)<<'\n';
    return 0;
}
