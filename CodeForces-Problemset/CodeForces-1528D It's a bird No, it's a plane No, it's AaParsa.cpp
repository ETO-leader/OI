#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class graph{
private:
    vector<vector<pair<int,lint>>> gr;
    auto dijkstra(const auto ux){
        const auto n=(int)(gr.size());
        vector f(n,_infl),ans(n,_infl);
        for(auto&[v,w]:gr[ux]) f[v]=min(f[v],w);
        cir(i,0,n){
            const auto u=ranges::min_element(f)-f.begin();
            const auto w=(ans[u]=f[u]);
            f[u]=_infl;
            for(auto&[v,ew]:gr[u]){
                const auto realv=(v+w)%n;
                if(ans[realv]<_infl) continue;
                f[realv]=min(f[realv],w+ew);
            }
            if(ans[(u+1)%n]==_infl) f[(u+1)%n]=min(f[(u+1)%n],w+1);
        }
        ans[ux]=0;
        return ans;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto check(int s){
        return dijkstra(s);
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<tuple<int,int,lint>> es(m);
    for(auto&[u,v,w]:es) cin>>u>>v>>w;
    graph gr(n);
    for(auto&[u,v,w]:es) gr.link(u,v,w);
    cir(s,0,n){
        const auto dis=gr.check(s);
        for(auto&i:dis) print("{} ",i);
        println("");
    }
    return 0;
}
