#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("fuse.in");
ofstream ouf("fuse.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=994007158;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> height,preht;
    vector<lint> fib;
    int init(int u,int f=-1){
        auto islf=true;
        height[u]=(int)(gr.size())+7;
        for(auto&i:gr[u]) if(i!=f) height[u]=min(height[u],init(i,u)+1),islf=false;
        if(islf) height[u]=0;
        return height[u];
    }
    void initpht(int u,int pht,int f=-1){
        pht=min(pht,height[u]);
        preht[u]=pht;
        for(auto&i:gr[u]) if(i!=f) initpht(i,pht,u);
    }
    lint check(int u,lint&ans,int curdep,int f=-1){
        if(preht[u]<curdep) return 1ll;
        auto res=fib[gr[u].size()];
        for(auto&i:gr[u]) if(i!=f){
            (res*=check(i,ans,curdep+1,u))%=MOD;
        }
        (ans+=res)%=MOD;
        return res;
    }
    lint dfs(int u,int f=-1){
        auto res=0ll;
        check(u,res,0,f);
        for(auto&i:gr[u]) if(i!=f) (res^=dfs(i,u))%=MOD;
        return res;
    }
public:
    void link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    lint init(){
        const auto n=(int)(gr.size());
        fib.resize(n+7,1);
        cir(i,3,n+7) fib[i]=(fib[i-1]+fib[i-2])%MOD;
        init(0);
        initpht(0,height[0]);
        return dfs(0);
    }
    bool ischain(){
        auto ok=true;
        cir(i,0,(int)(gr.size())) ok&=((int)(gr[i].size())<3);
        return ok;
    }
    tree(int _n):gr(_n),height(_n),preht(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;tree gr(n);
    cir(i,1,n){
        int f;inf>>f;--f;
        gr.link(i,f);
    }
    if(gr.ischain()){
        auto ans=0ll;
        cir(i,1,n+1) ans^=(i+1)/2;
        ouf<<ans<<'\n'; 
    }else{
        ouf<<gr.init()<<'\n';
    }
    return 0;
}
