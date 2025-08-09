#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    auto dijkstra(int s){
        const auto n=(int)(gr.size());
        vector<int> vis(n),dis(n,_inf);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
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
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
    }
    auto sp(const int s){return dijkstra(s);}
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n+1);
    vector<vector<pair<int,int>>> vx(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        gr.link(v,u,w);
        vx[u].emplace_back(v,w);
    }
    int s,t,k;cin>>s>>t>>k;
    const auto dis=gr.sp(t);
    vector<int> cnt(n+1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    q.emplace(dis[s],s);
    vector<int> ans(n+1);
    while((!q.empty())&&cnt[t]<k){
        auto[w,u]=q.top();q.pop();
        if((++cnt[u])>k) continue;
        w-=dis[u];
        ans[u]=w;
        for(auto&[v,vw]:vx[u]) if(cnt[v]<k){
            q.emplace(w+vw+dis[v],v);
        }
    }
    cout<<ans[t]<<'\n';
    return 0;
}
