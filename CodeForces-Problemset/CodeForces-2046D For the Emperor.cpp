#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto B=(lint)(1e12l);
static constexpr auto _infl=(lint)(1e18l);
class graph{
private:
    struct edge{
        int v,rev;lint fl,w;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<lint> dis;
    vector<int> fr,inq,fid;
    auto spfa(int ux){
        queue<int> q;q.emplace(ux);
        ranges::fill(dis,_infl);
        dis[ux]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto c=-1;auto&[v,rev,fl,w]:gr[u]) if(++c;fl){
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;fr[v]=u;fid[v]=c;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
    }
public:
    auto link(int u,int v,lint fl,lint w){
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto resw=0ll,resfl=0ll;
        for(;[&]{
            spfa(s);
            return dis[t]<_infl;
        }();){
            auto v=t;
            auto flx=_infl,cost=0ll;
            while(v!=s){
                const auto eid=fid[v];
                v=fr[v];flx=min(flx,gr[v][eid].fl);
                cost+=gr[v][eid].w;
            }
            v=t;
            while(v!=s){
                const auto eid=fid[v];
                const auto las=v;
                v=fr[v];gr[v][eid].fl-=flx;
                gr[las][gr[v][eid].rev].fl+=flx;
            }
            resw+=cost*flx;resfl+=flx;
        }
        return pair(resw,resfl);
    }
    graph(int _n):gr(_n),dis(_n),fr(_n),fid(_n),inq(_n){}
};
class scc{
private:
    vector<vector<int>> gr,sccs;
    vector<int> dfn,low,ins,stc;
    auto tarjan(int u,int&cdfn,int&sccid)->void{
        dfn[u]=low[u]=++cdfn;
        ins[u]=true;stc.emplace_back(u);
        for(auto&i:gr[u]) if(!dfn[i]){
            tarjan(i,cdfn,sccid);
            low[u]=min(low[u],low[i]);
        }else if(ins[i]){
            low[u]=min(low[u],dfn[i]);
        }
        if(dfn[u]==low[u]){
            auto v=-1;++sccid;
            while(v!=u){
                v=stc.back();stc.pop_back();
                ins[v]=false;
                sccs[sccid].emplace_back(v);
            }
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto init(){
        int cdfn=0,cscc=-1;
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i,cdfn,cscc);
        return cscc+1;
    }
    auto infoscc(auto u){return sccs[u];}
    scc(int _n):gr(_n),sccs(_n),dfn(_n),low(_n),ins(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;scc gr(n);
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<pair<int,int>> es;
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
            es.emplace_back(u,v);
        }
        const auto x=gr.init();
        nodegen ngen;
        vector<int> in(x),out(x),vx(x),ax(x);
        const auto s=ngen(),t=ngen();
        for(auto&i:in) i=ngen();
        for(auto&i:out) i=ngen();
        for(auto&i:vx) i=ngen();
        unordered_map<int,int> fscc;
        cir(i,0,x) for(auto&u:gr.infoscc(i)) ax[i]+=a[u],fscc[u]=i;
        graph ek(ngen.count());
        cir(i,0,x) ek.link(s,vx[i],ax[i],0);
        cir(i,0,x) ek.link(vx[i],out[i],_infl,0),ek.link(vx[i],in[i],1,1);
        cir(i,0,x) ek.link(in[i],out[i],1,-B),ek.link(in[i],out[i],_infl,0);
        cir(i,0,x) ek.link(out[i],t,_infl,0);
        for(auto&[u,v]:es) if(fscc[u]!=fscc[v]) ek.link(out[fscc[u]],in[fscc[v]],_infl,0);
        const auto w=ek.flow(s,t).first;
        println("{}",(w>-B*(x-1)-1)?-1:w+B*x);
    }();
    return 0;
}
