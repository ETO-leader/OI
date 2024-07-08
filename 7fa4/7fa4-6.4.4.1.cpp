#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{int v,fl,fw,rev,nrv;};
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int fl){
        if(u==vx) return fl;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,fli,fw,rev,nrv]=gr[u][i];
            if(!fli) continue;
            if(dist[u]-1!=dist[v]) continue;
            const auto flx=dfs(v,vx,min(fl,fli));
            res+=flx;fli-=flx;gr[v][rev].fl+=flx;
            if(!(fl-=flx)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,int w){
        gr[u].push_back({v,w,w,(int)(gr[v].size()),true});
        gr[v].push_back({u,0,0,(int)(gr[u].size())-1,false});
    }
    auto check(int s,int t){
        unusual=false;
        while(!unusual) dfs(s,t,_inf);
        for(auto&es:gr[s]) if(es.fl) return false;
        return true;
    }
    auto getflow(){
        map<pair<int,int>,int> res;
        cir(u,0,(int)(gr.size())) for(auto&[v,fl,fw,rev,nrv]:gr[u]){
            if(!nrv) continue;
            res.insert({pair(u,v),fw-fl});
        }
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n){}
};
struct edge_t{int u,v;bool dir;};
struct edge_q{int u,v,x,y;};
auto check(vector<edge_t>&es,const int n){
    vector<int> d(n+1);
    for(auto&[u,v,dir]:es){
        ++d[u];--d[v];
    }
    for(auto&i:d) if(i&1) throw exception();
    dinic gr(n+7);
    const auto s=0,t=n+1;
    for(auto&[u,v,dir]:es){
        if(!dir) gr.insert(u,v,1);
    }
    cir(i,1,n+1){
        if(d[i]>0) gr.insert(s,i,d[i]/2);
        if(d[i]<0) gr.insert(i,t,-d[i]/2);
    }
    if(!gr.check(s,t)) throw exception();
    auto rst=gr.getflow();
    vector<vector<int>> rg(n+1);
    for(auto&[u,v,dir]:es){
        if((!u)||(!v)) continue;
        if(u==t||v==t) continue;
        if(dir){
            rg[u].push_back(v);
            continue;
        }
        if(rst[{u,v}]) --rst[{u,v}],swap(u,v);
        rg[u].push_back(v);
    }
    return rg;
}
auto dfs(int u,vector<vector<int>>&gr,vector<int>&stc)->void{
    while(!(gr[u].empty())){
        const auto v=gr[u].back();
        gr[u].pop_back();
        dfs(v,gr,stc);
        stc.push_back(u);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<edge_q> es(m);
    auto mx=0;
    multimap<pair<int,int>,int> esid;
    for(auto c=0;auto&[u,v,x,y]:es){
        cin>>u>>v>>x>>y;
        mx=max({mx,x,y});
        esid.insert({pair(u,v),++c});
        if(y<x) swap(u,v),swap(x,y);
    }
    auto ansgr=vector<vector<int>>();
    auto checkf=[&](int mid){
        vector<edge_t> eq;
        for(auto&[u,v,x,y]:es){
            if(x>mid) return false;
            if(y>mid) eq.push_back({u,v,true});
            else eq.push_back({u,v,false});
        }
        try{
            const auto cpr=check(eq,n);
            ansgr=cpr;
        }catch(exception&){
            return false;
        }
        return true;
    };
    auto l=0,r=mx,ans=-1;
    while(l-1<r){
        const auto mid=(l+r)/2;
        checkf(mid)?((r=mid-1),(ans=mid)):(l=mid+1);
    }
    if(ans==-1) exit((cout<<"NIE\n",0));
    cout<<ans<<'\n';
    vector<int> ansv;
    dfs(1,ansgr,ansv);
    reverse(ansv.begin(),ansv.end());
    auto fnd=[&](int u,int v){
        for(auto&[px,id]:esid){
            if(px.first==u&&px.second==v) return tuple(px,id,false);
            if(px.first==v&&px.second==u) return tuple(px,id,true);
        }
        abort();
    };
    cout<<(get<2>(fnd(ansv[0],ansv[1]))?'r':'p')<<' ';
    ansv.push_back(ansv.front());
    cir(i,1,(int)(ansv.size())){
        auto[px,id,tp]=fnd(ansv[i-1],ansv[i]);
        cout<<id<<' ';
    }
    cout<<'\n';
    return 0;
}
