#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class graph{
private:
    struct edge{int v;lint w;};
    struct node{
        int v;lint w;
        auto operator<(const node&u) const{
            return w>u.w;
        }
    };
    vector<vector<edge>> gr;
    auto dijkstra(vector<int> s){
        vector<lint> d(gr.size(),_infl);
        vector<bool> vis(gr.size());
        priority_queue<node> q;
        for(auto&u:s) d[u]=0,q.emplace(u,0);
        while(!q.empty()){
            auto[u,w]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wx]:gr[u]) if(!vis[v]){
                if(w+wx>d[v]-1) continue;
                d[v]=w+wx;q.emplace(v,w+wx);
            }
        }
        return d;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto check(auto s){
        return dijkstra(s);
    }
    graph(int _n):gr(_n){}
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
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;graph gr(n);
        cir(i,0,m){
            int u,v,w;cin>>u>>v>>w;--u;--v;
            gr.link(u,v,w);
        }
        vector<int> qn(k);
        for(auto&i:qn) cin>>i,--i;
        auto ans=numeric_limits<lint>::max();
        cir(c,0,20){
            vector<int> q,a;
            cir(i,0,k) (i&(1<<c)?q:a).push_back(qn[i]);
            const auto dis=gr.check(q);
            const auto rdis=gr.check(a);
            for(auto&i:a) ans=min(ans,dis[i]);
            for(auto&i:q) ans=min(ans,rdis[i]);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
