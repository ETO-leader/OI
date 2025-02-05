#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("maze.in");
ofstream ouf("maze.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class tree{
private:
    vector<map<int,lint>> f;
    vector<lint> uw,v;
    vector<int> rid;
    vector<string> sgn;
    const int d;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto in_sub(int v,int u){
        v<<=1;
        while(v) if((v>>=1)==u) return true;
        return false;
    }
    auto fw(int u,int w){
        if(f[u].empty()||f[u].rbegin()->first<w) return _infl;
        return f[u].lower_bound(w)->second;
    }
    // f(u,i) 表示 u 子树内最大未被支配的点的价值 >= i 的最小代价
    auto init(int u,int w){
        if(!in_sub(rid[w],u)) return fw(u,w);
        if(v[u]>-1) return f[u][w]=(v[u]<w?_infl:0);
        return f[u][w]=init(ls(u),w)+min(uw[u],init(rs(u),w));
    }
    auto sign(int u,string cur){
        if(v[u]>-1) return sgn[u]=cur,void();
        sign(ls(u),cur+'L');sign(rs(u),cur+'R');
    }
    auto dfs(int u,int dep,lint x,vector<int>&ans){
        if(v[u]>-1) return ans.emplace_back(v[u]),0ll;
        auto val=-1;
        for(auto&[i,w]:f[u]) if(w<x+1) val=i;
        const auto lw=fw(ls(u),val);
        const auto rw=fw(rs(u),val);
        if(sgn[rid[val]][dep]=='R'){
            const auto w=dfs(rs(u),dep+1,x-lw,ans);
            return w+dfs(ls(u),dep+1,x-w,ans);
        }else{
            const auto w=dfs(ls(u),dep+1,x-min(uw[u],rw),ans);
            if(rw+w>x) return w+dfs(rs(u),dep+1,x-w-uw[u],ans)+uw[u];
            return w+dfs(rs(u),dep+1,x-w,ans);
        }
    }
public:
    auto init(vector<lint> _uw,vector<lint> _uv,const lint w){
        cir(i,1,(1<<d)) uw[i]=_uw[i-1];
        cir(i,(1<<d),(1<<(d+1))) v[i]=_uv[i-(1<<d)],rid[v[i]]=i;
        for(auto wx=(1<<d);~wx;--wx) init(1,wx);
        sign(1,"");
        vector<int> ans;
        dfs(1,0,w,ans);
        return ans;
    }
    tree(int _d):f((1<<(_d+1))+7),uw((1<<(_d+1))+7),
        v((1<<(_d+1))+7,-1),rid((1<<(_d+1))+7),sgn((1<<(_d+1))+7),d(_d){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        int n;lint w;inf>>n>>w;
        tree tr(n);
        vector<lint> uw((1<<n)-1),uv(1<<n);
        for(auto&x:uw) inf>>x;
        for(auto&x:uv) inf>>x;
        const auto ans=tr.init(uw,uv,w);
        for(auto&i:ans) ouf<<i<<' ';
        ouf<<'\n';
    }();
    return 0;
}
