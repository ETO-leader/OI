#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{int v,w,rev;};
    vector<vector<edge>> gr;
    vector<int> dist,cur,gap;
    bool unusual;
    auto dfs(int u,const int vx,int fl){
        if(u==vx) return fl;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev]=gr[u][i];
            if((!w)||(dist[u]!=dist[v]+1)) continue;
            const auto fx=dfs(v,vx,min(fl,w));
            w-=fx;gr[v][rev].w+=fx;
            res+=fx;
            if(!(fl-=fx)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w,(int)(gr[v].size()));
        gr[v].emplace_back(u,0,(int)(gr[u].size())-1);
    }
    auto flow(const int s,const int t){
        auto res=0;unusual=false;
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),gap(_n+7),dist(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    const auto mxa=*ranges::max_element(a);
    vector<set<int>> pos(mxa+1);
    cir(i,0,n) pos[a[i]].insert(i);
    dinic gr(n+2);
    const auto s=n,t=n+1;
    auto sum=0;
    cir(i,0,n){
        cir(w,1,mxa+1) if(!(a[i]%w)){
            const auto lb=pos[w].lower_bound(i);
            if(lb!=pos[w].begin()) gr.link(i,*prev(lb),_inf);
        }
        if(b[i]>0) gr.link(s,i,b[i]),sum+=b[i];
        else gr.link(i,t,-b[i]);
    }
    println("{}",sum-gr.flow(s,t));
    return 0;
}
