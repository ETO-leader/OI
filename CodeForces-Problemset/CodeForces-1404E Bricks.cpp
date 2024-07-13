#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    using lint=int;
    struct edge{int v,rev;lint w;};
    vector<vector<edge>> G;
    vector<int> cur,dist;
    auto bfs(int ux,int vx){
        queue<int> q;q.push(ux);
        fill(dist.begin(),dist.end(),_inf);
        dist[ux]=0;
        while(!q.empty()){
            auto u=q.front();q.pop();
            for(auto&[v,rev,w]:G[u]) if(G[v][rev].w){
                if(dist[v]>dist[u]+1){
                    dist[v]=dist[u]+1;q.push(v);
                }
            }
        }
        fill(cur.begin(),cur.end(),0);
        return dist[vx]<_inf;
    }
    auto dfs(int u,lint rst,const int t){
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
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        G[u].push_back({v,(int)(G[v].size()),w});
        G[v].push_back({u,(int)(G[u].size())-1,0});
    }
    auto flow(int s,int t){
        lint res=0;
        while(bfs(t,s)) res+=dfs(s,_inf,t);
        return res;
    }
    dinic(int n):G(n),cur(n),dist(n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<string> mp(n);
    for(auto&i:mp) cin>>i;
    nodegen ngen;
    const auto s=ngen(),t=ngen();
    map<tuple<int,int,int,int>,int> eid;
    auto ncnt=0;
    cir(i,0,n) cir(j,0,m) if(mp[i][j]=='#'){
        ++ncnt;
        if(i&&mp[i-1][j]=='#') eid[{i-1,j,i,j}]=ngen();
        if(j&&mp[i][j-1]=='#') eid[{i,j-1,i,j}]=ngen();
    }
    dinic gr(ngen.count());
    cir(i,0,n) cir(j,0,m) if(mp[i][j]=='#'){
        if(i&&mp[i-1][j]=='#') gr.insert(s,eid[{i-1,j,i,j}],1);
        if(j&&mp[i][j-1]=='#') gr.insert(eid[{i,j-1,i,j}],t,1);
    }
    cir(i,0,n) cir(j,0,m){
        if(eid.count({i-1,j,i,j})&&eid.count({i,j-1,i,j})){
            gr.insert(eid[{i-1,j,i,j}],eid[{i,j-1,i,j}],1);
        }
        if(eid.count({i-1,j,i,j})&&eid.count({i,j,i,j+1})){
            gr.insert(eid[{i-1,j,i,j}],eid[{i,j,i,j+1}],1);
        }
        if(eid.count({i,j,i+1,j})&&eid.count({i,j-1,i,j})){
            gr.insert(eid[{i,j,i+1,j}],eid[{i,j-1,i,j}],1);
        }
        if(eid.count({i,j,i+1,j})&&eid.count({i,j,i,j+1})){
            gr.insert(eid[{i,j,i+1,j}],eid[{i,j,i,j+1}],1);
        }
    }
    const auto maxsiz=ngen.count()-2-gr.flow(s,t);
    cout<<ncnt-maxsiz<<'\n';
    return 0;
}
