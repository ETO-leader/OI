#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,stc,ins;
    int dcnt,scnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt;
        ins[u]=true;stc.push_back(u);
        for(auto&i:gr[u]){
            if(!dfn[i]) tarjan(i),low[u]=min(low[u],low[i]);
            else if(ins[i]) low[u]=min(low[u],dfn[i]);
        }
        if(dfn[u]==low[u]){
            auto ux=-1;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                scc[ux]=scnt;ins[ux]=false;
            }
            ++scnt;
        }
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
    }
    auto init(){
        cir(i,1,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto scccount(){return scnt;}
    auto sccid(int u){return scc[u];}
    graph(int n):gr(n+1),dfn(n+1),low(n+1),scc(n+1),ins(n+1),dcnt(0),scnt(0){}
};
class ek_algorithm{
private:
    struct edge{
        int v,rev;lint fl,w;
    };
    vector<vector<edge>> gr;
    int curcnt;
    auto spfa(int s,int t)->tuple<lint,vector<int>,vector<int>>{
        vector dis(gr.size(),_infl);
        vector<int> inq(gr.size()),fr(gr.size()),ex(gr.size()),visc(gr.size());
        deque q({s});dis[s]=0;
        const auto val=(curcnt<2e8?(int)(1e8l):-(int)(1e5l));
        while(!q.empty()){
            if((++curcnt)>2e8&&val>0){
                return spfa(s,t);
            }
            const auto u=q.front();q.pop_front();
            if((!q.empty())&&dis[q.front()]>dis[q.back()])
                swap(q.front(),q.back());
            inq[u]=false;
            for(auto c=-1;auto&[v,rev,fl,w]:gr[u]) if((++c)>-1&&fl){
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;fr[v]=u;ex[v]=c;
                ++visc[v];
                if(!inq[v]){
                    if(q.empty()||dis[q.front()]+val>dis[u]+w) q.push_front(v);
                    else q.push_back(v);
                }
                inq[v]=true;
            }
        }
        return tuple(dis[t],fr,ex);
    }
public:
    auto insert(int u,int v,lint fl,lint w){
        gr[u].push_back({v,(int)(gr[v].size()),fl,w});
        gr[v].push_back({u,(int)(gr[u].size())-1,0ll,-w});
    }
    auto flow(int s,int t){
        auto flw=0ll,cst=0ll;
        while(true){
            auto[disx,fr,ex]=spfa(s,t);
            if(disx>_infl-1) break;
            auto u=t;auto fl=_infl;
            while(u!=s){
                const auto eid=ex[u];
                u=fr[u];
                fl=min(fl,gr[u][eid].fl);
            }
            flw+=fl;cst+=disx*fl;
            u=t;
            while(u!=s){
                const auto eid=ex[u];
                u=fr[u];
                gr[u][eid].fl-=fl;
                gr[gr[u][eid].v][gr[u][eid].rev].fl+=fl;
            }
        }
        return pair(flw,cst);
    }
    ek_algorithm(int n):gr(n),curcnt(0){}
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
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;graph gr(n);
    vector<pair<int,int>> es(m);
    for(auto&[u,v]:es){
        cin>>u>>v;gr.insert(u,v);
    }
    gr.init();
    vector<lint> a(n+1);
    cir(i,1,n+1) cin>>a[i];
    const auto sn=gr.scccount();
    nodegen ngen;
    const auto s=ngen(),t=ngen();
    vector<lint> cnt(sn);
    cir(i,1,n+1) cnt[gr.sccid(i)]+=a[i];
    vector<int> inid(sn),outid(sn);
    cir(i,0,sn) inid[i]=ngen(),outid[i]=ngen();
    ek_algorithm fgr(ngen.count());
    cir(i,0,sn){
        fgr.insert(inid[i],outid[i],1,-cnt[i]);
        fgr.insert(inid[i],outid[i],_infl,0);
        fgr.insert(outid[i],t,_infl,0);
    }
    for(auto&[u,v]:es) if(gr.sccid(u)!=gr.sccid(v)){
        fgr.insert(outid[gr.sccid(u)],inid[gr.sccid(v)],_infl,0);
    }
    fgr.insert(s,inid[gr.sccid(1)],k,0);
    cout<<-fgr.flow(s,t).second<<'\n';
    return 0;
}
