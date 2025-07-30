#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,rev,w,fwd;
        edge(auto _v,auto _rev,auto _w,auto _f):v(_v),rev(_rev),w(_w),fwd(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl,fwd]=gr[u][i];
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
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,gr[v].size(),w,true);
        gr[v].emplace_back(u,gr[u].size()-1,0,false);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    auto info(){
        vector<pair<int,int>> es;
        cir(u,0,(int)(gr.size())) for(auto&[v,rev,fl,fwd]:gr[u]) if(fwd&&(!fl)){
            es.emplace_back(u,v);
        }
        return es;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<string> a(n);
    for(auto&s:a) cin>>s;
    auto sp=[&](int x,int y){
        vector<vector<int>> dist(n,vector<int>(n,_inf));
        dist[x][y]=0;
        queue<pair<int,int>> q;
        q.emplace(x,y);
        while(!q.empty()){
            const auto[u,v]=q.front();q.pop();
            static auto vx=array<int,4>{-1,1,0,0};
            static auto vy=array<int,4>{0,0,-1,1};
            cir(i,0,4){
                const auto nx=u+vx[i],ny=v+vy[i];
                if(nx<0||ny<0||nx>n-1||ny>n-1) continue;
                if(a[nx][ny]!='*'&&dist[nx][ny]>dist[u][v]+1){
                    dist[nx][ny]=dist[u][v]+1;
                    q.emplace(nx,ny);
                }
            }
        }
        return dist;
    };
    int r;cin>>r;
    vector<pair<int,int>> cell(r);
    for(auto&[x,y]:cell) cin>>x>>y,--x,--y;
    vector<int> s(r);
    for(auto&i:s) cin>>i;
    vector<vector<int>> nok(n,vector<int>(n));
    int x;cin>>x;
    cir(c,0,x){
        int t,x,y,v;cin>>t>>x>>y>>v;--x;--y;--v;
        const auto dis=sp(x,y);
        cir(i,0,r) if(dis[cell[i].first][cell[i].second]>s[v]*t) nok[v][i]=true;
    }
    dinic gr(r*2+7);
    const auto sg=r*2,tg=r*2+1;
    cir(i,0,r) gr.link(sg,i,1);
    cir(i,0,r) gr.link(i+r,tg,1);
    cir(i,0,r) cir(j,0,r) if(!nok[i][j]) gr.link(i,j+r,1);
    gr.flow(sg,tg);
    const auto info=gr.info();
    for(auto&[u,v]:info) if(u<r&&v>r-1){
        cout<<u+1<<' '<<cell[v-r].first+1<<' '<<cell[v-r].second+1<<'\n';
    }
    return 0;
}
