#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("apple.in");
ofstream fcout("apple.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class subtq{
private:
    class tree{
    private:
        vector<vector<int>> gr;
    public:
        auto insert(int u,int v){
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
        auto dfs(int u,vector<vector<int>>&dis,int h=-1,int f=-1)->void{
            dis[++h].push_back(u);
            for(auto&i:gr[u]) if(i!=f) dfs(i,dis,h,u);
        }
        tree(int _n):gr(_n){}
    };
public:
    auto play(int n){
        tree gr(n);
        cir(i,0,n-1){
            int u,v;fcin>>u>>v;--u;--v;
            gr.insert(u,v);
        }
        string s;fcin>>s;
        mt19937_64 rnd(random_device().operator()());
        vector<uint64_t> rd(n);
        for(auto&i:rd) i=rnd();
        unordered_set<uint64_t> ans;
        cir(i,0,n) if(s[i]=='1'){
            vector<vector<int>> dis(n);
            gr.dfs(i,dis);
            auto wx=0ull;
            for(auto&x:dis){
                for(auto&u:x) wx^=rd[u];
                ans.insert(wx);
            }
        }
        fcout<<ans.size()<<'\n';
        return 0;
    }
};
class tree{
private:
    vector<vector<int>> gr;
    vector<int> fx,gx;
    struct node{
        int mx,smx;
        auto upd(int x){
            if(mx<x) swap(mx,smx),mx=x;
            else smx=max(smx,x);
        }
        node(int a=-1,int b=-1):mx(a),smx(b){}
    };
    vector<node> sdep;
    vector<int> fmx,fr;
    auto init(int u,int f=0)->node{
        sdep[u]=node(0,-1);fr[u]=f;
        for(auto&i:gr[u]) if(i!=f) sdep[u].upd(init(i,u).mx+1);
        if(!sdep[u].smx) sdep[u].smx=-1;
        return sdep[u];
    }
    auto dfsfx(int u,int f=0)->void{
        if(f){
            fmx[u]=fmx[f];
            ++fmx[u];
            for(auto&i:gr[f]) if(i!=u&&i!=fr[f]) fmx[u]=max(fmx[u],sdep[i].mx+2);
        }
        for(auto&i:gr[u]) if(i!=f) dfsfx(i,u);
    }
    auto dfsfg(int u,int f=0)->void{
        multiset q{sdep[u].mx,sdep[u].smx,fmx[u],0};
        fx[u]=*q.rbegin();
        gx[u]=*next(q.rbegin());
        for(auto&i:gr[u]) if(i!=f) dfsfg(i,u);
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(){
        init(1);dfsfx(1);dfsfg(1);
        auto ans=0ll;
        cir(i,1,(int)(gr.size())) ans+=min(fx[i],gx[i]+2);
        return ans;
    }
    tree(int _n):gr(_n+1),fx(_n+1),gx(_n+1),sdep(_n+1),fmx(_n+1),fr(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;
    if(n<10000) exit(subtq().play(n));
    tree gr(n);
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;
        gr.insert(u,v);
    }
    fcout<<gr.check()+1<<'\n';
    return 0;
}
