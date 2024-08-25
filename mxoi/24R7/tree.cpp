#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("tree.in");
ofstream fcout("tree.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=unsigned long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
    auto initfct(const int n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&i:ifct) i=inv(i);
    }
    auto C(const int a,const int b) const{
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
class tree{
private:
    vector<vector<int>> gr;
    vector<array<lint,2>> fx;
    vector<lint> c,w,cx;
    vector<bool> vis;
    auto dfs(int u,int f=-1)->void{
        fx[u][0]=cx[u];fx[u][1]=w[u];vis[u]=true;
        for(auto&i:gr[u]) if(i!=f){
            dfs(i,u);
            fx[u][1]=(fx[u][1]*(fx[i][0]+fx[i][1]*2)+fx[u][0]*fx[i][1])%MOD;
            (fx[u][0]*=(fx[i][0]+fx[i][1]*2))%=MOD;
        }
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto addw(int u,auto&f){++c[u];w[u]=f[c[u]];(cx[u]*=2)%=MOD;}
    auto check(){
        auto ans=1ll;
        cir(i,0,(int)(gr.size())) if((!vis[i])&&((!gr[i].empty())||w[i])){
            dfs(i);
            (ans*=fx[i][1])%=MOD;
        }
        return ans;
    }
    tree(int n):gr(n),fx(n),w(n),c(n),cx(n,1),vis(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;vector<vector<int>> adj(n);
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;--u;--v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    math.initfct(n+7);
    vector<int> inq(n);
    vector<lint> f(n);
    cir(i,1,n) cir(cu,0,i+1){
        (f[i]+=math.C(i,cu)*cu)%=MOD;
    }
    cir(i,0,n-1){
        int u;fcin>>u;--u;
        inq[u]=true;
        tree gr(n);
        cir(u,0,n) if(inq[u]){
            for(auto&v:adj[u]){
                if(inq[v]&&u>v) gr.insert(u,v);
                else if(!inq[v]) gr.addw(u,f);
            }
        }
        fcout<<gr.check()<<'\n';
    }
    return 0;
}
