#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("graph.in");
ofstream ouf("graph.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
static constexpr auto _inf=(int)(1e9+7);
class ssp{
private:
    struct edge{
        int v,fl,w,rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid,h;
    auto spfa(int s){
        const auto n=(int)(gr.size());
        h=vector<int>(n,_inf);
        vector<int> inq(n);
        queue<int> q;
        q.emplace(s);
        h[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto&[v,fl,w,rev]:gr[u]) if(h[v]>h[u]+w&&fl){
                h[v]=h[u]+w;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
    }
    auto dijkstra(int s,int t){
        const auto n=(int)(gr.size());
        vector<int> dis(n,_inf),rest(n),vis(n);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
        q.emplace(0,s);
        rest[s]=_inf;dis[s]=0;
        while(!q.empty()){
            const auto[uw,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            auto cnt=-1;
            for(auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w+h[u]-h[v]&&fl){
                dis[v]=dis[u]+w+h[u]-h[v];
                rest[v]=min(rest[u],fl);
                fr[v]=u;eid[v]=cnt;
                q.emplace(dis[v],v);
            }
        }
        cir(i,0,n) h[i]=min(h[i]+dis[i],_inf);
        return rest[t];
    }
    auto update(int s,int t,int&flw,int&cur){
        const auto fl=dijkstra(s,t);
        if(!fl) return false;
        flw+=fl;
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
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto fl=0,ans=0;
        spfa(s);
        while(update(s,t,fl,ans));
        return ans;
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,k,a,b,c;inf>>n>>k>>a>>b>>c;
    vector<int> w(n);
    for(auto&i:w) inf>>i;
    const auto s=n*2,ns=n*2+1,t=n*2+2;
    ssp gr(n*2+7);
    gr.link(s,ns,k,0);
    cir(i,0,n) gr.link(ns,i,k,0);
    cir(i,0,n){
        gr.link(i,i+n,1,-1);
        gr.link(i,i+n,k-1,0);
        gr.link(i+n,t,k,0);
    }
    map<int,int> valp,modp;
    for(auto i=n-1;~i;--i){
        if(valp.count(w[i]-a)) gr.link(i+n,valp[w[i]-a],k,0);
        if(valp.count(w[i]+a)) gr.link(i+n,valp[w[i]+a],k,0);
        if(valp.count(w[i]*b)) gr.link(i+n,valp[w[i]*b],k,0);
        if(b&&(!(w[i]%b))&&valp.count(w[i]/b)) gr.link(i+n,valp[w[i]/b],k,0);
        if(modp.count(w[i]%c)) gr.link(i+n,modp[w[i]%c],k,0);
        valp[w[i]]=i;
        modp[w[i]%c]=i;
    }
    ouf<<-gr.flow(s,t)<<'\n';
    return 0;
}
