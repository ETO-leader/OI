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
    int n,m;cin>>n>>m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<vector<int>> xid(n,vector<int>(m,-1)),yid(n,vector<int>(m,-1));
    vector<int> xp(n*m),yp(n*m);
    auto cx=-1,cy=-1;
    cir(i,0,n){
        cir(j,0,m) if(a[i][j]!=2){
            ++cx;
            xp[cx]=i;
            auto p=j;
            while(p+1<m&&a[i][p+1]!=2) ++p;
            cir(x,j,p+1) xid[i][x]=cx;
            j=p+1;
        }
    }
    cir(j,0,m){
        cir(i,0,n) if(a[i][j]!=2){
            ++cy;
            yp[cy]=j;
            auto p=i;
            while(p+1<n&&a[p+1][j]!=2) ++p;
            cir(x,i,p+1) yid[x][j]=cy;
            i=p+1;
        }
    }
    dinic gr(cx+cy+4);
    const auto s=cx+cy+2,t=cx+cy+3;
    cir(i,0,n) cir(j,0,m) if(!a[i][j]){
        gr.link(xid[i][j],yid[i][j]+cx+1,1);
    }
    cir(i,0,cx+1) gr.link(s,i,1);
    cir(i,0,cy+1) gr.link(i+cx+1,t,1);
    cout<<gr.flow(s,t)<<'\n';
    const auto es=gr.info();
    for(auto[u,v]:es) if(u<cx+1&&v>cx){
        cout<<xp[u]+1<<' '<<yp[v-cx-1]+1<<'\n';
    }
    return 0;
}
