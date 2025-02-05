#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("cities.in");
ofstream ouf("cities.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=unsigned long long;
static constexpr auto MOD=998244353;
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> dfn,low,vis,vbcc;
    vector<pair<int,int>> stc;
    set<pair<int,int>> ans;
    int cnt,vcnt,ecnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++cnt;
        for(auto&[v,id]:gr[u]){
            if((!vis[id])&&(vbcc[id]<0)){
                vis[id]=true;stc.emplace_back(v,id);
            }
            if(!dfn[v]){
                tarjan(v);low[u]=min(low[u],low[v]);
                if(dfn[u]==low[v]){
                    ++vcnt;
                    ans.emplace(u,vcnt);
                    while(vis[id]){
                        const auto[vx,idi]=stc.back();stc.pop_back();
                        vis[idi]=false;ans.emplace(vx,vcnt);vbcc[idi]=vcnt;
                    }
                }
            }else{
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
public:
    auto link(int u,int v){
        ++ecnt;
        gr[u].emplace_back(v,ecnt);
        gr[v].emplace_back(u,ecnt);
    }
    auto check(){
        tarjan(0);return ans;
    }
    graph(int _n,int _m):gr(_n),dfn(_n),low(_n),vis(_m),vbcc(_m,-1),cnt(0),ecnt(-1),vcnt(-1){}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> ntype,ord;
    vector<lint> siz,fx;
    const int n;
    int root;
    auto init(int u,int f=-1)->int{
        siz[u]=ntype[u];
        for(auto&i:gr[u]) if(i!=f) siz[u]+=init(i,u);
        return siz[u];
    }
    auto get_g(int u,const auto sizx,int f=-1)->void{
        auto mxsiz=sizx-siz[u];
        for(auto&i:gr[u]) if(i!=f) get_g(i,sizx,u),mxsiz=max(mxsiz,siz[i]);
        if(mxsiz<sizx/2+1) throw u;
    }
    auto init_ord(int u,int f=-1)->void{
        ord.emplace_back(u);
        for(auto&i:gr[u]) if(i!=f) init_ord(i,u);
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
    }
    auto dfs_norm(const auto k){
        for(auto&u:ord){
            if(siz[u]<k){
                fx[u]=0;continue;
            }
            if(ntype[u]){
                fx[u]=1;
                auto csiz=1;
                for(auto&i:gr[u]){
                    if(siz[i]<k) csiz+=siz[i];
                    else fx[u]&=fx[i];
                }
                fx[u]&=(csiz==k);
            }else{
                fx[u]=1;
                for(auto&i:gr[u]) fx[u]&=fx[i];
            }
        }
    }
    auto dfs_extra(const auto k){
        for(auto&u:ord){
            if(siz[u]<k){
                fx[u]=0;continue;
            }
            if(ntype[u]){
                fx[u]=1;
                auto csiz=1,vcnt=0;
                for(auto&i:gr[u]){
                    if(siz[i]<k) csiz+=siz[i];
                    else if(siz[i]==k) fx[i]?++vcnt:csiz+=siz[i];
                    else (fx[u]*=fx[i])%=MOD;
                }
                auto rfx=0ull;
                if(csiz==1) rfx+=fx[u]*vcnt;
                if(csiz==k) rfx+=fx[u];
                if(csiz==k+1) rfx+=fx[u];
                fx[u]=rfx%MOD;
            }else{
                fx[u]=1;
                for(auto&i:gr[u]){
                    (fx[u]*=fx[i])%=MOD;
                }
            }
        }
    }
public:
    auto link(int u,int vbcc){
        ntype[u]=true;
        gr[u].emplace_back(vbcc+n);
        gr[vbcc+n].emplace_back(u);
    }
    auto init(){
        init(0);
        try{
            get_g(0,siz[0]);
            abort();
        }catch(int r){
            root=r;
        }
        init(root);
        init_ord(root);
        reverse(ord.begin(),ord.end());
    }
    auto check_norm(){
        auto res=0;
        cir(i,1,n) if(!(n%i)) dfs_norm(i),res+=fx[root];
        return res;
    }
    auto check_extra(){
        auto res=0ull;
        vector<int> vaild(n+7);
        cir(i,1,n+1){
            vaild[n/i]=true;
            if(!(n%i)) vaild[n/i-1]=true;
        }
        cir(i,1,min(n/2+1,n-1)) if(vaild[i]){
            dfs_extra(i);(res+=fx[root])%=MOD;
        }
        return (res+MOD+1-check_norm())%MOD;
    }
    tree(int _n):gr(_n<<1),ntype(_n<<1),siz(_n<<1),fx(_n<<1),n(_n),root(-1){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,k;inf>>n>>m>>k;
    graph gr(n,m);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        gr.link(u,v);
    }
    const auto es=gr.check();
    tree tr(n);
    for(auto&[u,vbcc]:es) tr.link(u,vbcc);
    tr.init();
    if(!k){
        ouf<<tr.check_norm()<<'\n';
    }else{
        ouf<<tr.check_extra()<<'\n';
    }
    return 0;
}
