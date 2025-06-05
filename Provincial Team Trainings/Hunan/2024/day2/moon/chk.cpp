#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("moon.in");
ofstream ouf("moon.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
mt19937_64 eng(251);
class graph{
public:
    class failsign{};
    vector<vector<pair<int,int>>> gr;
    vector<int> vis,dep;
    vector<int> stc;
    auto dfs(int u,int cdep,int lasid=-1){
        if(vis[u]){
            if((cdep-dep[u])&1) return;
            vector<int> res{u};
            while(stc.back()!=u) res.emplace_back(stc.back()),stc.pop_back();
            res.emplace_back(stc.back());
            throw res;
        }
        vis[u]=true;
        dep[u]=cdep;
        stc.emplace_back(u);
        shuffle(gr[u].begin(),gr[u].end(),eng);
        for(auto&[v,id]:gr[u]) if(id!=lasid){
            dfs(v,cdep+1,id);
        }
        vis[u]=false;
        stc.pop_back();
    }
public:
    auto link(int u,int v,int id){
        gr[u].emplace_back(v,id);
        gr[v].emplace_back(u,id);
    }
    auto check(){
        const auto s=uniform_int_distribution<int>(0,(int)(gr.size())-1)(eng);
        try{
            dfs(s,0);
            return vector<int>{};
        }catch(vector<int> res){
            return res;
        }
    }
    graph(int _n):gr(_n),vis(_n),dep(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<int> k(m);
    for(auto&i:k) inf>>i;
    if(m<21) [&]{
        vector<int> a(m);
        cir(i,0,m){
            auto s=0;
            cir(c,0,k[i]){
                int u;inf>>u;--u;
                s|=(1<<u);
            }
            a[i]=s;
        }
        cir(s,1,(1<<m)){
            auto cur=s;
            cir(i,0,m) if(s&(1<<i)) cur|=a[i];
            auto ncur=0;
            cir(i,0,m) if((!(s&(1<<i)))&&((cur&a[i])==a[i])) ncur|=a[i];
            if(cur==ncur){
                vector<int> ansx,ansy;
                cir(i,0,m) if(s&(1<<i)) ansx.emplace_back(i+1);
                cir(i,0,m) if((!(s&(1<<i)))&&((cur&a[i])==a[i])) ansy.emplace_back(i+1);
                ouf<<ansx.size()<<' '<<ansy.size()<<'\n';
                for(auto&i:ansx) ouf<<i<<' ';
                ouf<<'\n';
                for(auto&i:ansy) ouf<<i<<' ';
                ouf<<'\n';
                return;
            }
        }
        ouf<<-1<<'\n';
    }(); else [&]{
        graph gr(m);
        map<pair<int,int>,int> idx;
        cir(i,0,m){
            int u,v;inf>>u>>v;--u;--v;
            if(u>v) swap(u,v);
            if(idx.count({u,v})){
                ouf<<1<<' '<<1<<'\n';
                ouf<<idx[{u,v}]+1<<'\n';
                ouf<<i+1<<'\n';
                return;
            }
            idx[{u,v}]=i;
            gr.link(u,v,i);
        }
        cir(i,0,50000){
            const auto ux=gr.check();
            if(ux.empty()) continue;
            vector<int> ansx,ansy;
            cir(i,0,(int)(ux.size())){
                ((i&1)?ansx:ansy).emplace_back(idx[{min(ux[i],ux[i+1]),max(ux[i],ux[i+1])}]);
            }
            ouf<<ansx.size()<<' '<<ansy.size()<<'\n';
            for(auto&i:ansx) ouf<<i+1<<' ';
            ouf<<'\n';
            for(auto&i:ansy) ouf<<i+1<<' ';
            ouf<<'\n';
            return;
        }
        ouf<<-1<<'\n';
    }();
    return 0;
}
