#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class ssp{
private:
    struct edge{
        int v,fl,w,rev;
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
            for(auto cnt=-1;auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w&&fl){
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
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto ans=0;
        while(update(s,t,ans));
        return ans;
    }
    auto emplace_query(int u,int v){
        es.emplace(pair(u,v),0);
    }
    auto qedges(){
        const auto n=(int)(gr.size());
        cir(u,0,n){
            for(auto&[v,fl,w,rev]:gr[u]) if(es.contains(pair(v,u))) es[pair(v,u)]+=fl; 
        }
        return es;
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n){}
};
class graph{
private:
    ssp flow;const int s,t,n;
    map<pair<int,int>,int> basicf;
    int basic;
public:
    auto emplace(int u,int v,int l,int r,int w){
        flow.link(u,v,r-l,w);
        flow.link(s,v,l,0);
        flow.link(u,t,l,0);
        flow.emplace_query(u,v);
        basic+=l*w;
        basicf[pair(u,v)]+=l;
    }
    auto flows(){
        vector<vector<int>> res(n);
        const auto cost=flow.flow(s,t);
        const auto es=flow.qedges();
        for(auto&[info,cnt]:es){
            const auto[u,v]=info;
            cir(i,0,cnt+basicf[pair(u,v)]) res[u].emplace_back(v);
        }
        return pair(cost,res);
    }
    graph(int _n,int _s,int _t):flow(_n+2),s(_n),t(_n+1),n(_n),basic(0){
        flow.link(_s,_t,_inf,0);
        flow.link(_t,_s,_inf,0);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int d,n;cin>>d>>n;
    auto nodecnt=-1;
    auto node=[&]{return ++nodecnt;};
    const auto s=node(),t=node();
    vector<int> in(1<<d),out(1<<d);
    for(auto&x:in) x=node();
    for(auto&x:out) x=node();
    vector<int> rtype(nodecnt+1,-1);
    cir(i,0,(1<<d)) rtype[in[i]]=i;
    graph gr(nodecnt+1,s,t);
    unordered_set<int> q;
    cir(i,0,n){
        string s;cin>>s;
        auto num=0;
        ranges::reverse(s);
        for(auto&i:s) (num<<=1)|=(i-'0');
        q.emplace(num);
    }
    cir(i,0,(1<<d)){
        if(q.count(i)) gr.emplace(in[i],out[i],1,_inf,0);
        else gr.emplace(in[i],out[i],0,_inf,0);
        cir(p,0,d) if(!(i&(1<<p))) gr.emplace(out[i],in[i^(1<<p)],0,_inf,1);
    }
    gr.emplace(s,in[0],0,1,0);
    gr.emplace(s,in[0],0,_inf,1);
    cir(i,0,(1<<d)) gr.emplace(out[i],t,0,_inf,0);
    auto[cost,ansg]=gr.flows();
    println("{}",cost);
    vector<int> cur;
    auto getpath=[&](auto __self,int u)->void {
        if(u==t) return;
        if(rtype[u]>-1) cur.emplace_back(rtype[u]);
        if(ansg[u].empty()) return;
        const auto v=ansg[u].back();
        ansg[u].pop_back();
        __self(__self,v);
    };
    vector<int> type((1<<d)+7);
    cir(i,0,d) type[1<<i]=i;
    for(auto ndr=false;[&]{cur.clear();getpath(getpath,in[0]);return cur.size()>1;}();ndr=true){
        if(ndr) print("R ");
        for(auto i=(int)(cur.size())-1;i;--i) cur[i]^=cur[i-1];
        cur.erase(cur.begin());
        for(auto&u:cur) print("{} ",type[u]);
    }
    println("");
    return 0;
}
