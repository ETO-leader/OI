#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    vector<vector<pair<int,lint>>> gr;
    auto dijkstra(int s){
        const auto n=(int)(gr.size());
        vector<int> vis(n);
        vector dis(n,_infl);
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<>> q;
        dis[s]=0;q.emplace(0,s);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,vw]:gr[u]) if(dis[v]>w+vw){
                dis[v]=w+vw;
                q.emplace(w+vw,v);
            }
        }
        return dis;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto sp(const int s){return dijkstra(s);}
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;--k;
        graph gr(n);
        vector<vector<pair<int,lint>>> vx(n);
        cir(i,0,m){
            int u,v,l,r;cin>>u>>v>>l>>r;--u;--v;
            vx[u].emplace_back(v,l);
            vx[v].emplace_back(u,l);
            gr.link(u,v,r);
        }
        const auto dis=gr.sp(k);
        vector f(n,_infl);
        f[0]=-dis[0];
        priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<>> q;
        q.emplace(-dis[0],0);
        vector<int> vis(n);
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            if(w>dis[u]-1) continue;
            vis[u]=true;
            for(auto&[v,vw]:vx[u]) if(f[v]>max(w+vw,-dis[v])){
                f[v]=max(w+vw,-dis[v]);
                q.emplace(max(w+vw,-dis[v]),v);
            }
        }
        cout<<(vis[n-1]?"Yes":"No")<<'\n';
    }();
    return 0;
}
