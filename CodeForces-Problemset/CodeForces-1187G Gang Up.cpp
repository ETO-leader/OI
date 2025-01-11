#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int _inf=1e9+7;
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
    // auto emplace_query(int u,int v){
    //     es.emplace(pair(v,u),-1);
    // }
    // auto qedges(){
    //     const auto n=(int)(gr.size());
    //     cir(u,0,n){
    //         for(auto&[v,fl,w,rev]:gr[u]) if(es.contains(pair(v,u))) es[pair(v,u)]=fl; 
    //     }
    //     return es;
    // }
    ssp(int _n):gr(_n),fr(_n),eid(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto getnode(){return cnt++;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k,c,d;cin>>n>>m>>k>>c>>d;
    vector<int> psx(k);
    for(auto&i:psx) cin>>i;
    vector<vector<int>> grx(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        grx[u].push_back(v);grx[v].push_back(u);
    }
    ssp gr(n*207+7);
    nodegen ngen;
    const auto s=ngen.getnode(),t=ngen.getnode();
    vector<int> lnds(n),nds(n);
    for(auto&i:nds) i=ngen.getnode();
    for(auto&i:psx) gr.link(s,nds[i-1],1,0);
    cir(cx,0,199){
        swap(nds,lnds);
        for(auto&i:nds) i=ngen.getnode();
        cir(i,1,n+1){
            gr.link(lnds[i-1],nds[i-1],_inf,c*(i!=1));
            for(auto&x:grx[i]){
                cir(p,1,k+1) gr.link(lnds[i-1],nds[x-1],1,d*p*p-d*(p-1)*(p-1)+c);
            }
        }
    }
    gr.link(nds[0],t,_inf,0);
    println("{}",gr.flow(s,t));
    return 0;
}
