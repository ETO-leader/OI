#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class ssp{
private:
    struct edge{
        int v,fl,w,rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid;
    map<pair<int,int>,int> es;
    auto spfa(int s,int t){
        const auto n=(int)(gr.size());
        vector<int> dis(n,_inf),rest(n),inq(n);
        queue<int> q;q.emplace(s);
        rest[s]=_inf;dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            auto cnt=-1;
            for(auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w&&fl){
                dis[v]=dis[u]+w;rest[v]=min(rest[u],fl);
                fr[v]=u;eid[v]=cnt;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        return rest[t];
    }
    auto update(int s,int t,int&cur){
        const auto fl=spfa(s,t);
        if(!fl) return false;
        for(;t!=s;t=fr[t]){
            const auto u=fr[t];
            gr[u][eid[t]].fl-=fl;
            gr[t][gr[u][eid[t]].rev].fl+=fl;
            cur+=gr[u][eid[t]].w*fl;
        }
        return true;
    }
public:
    auto link(int u,int v,int fl,int w){
        gr[u].emplace_back(v,fl,w,(int)(gr[v].size()));
        gr[v].emplace_back(u,0,-w,(int)(gr[u].size()-1));
    }
    auto flowpath(int s,int t,int&ans){
        update(s,t,ans);
        return fr[t];
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> p(n);
    for(auto&i:p) cin>>i;
    vector<vector<int>> w(n,vector<int>(m));
    for(auto&x:w) for(auto&i:x) cin>>i;
    const auto v=accumulate(p.begin(),p.end(),0);
    ssp gr(n+m*(v+m)*2+7);
    const auto s=n+m*(v+m)*2,t=n+m*(v+m)*2+1;
    cir(i,0,n) gr.link(s,i,p[i],0);
    cir(u,0,m) gr.link(u+n+m*(v+m),u+n,1,0),gr.link(u+n,t,_inf,0);
    cir(i,0,n) cir(u,0,m) gr.link(i,u+n+m*(v+m),1,w[i][u]);
    auto ans=0;
    vector<int> cnt(m);
    cir(c,0,v){
        const auto id=gr.flowpath(s,t,ans)-n;
        ++cnt[id];
        gr.link(id+n+m*(v+m)+m*cnt[id],id+n+m*cnt[id],1,0);
        gr.link(id+n+m*cnt[id],id+n+m*(cnt[id]-1),_inf,0);
        cir(i,0,n) gr.link(i,id+(cnt[id])*m+n+(v+m)*m,1,w[i][id]*(cnt[id]+1));
    }
    cout<<ans<<'\n';
    return 0;
}
