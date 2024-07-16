#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<int>> gr;
    auto bfs(int s){
        queue<int> q;q.push(s);
        vector<int> dis(gr.size(),_inf),vis(gr.size());
        vis[s]=true;dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&i:gr[u]) if(!vis[i]){
                dis[i]=dis[u]+1;vis[i]=true;
                q.push(i);
            }
        }
        return dis;
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto dist(int u){
        return bfs(u);
    }
    graph(int n):gr(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,l;cin>>n>>k>>l;graph gr(n+1);
    vector<int> x(k),a(l),st(n+1);
    for(auto&i:x) cin>>i,st[i]=true;
    for(auto&i:a) cin>>i;
    cir(i,0,n) st[i]^=st[i+1];
    cir(i,0,n) for(auto&x:a) if(i+x<n+1) gr.insert(i,i+x);
    vector<int> posx;
    cir(i,0,n+1) if(st[i]) posx.push_back(i);
    const auto m=posx.size();
    vector<vector<int>> dis(m);
    for(auto c=-1;auto&i:posx) dis[++c]=gr.dist(i);
    vector f(1<<m,_inf);f[0]=0;
    cir(s,0,(1<<m)) cir(u,0,m) cir(v,u+1,m){
        if((s&(1<<u))||(s&(1<<v))) continue;
        f[s|(1<<u)|(1<<v)]=min(
            f[s|(1<<u)|(1<<v)],
            f[s]+dis[u][posx[v]]
        );
    }
    cout<<(f[(1<<m)-1]<_inf?f[(1<<m)-1]:-1)<<'\n';
    return 0;
}
