#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class dinic{
private:
    struct edge{
        int v,rev;lint w,fw;
    };
    vector<vector<edge>> gr;
    vector<int> dist,gap,cur;
    bool unusual;
    auto dfs(int u,const int vx,lint wx){
        if(u==vx) return wx;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,w,fw]=gr[u][i];
            if((!w)||(dist[u]-1!=dist[v])) continue;
            const auto wi=dfs(v,vx,min(wx,w));
            res+=wi;w-=wi;gr[v][rev].w+=wi;
            if(!(wx-=wi)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].push_back({v,
            (int)(gr[v].size()),w,w});
        gr[v].push_back({u,
            (int)(gr[u].size())-1,0,0});
        return pair((int)(gr[u].size()),(int)(gr[v].size()));
    }
    auto flow(int s,int t){
        auto res=0ll;
        for(unusual=false;!unusual;res+=dfs(s,t,_infl));
        return res;
    }
    dinic(int n):gr(n),gap(n),dist(n),cur(n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        dinic gr(n+67);
        nodegen ngen;
        const auto s=ngen(),t=ngen();
        vector<int> id(64);
        for(auto&i:id) i=ngen(),gr.link(s,i,1);
        cir(i,0,n){
            const auto idi=ngen();
            cir(x,0,64) if((a[i]>>x)&1) gr.link(id[x],idi,_infl);
            gr.link(idi,t,1);
        }
        println("{}",n-gr.flow(s,t));
    }();
    return 0;
}
