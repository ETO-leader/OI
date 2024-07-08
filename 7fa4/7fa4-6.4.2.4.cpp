#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int _inf=1e9+7;
class dinic{
private:
    struct edge{
        int v,rev;bool notrev;
        lint formw,w;
    };
    vector<vector<edge>> G;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint rst,int t){
        if(u==t) return rst;
        lint res=0;
        for(auto&i=cur[u];i<(int)(G[u].size());++i){
            auto&e=G[u][i];
            if(e.w&&dist[u]-1==dist[e.v]){
                auto rx=dfs(e.v,min(rst,e.w),t);
                e.w-=rx;
                G[e.v][e.rev].w+=rx;
                res+=rx;
                if(!(rst-=rx)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        gap[++dist[u]]++;
        cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        G[u].push_back({v,(int)(
            G[v].size()),true,w,w});
        G[v].push_back({u,(int)(
            G[u].size())-1,false,0,0});
    }
    auto check(int s,int t){
        unusual=false;
        while(!unusual) dfs(s,_inf,t);
        for(auto&i:G[s]) if(i.w) return false;
        return true;
    }
    auto get_result(){
        multiset<pair<int,int>> res;
        cir(u,0,(int)(G.size())){
            for(auto&[v,rev,nrv,fw,w]:G[u]){
                if(nrv&&(fw-w)){
                    res.insert({u,v});
                }
            }
        }
        return res;
    }
    dinic(int n):G(n),cur(n),dist(n),gap(n){}
};
struct edge_t{int u,v;lint l,r;};
class euler_tour{
private:
    dinic gr;int s,t;
    vector<deque<int>> frg;
    void dfs(int u,stack<int>&ans){
        if(frg[u].empty())
            return ans.push(u),void();
        while(!frg[u].empty()){
            auto v=frg[u].front();
            frg[u].pop_front();
            dfs(v,ans);
        }
        ans.push(u);
    }
public:
    void insert(int u,int v,int l,int r){
        gr.insert(s,v,l);gr.insert(u,t,l);
        gr.insert(u,v,r-l);
        if(l) frg[u].push_back(v);
    }
    auto tour(){
        assert(gr.check(s,t));
        auto mp=gr.get_result();
        for(auto&[u,v]:mp) if(u!=s&&v!=t){
            frg[u].push_back(v);
        }
        stack<int> ans;
        return dfs([&](){
            cir(i,s+1,t) if(!frg[i].empty())
                return i;
            throw "Not Found\n";
        }(),ans),[&](){
            stringstream str;
            while(!ans.empty())
                str<<ans.top()<<' ',ans.pop();
            return str.str();
        }();
    }
    euler_tour(int n):gr(n+7),
        frg(n+2),s(0),t(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;euler_tour gr(n);
    cir(i,0,m){
        int u,v,k;cin>>u>>v>>k;
        gr.insert(u,v,k,1);
    }
    cout<<gr.tour()<<'\n';
    return 0;
}
