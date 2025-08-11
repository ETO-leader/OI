#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,rev,w,fv;
        edge(auto _v,auto _rev,auto _w,auto _f):v(_v),rev(_rev),w(_w),fv(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl,fv]=gr[u][i];
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
        gr[u].emplace_back(v,gr[v].size(),w,w);
        gr[v].emplace_back(u,gr[u].size()-1,0,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        unusual=false;
        fill(cur.begin(),cur.end(),0);
        fill(dist.begin(),dist.end(),0);
        fill(gap.begin(),gap.end(),0);
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    auto revoke(int u,int v){
        gr[u].pop_back();gr[v].pop_back();
    }
    auto val(const int s){return gr[s].back().w;}
    auto info(){
        vector<tuple<int,int,int>> es;
        cir(u,0,(int)(gr.size())) for(auto&[v,rev,fl,fv]:gr[u]) if(fv>fl){
            es.emplace_back(u,v,fv-fl);
        }
        return es;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n+7),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;dinic gr(n*2+7);
    const int s=n*2,t=n*2+1,rs=n*2+2,rt=n*2+3;
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u+n,v,1);
    }
    cir(i,0,n) gr.link(rs,i+n,1),gr.link(i,rt,1),gr.link(s,i,1),gr.link(i+n,t,1);
    gr.link(t,s,_inf);
    gr.flow(rs,rt);
    auto ans=gr.val(s);
    gr.revoke(t,s);
    ans-=gr.flow(t,s);
    const auto info=gr.info();
    vector<deque<int>> vx(n*2+7);
    for(auto&[u,v,w]:info) if((u>n-1&&v<n)||((u==s)+(v==t)==1)) vx[u].emplace_back(v);
    cir(i,0,n) vx[i].emplace_back(i+n);
    cir(i,0,ans){
        auto u=s;
        vector<int> ux{s},px;
        while(u!=t){
            u=vx[u].front();
            ux.emplace_back(u);
            if(u<n) px.emplace_back(u);
        }
        cir(i,0,(int)(ux.size())-1){
            vx[ux[i]].pop_front();
        }
        for(auto&i:px) cout<<i+1<<' ';
        cout<<'\n';
    }
    cout<<ans<<'\n';
    return 0;
}
