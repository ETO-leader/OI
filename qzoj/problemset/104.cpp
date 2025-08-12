#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l); 
static constexpr auto delta=(lint)(1e10l);
class ssp{
private:
    struct edge{
        int v;lint fl,w;int rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid;
    map<pair<int,int>,int> es;
    auto spfa(int s,int t){
        const auto n=(int)(gr.size());
        vector<lint> dis(n,_infl),rest(n),inq(n);
        deque<int> q;q.emplace_back(s);
        rest[s]=_infl;dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop_front();
            inq[u]=false;
            auto cnt=-1;
            for(auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w&&fl){
                dis[v]=dis[u]+w;rest[v]=min(rest[u],fl);
                fr[v]=u;eid[v]=cnt;
                if(!inq[v]) q.emplace_back(v);
                if(dis[q.front()]>dis[q.back()]) swap(q.front(),q.back());
                inq[v]=true;
            }
        }
        return rest[t];
    }
    auto update(int s,int t,lint&flw,lint&cur){
        const auto fl=spfa(s,t);
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
        return ans;
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int d,n1,n2,c1,c2,tc;cin>>d;
    vector<int> x(d);
    for(auto&i:x) cin>>i;
    cin>>tc>>n1>>c1>>n2>>c2;
    const auto s=d*2,t=d*2+1;
    ssp gr(d*2+7);
    gr.link(s,0,_infl,tc);
    cir(i,0,d){
        gr.link(i,t,x[i],0);
        gr.link(s,i+d,x[i],0);
        if(i+1<d) gr.link(i,i+1,_infl,0);
        if(i+n1<d) gr.link(i+d,i+n1,x[i],c1);
        if(i+n2<d) gr.link(i+d,i+n2,x[i],c2);
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}
