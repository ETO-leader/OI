#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    auto clear(){
        iota(f.begin(),f.end(),0);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
class graph{
private:
    vector<vector<int>> gr;
    vector<int> col;
    auto dfs(int u,int c){
        if(col[u]>-1){
            if(col[u]!=c) return false;
            return true;
        }
        col[u]=c;
        auto res=true;
        for(auto&i:gr[u]) res&=dfs(i,c^1);
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
    }
    auto check(){
        auto res=true;
        cir(i,0,(int)(gr.size())) if(col[i]==-1) res&=dfs(i,0);
        return res;
    }
    auto clear(){
        for(auto&x:gr) x.clear();
        fill(col.begin(),col.end(),-1);
    }
    graph(int _n):gr(_n),col(_n,-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> vx(n);
    cir(i,0,n) cir(j,0,n){
        int w;cin>>w;
        if(w) vx[i].emplace_back(j);
    }
    vector<lint> f(1<<n);
    dsu qwq(n);
    graph gr(n);
    cir(s,0,(1<<n)){
        qwq.clear();
        gr.clear();
        cir(i,0,n) if((s>>i)&1){
            for(auto&v:vx[i]) if((s>>v)&1){
                gr.link(i,v);
                qwq.merge(i,v);
            }
        }
        if(!gr.check()) continue;
        set<int> p;
        cir(i,0,n) if((s>>i)&1) p.emplace(qwq.findset(i));
        f[s]=(1ll<<p.size());
    }
    auto ans=0ll;
    cir(s,0,(1<<n)) ans+=f[s]*f[((1<<n)-1)^s];
    cout<<ans<<'\n';
    return 0;
}
