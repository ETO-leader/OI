#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e12+7;
class dinic{
private:
    struct edge{
        int v,rev;bool notrev;
        lint formw,w;
    };
    vector<vector<edge>> G;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint rst,int t){
        if(u==t) return rst;
        lint res=0;
        for(auto&i=cur[u];i<(int)(G[u].size());++i){
            auto&e=G[u][i];
            if(e.w&&dist[u]-1==dist[e.v]){
                auto rx=dfs(e.v,min(rst,e.w),t);
                e.w-=rx;
                G[e.v][e.rev].w+=rx;
                res+=rx;
                if(!(rst-=rx)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        gap[++dist[u]]++;
        cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,lint w,lint fw=0){
        G[u].push_back({v,(int)(
            G[v].size()),true,fw,w});
        G[v].push_back({u,(int)(
            G[u].size())-1,false,fw,0});
    }
    auto get(int s,int t){
        unusual=false;lint res=0;
        while(!unusual) res+=dfs(s,_inf,t);
        return res;
    }
    void check(int s){
        for(auto&[v,rev,nrv,fw,w]:G[s]){
            if(w) throw false;
        }
    }
    auto get_result(int s,int t){
        lint ans=0;
        cir(u,1,G.size()-1){
            for(auto&[v,rev,nrv,fw,w]:G[u]){
                //clog<<u<<' '<<v<<' '<<fw<<' '<<w<<'\n';
                if(!nrv) continue;
                if(u==t) ans-=fw-w;
                if(v==t) ans+=fw-w;
            }
        }
        return ans;
    }
    auto size(){return G.size();}
    void pop(int u,int k) noexcept{
        while(k--) G[u].pop_back();
    }
    dinic(int n):G(n),cur(n),dist(n),gap(n){}
};
class minflow{
private:
    dinic gr;int rs,rt;
public:
    void insert(int u,int v,lint l,lint r){
        gr.insert(rs,v,l,r-l);gr.insert(u,rt,l,r-l);
        gr.insert(u,v,r-l,r);
    }
    auto get(int s,int t){
        gr.insert(s,t,_inf);
        gr.insert(t,s,_inf);
        gr.get(rs,rt);gr.check(rs);
        gr.pop(s,2);gr.pop(t,2);
        return gr.get(t,s),gr.get_result(s,t);
    }
    minflow(int n):gr(n+7),rs(0),rt(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,s,t;cin>>n>>m>>s>>t;
    minflow gr(n);
    cir(i,0,m){
        int u,v;lint l,r;cin>>u>>v>>l>>r;
        gr.insert(u,v,l,r);
    }
    try{
        auto gt=gr.get(s,t);
        cout<<true<<'\n'<<gt<<'\n';
    }catch(bool result){
        cout<<result<<'\n';
    }
    return 0;
}
