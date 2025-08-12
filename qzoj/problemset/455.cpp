#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class ssp{
private:
    struct edge{
        int v;lint fl,w;int rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid;
    vector<lint> h;
    auto dijkstra(int s,int t){
        const auto n=(int)(gr.size());
        vector<lint> dis(n,_infl),rest(n),vis(n);
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<>> q;
        q.emplace(0,s);
        rest[s]=_infl;dis[s]=0;
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
        cir(i,0,n) h[i]=min(h[i]+dis[i],_infl);
        return rest[t];
    }
    auto update(int s,int t,lint&flw,lint&cur){
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
    auto link(int u,int v,lint fl,lint w){
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto fl=0ll,ans=0ll;
        while(update(s,t,fl,ans));
        return make_pair(fl,ans);
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m,n;cin>>m>>n;ssp gr(n+m*n*2+7);
    const auto s=n+m*n*2,t=n+m*n*2+1;
    cir(i,0,n) gr.link(s,i,1,0);
    cir(i,0,m) gr.link(i+n+n*m,t,_infl,0);
    cir(i,0,n) cir(j,0,m){
        lint w;cin>>w;
        cir(c,0,n) gr.link(i,c*m+j+n,1,w*(c+1));
    }
    cir(i,0,m) cir(c,0,n) gr.link(c*m+i+n,c*m+i+n*m+n,1,0);
    cir(i,0,m) cir(c,1,n) gr.link(c*m+i+n*m+n,(c-1)*m+i+n*m+n,_infl,0);
    cout<<fixed<<setprecision(2)<<(double)(gr.flow(s,t).second)/n<<'\n';
    return 0;
}
