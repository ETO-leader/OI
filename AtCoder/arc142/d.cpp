#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
class tree{
private:
    vector<vector<int>> gr;
    vector<array<lint,3>> uf;
    auto dfs(int u,int f=-1)->void{
        uf[u][0]=1;
        auto pwx=1ll,pwy=1ll,cntx=0ll,cnty=0ll;
        for(auto&x:gr[u]) if(x!=f){
            dfs(x,u);
            const auto w=uf[x][2]*2%MOD;
            uf[u][1]=(uf[u][0]*uf[x][0]+uf[u][1]*uf[x][1])%MOD;
            (uf[u][0]*=uf[x][1])%=MOD;            
            uf[u][2]=((uf[u][2]*w)+(cnty*uf[x][0]))%MOD;
            cntx=((cntx*w)+(pwx*uf[x][0]))%MOD;
            (pwx*=w)%=MOD;
            cnty=((cnty*w)+(pwy*uf[x][0]))%MOD;
            (pwy*=w)%=MOD;
        }
        (uf[u][0]+=cntx)%=MOD;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto calc(){
        dfs(0);
        return (uf[0][1]+uf[0][2])*2%MOD;
    }
    tree(int _n):gr(_n),uf(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) []{
        int n;cin>>n;tree gr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        cout<<gr.calc()<<'\n';
    }();
    return 0;
}
