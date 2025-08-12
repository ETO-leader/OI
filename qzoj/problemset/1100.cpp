#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class dinic{
private:
    struct edge{
        int v,rev;lint w,fv;
        edge(auto _v,auto _rev,auto _w,auto _f):v(_v),rev(_rev),w(_w),fv(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,lint rst){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl,fv]=gr[u][i];
            if(dist[u]!=dist[v]+1||(!fl)) continue;
            const auto vw=dfs(v,vx,min<lint>(rst,fl));
            fl-=vw;gr[v][rev].w+=vw;res+=vw;
            if(!(rst-=vw)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,gr[v].size(),w,w);
        gr[v].emplace_back(u,gr[u].size()-1,0,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        unusual=false;
        fill(cur.begin(),cur.end(),0);
        fill(dist.begin(),dist.end(),0);
        fill(gap.begin(),gap.end(),0);
        while(!unusual) res+=dfs(s,t,_infl);
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
class minflow{
private:
    dinic gr;
    const int rs,rt;
public:
    auto link(int u,int v,lint l,lint r){
        gr.link(u,v,r-l);
        gr.link(rs,v,l);
        gr.link(u,rt,l);
    }
    auto flow(int s,int t){
        gr.link(t,s,_infl);
        gr.flow(rs,rt);
        auto ans=gr.val(s);
        gr.revoke(s,t);
        return ans-gr.flow(t,s);
    }
    minflow(int _n):gr(_n+2),rs(_n),rt(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    const auto s=n,t=n+1;
    minflow gr(n+7);
    cir(i,0,n){
        int c;cin>>c;
        gr.link(s,i,0,_infl);
        gr.link(i,t,0,_infl);
        cir(x,0,c){
            int v;cin>>v;--v;
            gr.link(i,v,1,_infl);
        }
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}

