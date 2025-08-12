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
    int n;cin>>n;
    const auto s=n*n,t=n*n+1;
    graph gr(n*n+7);
    vector<vector<int>> acnt(n+1,vector<int>(n));
    vector<vector<int>> bcnt(n,vector<int>(n+1));
    cir(i,0,n+1) cir(j,0,n){
        int w;cin>>w;
        if(!i) gr.link(s,i*n+j,w);
        else if(i==n) gr.link((i-1)*n+j,t,w);
        else gr.link((i-1)*n+j,i*n+j,w);
    }
    cir(i,0,n) cir(j,0,n+1){
        int w;cin>>w;
        if(!j) gr.link(i*n+j,t,w);
        else if(j==n) gr.link(s,i*n+j-1,w);
        else gr.link(i*n+j,i*n+j-1,w);
    }
    cir(i,0,n+1) cir(j,0,n){
        int w;cin>>w;
        if(!i) gr.link(i*n+j,s,w);
        else if(i==n) gr.link(t,(i-1)*n+j,w);
        else gr.link(i*n+j,(i-1)*n+j,w);
    }
    cir(i,0,n) cir(j,0,n+1){
        int w;cin>>w;
        if(!j) gr.link(t,i*n+j,w);
        else if(j==n) gr.link(i*n+j-1,s,w);
        else gr.link(i*n+j-1,i*n+j,w);
    }
    cout<<gr.sp(s)[t]<<'\n';
    return 0;
}
