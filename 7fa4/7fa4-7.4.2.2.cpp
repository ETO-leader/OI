#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename _Ty,class comp=greater<_Ty>>
using heap=__gnu_pbds::priority_queue<_Ty,
    comp,__gnu_pbds::pairing_heap_tag>;
static constexpr auto _inf=(lint)(1e12+7);
struct edge{int v;lint w;};
vector<vector<edge>> gr;
vector<heap<lint>> aq,aw;
vector<lint> dep,a,b;
auto dfs(int u,int f=0)->lint{
    auto res=0ll;
    cir(i,a[u],b[u]) aq[u].push(dep[u]-_inf),res+=_inf;
    cir(i,b[u],a[u]) aw[u].push(dep[u]);
    for(auto&[v,w]:gr[u]) if(v!=f){
        dep[v]=dep[u]+w;
        res+=dfs(v,u);
        aq[u].join(aq[v]);
        aw[u].join(aw[v]);
    }
    while((!aq[u].empty())&&(!aw[u].empty())&&
        aq[u].top()+aw[u].top()<dep[u]*2){
        const auto fwq=aq[u].top();
        const auto fww=aw[u].top();
        aq[u].pop();aw[u].pop();
        res+=(fwq+fww)-dep[u]*2;
        aq[u].push(dep[u]*2-fww);
        aw[u].push(dep[u]*2-fwq);
    }
    return res;
}
auto init(int n){
    gr.resize(n+1);aq.resize(n+1);
    aw.resize(n+1);dep.resize(n+1);
    a.resize(n+1);b.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;init(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        gr[u].push_back({v,w});
        gr[v].push_back({u,w});
    }
    cir(i,1,n+1) cin>>a[i]>>b[i];
    cout<<dfs(1)<<'\n';
    return 0;
}
