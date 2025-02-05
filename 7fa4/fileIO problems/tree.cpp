#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("tree.in");
ofstream ouf("tree.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return u==f[u]?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> col,fr;
    auto dfs(int u,int w,int f=-1)->int{
        col[u]=w;
        fr[u]=f;
        for(auto&i:gr[u]) if(i!=f){
            col[u]+=dfs(i,-w,u);
        }
        return col[u];
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto checkcir(int rt,int v){
        dfs(rt,1);
        if(v>-1){
            auto vx=v;
            vector<int> a{col[vx]};
            while(vx!=rt) a.push_back(col[vx=fr[vx]]);
            if(a.size()&1){
                if(col[rt]&1) return -1ll;
                col[v]-=col[rt]/2;
                while(v!=rt) col[v=fr[v]]-=col[rt]/2;
            }else{
                if(col[rt]) return -1ll;
                sort(a.begin(),a.end());
                const auto mw=a[a.size()/2];
                col[v]-=mw;
                while(v!=rt) col[v=fr[v]]-=mw;
            }
        }else{
            if(col[rt]) return -1ll;
        }
        auto res=0ll;
        for(auto&i:col) res+=abs(i);
        return res;
    }
    tree(int _n):gr(_n),col(_n),fr(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;tree tr(n);
    dsu ds(n);
    auto rt=0,vx=-1;
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        if(ds.findset(u)==ds.findset(v)){
            rt=u;vx=v;continue;
        }
        ds.merge(u,v);
        tr.link(u,v);
    }
    ouf<<tr.checkcir(rt,vx)<<'\n';
    return 0;
}
