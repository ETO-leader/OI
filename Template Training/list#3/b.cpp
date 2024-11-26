#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    vector<vector<tuple<int,int,int>>> gr;
    vector<int> cur,gap,dist;
    bool unusual;
    auto dfs(int u,const int vx,int wx){
        if(u==vx) return wx;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,fl,rev]=gr[u][i];
            if(dist[u]!=dist[v]+1||(!fl)) continue;
            const auto vw=dfs(v,vx,min(wx,fl));
            fl-=vw;get<1>(gr[v][rev])+=vw;res+=vw;
            if(!(wx-=vw)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w,gr[v].size());
        gr[v].emplace_back(u,0,gr[v].size()-1);
    }
    auto flow(int s,int t){
        auto res=0;unusual=false;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),gap(_n+7),dist(_n),unusual(false){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count() const{return cnt;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector<string> a(n);
    for(auto&x:a) cin>>x;
    nodegen ngen;
    const auto s=ngen(),t=ngen();
    vector xn(n,vector<int>(m)),yn(n,vector<int>(m));
    set<int> in,out;
    cir(i,0,n) cir(j,0,m) if((!xn[i][j])&&a[i][j]=='*'){
        const auto id=ngen();
        while(j<m&&a[i][j]=='*') xn[i][j]=id,++j; 
        in.insert(id);
    }
    cir(j,0,m) cir(i,0,n) if((!yn[i][j])&&a[i][j]=='*'){
        const auto id=ngen();
        while(i<n&&a[i][j]=='*') yn[i][j]=id,++i;
        out.insert(id);
    }
    dinic gr(ngen.count());
    for(auto&x:in) gr.link(s,x,1);
    for(auto&x:out) gr.link(x,t,1);
    cir(i,0,n) cir(j,0,m) if(a[i][j]=='*') gr.link(xn[i][j],yn[i][j],1);
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}

