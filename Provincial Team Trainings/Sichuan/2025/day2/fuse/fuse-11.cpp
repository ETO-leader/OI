#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define inf cin
#define ouf cout
using lint=long long;
static constexpr auto MOD=994007158;
class tree{
private:
    vector<vector<int>> gr,vaild;
    vector<int> height,preht;
    vector<lint> fib;
    int init(int u,int f=-1){
        bool islf=true;
        height[u]=(int)gr.size()+7;
        for(auto&i:gr[u]) if(i!=f){
            height[u]=min(height[u],init(i,u)+1);
            islf=false;
        }
        for(auto&i:gr[u]) if(i!=f){
            if(gr[i].size()>3) vaild[u].emplace_back(i);
            else for(auto&x:vaild[i]) vaild[u].emplace_back(x);
        }
        if(islf) height[u]=0;
        return height[u];
    }
    void initpht(int u,int pht,int f=-1){
        pht=min(pht,height[u]);
        preht[u]=pht;
        for(auto&i:gr[u]) if(i!=f) initpht(i,pht,u);
    }
    lint check(int u,lint&ans,int curdep){
        if(preht[u]<curdep) return 1ll;
        lint res=fib[gr[u].size()];
        for(auto&i:vaild[u]){
            res=res*check(i,ans,curdep+1)%MOD;
        }
        ans=(ans+res)%MOD;
        return res;
    }
    lint dfs(int u,int f=-1){
        lint res=0;
        check(u,res,0);
        for(auto&i:gr[u]) if(i!=f) res=(res^dfs(i,u))%MOD;
        return res;
    }
public:
    void link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    lint init(){
        int n=(int)gr.size();
        fib.assign(n+7,1);
        cir(i,3,n+7) fib[i]=(fib[i-1]+fib[i-2])%MOD;
        init(0);
        initpht(0,height[0]);
        return dfs(0);
    }
    tree(int _n):gr(_n),height(_n),preht(_n),vaild(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;tree gr(n);
    cir(i,1,n){
        int f;inf>>f;--f;
        gr.link(i,f);
    }
    ouf<<gr.init()<<'\n';
    return 0;
}
