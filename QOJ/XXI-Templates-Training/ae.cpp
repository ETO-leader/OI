#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class sssp{
private:
    struct edge{
        int v,rev;lint fl,w;
        edge(auto _v,auto _r,auto _f,auto _w):v(_v),rev(_r),fl(_f),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<lint> dis,inq,fr,fid;
    auto spfa(int s,int t){
        fill(dis.begin(),dis.end(),_infl);
        deque<int> q;q.emplace_back(s);
        dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop_front();
            inq[u]=false;
            for(auto id=-1;auto&[v,rev,fl,w]:gr[u]) if(++id;fl){
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;
                fr[v]=u;
                fid[v]=id;
                if(!inq[v]){
                    if(q.empty()||dis[v]<dis[q.front()]) q.emplace_front(v);
                    else q.emplace_back(v);
                }
                inq[v]=true;
            }
        }
        return dis[t];
    }
public:
    auto link(int u,int v,auto fl,auto w){
        gr[u].emplace_back(v,(int)(gr[v].size()),fl,w);
        gr[v].emplace_back(u,(int)(gr[u].size())-1,0,-w);
    }
    auto flow(int s,int t){
        auto res=0ll,rfl=0ll;
        while(spfa(s,t)<_infl){
            const auto w=dis[t];
            auto fl=_infl;
            for(auto u=t;u!=s;){
                const auto v=u;
                u=fr[u];
                fl=min(fl,gr[u][fid[v]].fl);
            }
            rfl+=fl;
            res+=fl*w;
            for(auto u=t;u!=s;){
                const auto v=u;
                u=fr[u];
                gr[u][fid[v]].fl-=fl;
                gr[v][gr[u][fid[v]].rev].fl+=fl;
            }
        }
        return pair(rfl,res);
    }
    sssp(int _n):gr(_n),dis(_n),inq(_n),fr(_n),fid(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    const auto s=0,t=n-1;
    sssp gr(n);
    cir(i,0,m){
        int u,v,fl,w;cin>>u>>v>>fl>>w;--u;--v;
        gr.link(u,v,fl,w);
    }
    const auto[fl,val]=gr.flow(s,t);
    cout<<fl<<' '<<val<<'\n';
    return 0;
}
