#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    struct edge{
        int v;lint w;
        edge(int _v,lint _w):v(_v),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<vector<edge>> ng;
    auto spfa(int ux){
        vector dis(gr.size(),_infl);
        vector<int> inq(gr.size());
        queue<int> q;q.push(ux);dis[ux]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto&[v,w]:gr[u]) if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v);
                inq[v]=true;
            }
        }
        return dis;
    }
    auto dijkstra(const auto s){
        vector dis(gr.size(),_infl);
        vector<int> vis(gr.size());
        dis[s]=0;
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<pair<lint,int>>> q;
        q.emplace(0,s);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wx]:ng[u]) if(w+wx<dis[v]){
                dis[v]=w+wx;q.emplace(w+wx,v);
            }
        }
        return dis;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto johnson(){
        const auto n=(int)(gr.size())-1;
        cir(v,0,n) link(0,v,0);
        const auto dis=spfa(0);
        cir(i,1,n+1) for(auto&[v,w]:gr[i]) ng[i].emplace_back(v,w-dis[v]+dis[i]);
        vector f(n+1,vector<lint>());
        cir(i,1,n+1) f[i]=dijkstra(i);
        cir(i,1,n+1) cir(j,1,n+1) (f[i][j]-=dis[i])+=dis[j];
        return f;
    }
    graph(int _n):gr(_n),ng(_n){}
};
auto sprint(auto expr,auto num,auto str){
    stringstream x;
    if(expr) x<<num;
    else x<<str;
    return x.str();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        gr.link(u,v,w);
    }
    const auto dis=gr.johnson();
    cir(i,1,n+1){
        cir(j,1,n+1) cout<<sprint((dis[i][j]<_infl/2),dis[i][j],"inf")<<' ';
        cout<<'\n';
    }
    return 0;
}
