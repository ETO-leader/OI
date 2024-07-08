#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e15+7;
class dinic{
private:
    struct edge{
        int v;lint w;int rev;bool rl;
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint cst,const int vx){
        if(u==vx) return cst;
        auto res=(lint)(0);
        for(auto&c=cur[u];c<(int)(gr[u].size());++c){
            auto&[v,w,rev,rl]=gr[u][c];
            if((!w)||(dist[u]-1!=dist[v])) continue;
            const auto wx=dfs(v,min(cst,w),vx);
            w-=wx;gr[v][rev].w+=wx;res+=wx;
            if(!(cst-=wx)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
    unordered_set<int> frs;
    auto full(edge e){
        if(e.rl) return !e.w;
        return (!e.w)||(!gr[e.v][e.rev].w);
    }
    auto dfs(int u){
        if(frs.count(u)) return;
        frs.insert(u);
        for(auto&[v,w,rev,rl]:gr[u]){
            if(full({v,w,rev,rl})) continue;
            dfs(v);
        }
    }
public:
    auto insert(int u,int v,lint w){
        gr[u].push_back({v,w,(int)(
            gr[v].size()),true});
        gr[v].push_back({u,w,(int)(
            gr[u].size())-1,false});
    }
    auto flow(int s,int t){
        unusual=false;auto res=(lint)(0);
        while(!unusual) res+=dfs(s,_inf,t);
        dfs(s);
        return res;
    }
    auto check(int u,int v){
        return frs.count(u)&&(!frs.count(v));
    }
    dinic(int _n):gr(_n),gap(_n),dist(_n),cur(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto getnode(){return cnt++;}
    nodegen():cnt(0){}
};
vector<int> bld,ans,rid,rxid;
vector<vector<lint>> a;
auto divide(int l,int r,vector<int> llst,vector<int> rlst,int al,int ar){
    if(l==r) return [&](){
        cir(i,al,ar+1) ans[rid[i]]=bld[l];
    }();
    if(ar<al) return;
    const auto mid=(l+r)/2;
    const auto midw=bld[mid];
    dinic gr((ar-al+1)+7);
    nodegen ngen;
    const auto s=ngen.getnode(),t=ngen.getnode();
    auto getcost=[&](int id,int p){
        lint res=0;
        cir(i,0,(int)(bld.size()))
            res+=abs(p-bld[i])*a[id][rxid[i]];
        cir(i,0,(int)(bld.size()))
            res+=abs(p-bld[i])*a[id][rxid[i]];
        for(auto&i:llst) res+=abs(p-l)*a[id][i];
        for(auto&i:rlst) res+=abs(r-p)*a[id][i];
        return res;
    };
    vector<int> ids(ar-al+1);
    for(auto&i:ids) i=ngen.getnode();
    cir(i,al,ar+1){
        gr.insert(s,ids[i-al],getcost(rid[i],midw));
        gr.insert(ids[i-al],t,getcost(rid[i],midw+1));
    }
    cir(i,al,ar+1) cir(j,al,ar+1){
        gr.insert(ids[i-al],ids[j-al],a[rid[i]][rid[j]]);
    }
    gr.flow(s,t);
    vector<int> tps(ar-al+1);
    cir(i,0,ar-al+1) tps[i]=gr.check(ids[i],t);
    sort(rid.begin()+al,rid.begin()+ar+1,
        [&](int u,int v){return tps[u]<tps[v];});
    auto cpl=llst,cpr=rlst;
    cir(i,al,ar+1) if(!tps[i-al]) cpl.push_back(rid[i]);
    cir(i,al,ar+1) if(tps[i-al]) cpr.push_back(rid[i]);
    divide(l,mid,llst,cpr,al,al+(int)(cpl.size())-1);
    divide(mid+1,r,cpl,rlst,al+cpl.size(),ar);
}
auto init(int n,int m){
    bld.resize(n);ans.resize(n+m);
    rid.resize(n+m);rxid.resize(n);
    iota(rid.begin(),rid.end(),0);
    iota(rxid.begin(),rxid.end(),0);
    a.assign(n+m,vector<lint>(n+m));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n,m);
    for(auto&i:bld) cin>>i;
    cir(i,0,n) ans[i]=bld[i];
    sort(rxid.begin(),rxid.end(),
        [&](int u,int v){return bld[u]<bld[v];});
    sort(bld.begin(),bld.end());
    for(auto&i:a) for(auto&j:i) cin>>j;
    divide(0,n-1,vector<int>(),vector<int>(),n,n+m-1);
    lint costf=0;
    cir(i,0,n+m) cir(j,0,n+m)
        costf+=abs(ans[i]-ans[j])*a[i][j];
    cout<<costf/2<<'\n';
    return 0;
}
