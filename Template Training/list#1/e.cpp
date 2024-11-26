#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
class graph{
private:
    vector<vector<int>> to;
    vector<vector<pair<int,lf>>> in;
    vector<int> inc;
    vector<lf> p;
    auto bfs(int ux){
        queue<int> q;q.push(ux);p[ux]=1;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&[v,w]:in[u]) p[u]+=(p[v]/to[v].size());
            for(auto&i:to[u]) if(!(--inc[i])) q.push(i);
        }
    }
public:
    auto link(int u,int v,lf w){
        to[u].push_back(v);++inc[v];
        in[v].emplace_back(u,w);
    }
    auto check(int u,int v){
        bfs(u);
        auto res=0.0l;
        cir(i,0,(int)(to.size())) for(auto&[fr,w]:in[i]) res+=p[fr]/(to[fr].size())*w;
        return res;
    }
    graph(int _n):to(_n),in(_n),inc(_n),p(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n);
    cir(i,0,m){
        int u,v;lf w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    cout<<fixed<<setprecision(2)<<gr.check(0,n-1)<<'\n';
    return 0;
}
