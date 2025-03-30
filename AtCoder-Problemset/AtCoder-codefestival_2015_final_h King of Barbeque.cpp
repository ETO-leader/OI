#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    auto dijkstra(int s,int t){
        const auto n=(int)(gr.size());
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        q.emplace(0,s);
        vector dis(n,_inf);
        vector vis(n,false);
        dis[s]=0;
        while(!q.empty()){
            const auto[w,u]=q.top();q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wx]:gr[u]) if(w+wx<dis[v]){
                dis[v]=w+wx;q.emplace(w+wx,v);
            }
        }
        return dis[t];
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
    }
    auto sp(int u,int v){
        return dijkstra(u,v);
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(m+7);
    cir(i,0,m+6) gr.link(i,i+1,2),gr.link(i+1,i,0);
    cir(i,0,n){
        int u,l;cin>>u>>l;
        gr.link(u,u+l,l);
    }
    cout<<(m+6)*2-gr.sp(0,m+6)<<'\n';
    return 0;
}
