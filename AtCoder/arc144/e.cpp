#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
class dag{
private:
    vector<vector<int>> gr;
    vector<int> ok,vis;
    auto dfs(int u,int v){
        if(vis[u]) return ok[u];
        vis[u]=true;
        if(u==v) return ok[u]=true;
        for(auto&i:gr[u]) ok[u]|=dfs(i,v);
        return ok[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto init(){dfs(0,(int)(gr.size()-1));}
    auto is_ok(int u) const{return ok[u];}
    dag(int _n):gr(_n),ok(_n),vis(_n){}
};
class graph{
private:
    vector<vector<pair<int,lint>>> gr;
    vector<lint> dep;
    vector<int> vis;
    lint ans;
    auto dfs(int u)->void{
        vis[u]=true;
        for(auto&[v,w]:gr[u]){
            if(!vis[v]){
                dep[v]=dep[u]+w;
                dfs(v);
            }else{
                ans=gcd(ans,abs(dep[u]-dep[v]+w));
            }
        }
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,-w);
    }
    auto calc(){
        dfs(0);
        if(vis[(int)(gr.size())-1]) ans=gcd(ans,dep[(int)(gr.size())-1]);
        cir(u,1,(int)(gr.size())) if(!vis[u]) dfs(u);
        return (ans?ans:-1);
    }
    graph(int _n):gr(_n),dep(_n),vis(_n),ans(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<pair<int,int>> es(m);
    dag d(n);
    for(auto&[u,v]:es) cin>>u>>v,--u,--v,d.link(u,v);
    d.init();
    vector<lint> w(n);
    for(auto&x:w) cin>>x;
    if(!d.is_ok(0)){
        cout<<-1<<'\n';
    }else{
        graph gr(n*2);
        for(auto&[u,v]:es){
            if(d.is_ok(u)&&d.is_ok(v)) gr.link(u+n,v,0);
        }
        cir(u,0,n) if(d.is_ok(u)&&(~w[u])) gr.link(u,u+n,w[u]);
        cout<<gr.calc()<<'\n';
    }
    return 0;
}
