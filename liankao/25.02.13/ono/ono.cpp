#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("ono.in");
ofstream ouf("ono.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class dinic{
private:
    struct edge{
        int v,rev;lint w;
        edge(auto _v,auto _rev,auto _w):v(_v),rev(_rev),w(_w){}
    };
    vector<vector<edge>> gr;
    vector<int> dist,gap,cur;
    bool unusual;
    auto dfs(int u,lint rst,const auto vx){
        if(u==vx) return rst;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl]=gr[u][i];
            if(fl&&dist[v]+1==dist[u]){
                const auto w=dfs(v,min(rst,fl),vx);
                fl-=w;gr[v][rev].w+=w;res+=w;
                if(!(rst-=w)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,(int)(gr[v].size()),w);
        gr[v].emplace_back(u,(int)(gr[u].size())-1,0);
    }
    auto flow(auto s,auto t){
        auto res=0ll;unusual=false;
        while(!unusual) res+=dfs(s,_infl,t);
        return res;
    }
    dinic(int _n):gr(_n),dist(_n),gap(_n),cur(_n),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<lint> a(n);
    for(auto&i:a) inf>>i;
    const auto ucnt=n*4+m+7;
    const auto s=0,t=ucnt-1;
    dinic qwq(ucnt);
    auto ls=[&](auto u){return u*2;};
    auto rs=[&](auto u){return u*2+1;};
    auto build=[&](auto __self,int u,int l,int r){
        if(l==r) return qwq.link(u,t,a[l]);
        qwq.link(u,ls(u),_infl);
        qwq.link(u,rs(u),_infl);
        const auto mid=(l+r)/2;
        __self(__self,ls(u),l,mid);
        __self(__self,rs(u),mid+1,r);
    };
    build(build,1,0,n-1);
    auto link=[&](auto __self,int u,int l,int r,int ql,int qr,int f){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return qwq.link(f,u,_infl);
        const auto mid=(l+r)/2;
        __self(__self,ls(u),l,mid,ql,qr,f);
        __self(__self,rs(u),mid+1,r,ql,qr,f);
    };
    auto cnt=n*4-1;
    vector<tuple<int,int,lint>> q(m);
    for(auto&[l,r,w]:q){
        inf>>l>>r>>w;--l;--r;
        link(link,1,0,n-1,l,r,++cnt);
    }
    cir(i,0,n){
        auto cur=qwq;
        for(auto cnt=n*4-1;auto&[l,r,w]:q){
            ++cnt;
            if(r<i||i<l) continue;
            cur.link(s,cnt,w);
        }
        ouf<<cur.flow(s,t)<<'\n';
    }
    return 0;
}
