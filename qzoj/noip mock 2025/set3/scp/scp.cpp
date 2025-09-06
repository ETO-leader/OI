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
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,gr[v].size(),w);
        gr[v].emplace_back(u,gr[u].size()-1,0);
    }
    auto flow(int s,int t){
        auto res=0;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;
        const auto ec=n+m+k*5+7;
        dinic gr(ec);
        const auto s=ec-2,t=ec-1;
        cir(i,0,n){
            int c;cin>>c;
            cir(j,0,c){
                int v;cin>>v;--v;
                gr.link(n+v,i,1);
            }
            gr.link(i,t,1);
        }
        vector<vector<int>> ps(k);
        vector<vector<vector<int>>> pt(k,vector<vector<int>>(3));
        cir(i,0,m){
            int fs,ft;cin>>fs>>ft;--fs;--ft;
            if(fs>-1){
                ps[fs].emplace_back(i);
                pt[fs][ft].emplace_back(i);
            }else{
                gr.link(s,n+i,1);
            }
        }
        cir(i,0,k){
            auto cnt=0;
            cir(x,0,3) cnt+=pt[i][x].empty();
            if(ps[i].size()<3||cnt>1) return cout<<"VK"<<'\n',void();
            if(ps[i].size()>3){
                gr.link(s,n+m+i,(int)(ps[i].size())-4+(!(!cnt)));
                cir(x,0,3){
                    if(!pt[i][x].empty()) gr.link(n+m+i,n+m+(x+1)*k+i,(int)(pt[i][x].size())-1);
                    for(auto&p:pt[i][x]) gr.link(n+m+(x+1)*k+i,n+p,1);
                }
                if(!cnt){
                    gr.link(s,n+m+k*4+i,1);
                    cir(x,0,3) gr.link(n+m+k*4+i,n+m+(x+1)*k+i,1);
                }
            }
        }
        cout<<gr.flow(s,t)<<'\n';
    }();
    return 0;
}