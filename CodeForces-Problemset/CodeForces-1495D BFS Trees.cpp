#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=998244353;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dis;
    auto bfs(int ux){
        queue<int> q;q.push(ux);
        dis[ux]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&i:gr[u]){
                if(dis[i]>-1) continue;
                dis[i]=dis[u]+1;q.push(i);
            }
        }
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto dist(int u){return dis[u];}
    auto init(const int s){bfs(s);}
    graph(int _n):gr(_n),dis(_n,-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector grs(n,graph(n));
    vector<vector<int>> gr(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].push_back(v);gr[v].push_back(u);
        cir(i,0,n) grs[i].insert(u,v);
    }
    cir(i,0,n) grs[i].init(i);
    auto path=[&](int v,int u){
        vector<int> pth;
        for(;u!=v;u=[&](){
            for(auto&x:gr[u]) if(grs[v].dist(x)+1==grs[v].dist(u)) return x;
            return v;
        }()) pth.push_back(u);
        pth.push_back(v);
        return ranges::reverse(pth),pth;
    };
    vector<int> ol(n);
    cir(u,0,n) cir(v,0,n){
        const auto pth=path(v,u);
        ranges::fill(ol,false);
        for(auto&i:pth) ol[i]=true;
        auto ans=1ll;
        cir(i,0,n) if(!ol[i]){
            auto cnt=0;
            for(auto&x:gr[i]) cnt+=(grs[u].dist(x)==grs[u].dist(i)-1&&grs[v].dist(x)==grs[v].dist(i)-1);
            (ans*=cnt)%=MOD;
        }
        print("{}{}",ans," \n"[v==n-1]);
    }
    return 0;
}
