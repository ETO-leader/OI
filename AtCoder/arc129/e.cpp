#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
class dinic{
private:
    struct edge{
        int v;lint w;int rev;
        edge(int _v,lint _w,auto r):v(_v),w(_w),rev(r){}
    };
    vector<vector<edge>> gr;
    vector<int> dist,gap,cur;
    bool unusual;
    auto dfs(int u,const int vx,lint rst){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev]=gr[u][i];
            if(dist[u]==dist[v]+1){
                const auto fl=dfs(v,vx,min(rst,w));
                res+=fl;
                w-=fl;gr[v][rev].w+=fl;
                if(!(rst-=fl)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w,(int)(gr[v].size()));
        gr[v].emplace_back(u,0,(int)(gr[u].size())-1);
    }
    auto flow(int s,int t){
        auto res=0ll;
        while(!unusual) res+=dfs(s,t,_infl);
        return res;
    }
    dinic(int _n):gr(_n),dist(_n),gap(_n+7),cur(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector a(n,vector<int>(m)),c(n,vector<int>(m));
    cir(i,0,n) cir(j,0,m) cin>>a[i][j]>>c[i][j];
    cir(i,0,n){
        vector<int> ord(m);
        iota(ord.begin(),ord.end(),0);
        ranges::sort(ord,[&](auto u,auto v){
            return a[i][u]<a[i][v];
        });
        const auto ua=a[i],uc=c[i];
        cir(w,0,m) a[i][w]=ua[ord[w]],c[i][w]=uc[ord[w]];
    }
    dinic gr(n*(m+1)+7);
    vector cst(n,vector<int>(n));
    cir(i,0,n) cir(j,i+1,n) cin>>cst[i][j];
    cir(i,0,n) cir(j,0,i+1) cst[i][j]=cst[j][i];
    auto cnt=-1;
    const auto s=++cnt,t=++cnt;
    vector id(n,vector<int>(m+1));
    for(auto&x:id) for(auto&i:x) i=++cnt;
    cir(i,0,n){
        gr.link(s,id[i][0],_infl);
        cir(j,1,m+1) gr.link(id[i][j-1],id[i][j],c[i][j-1]);
        gr.link(id[i][m],t,_infl);
    }
    cir(i,0,n) cir(j,i+1,n){
        set<int> x;
        cir(c,0,m) x.emplace(a[i][c]),x.emplace(a[j][c]);
        const auto ar=vector(x.begin(),x.end());
        cir(k,1,(int)(ar.size())){
            const auto p=ranges::lower_bound(a[i],ar[k])-a[i].begin();
            const auto q=ranges::lower_bound(a[j],ar[k])-a[j].begin();
            if(p&&q<m) gr.link(id[j][q],id[i][p],cst[i][j]*(ar[k]-ar[k-1]));
            if(q&&p<m) gr.link(id[i][p],id[j][q],cst[i][j]*(ar[k]-ar[k-1]));
        }
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}
