#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("tcrh.in");
ofstream ouf("tcrh.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
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
class dag{
private:
    vector<vector<int>> gr,rgr;
    vector<unordered_map<int,lint>> f;
    vector<int> in,vis,vaild;
    auto dfs(int u)->void{
        vis[u]=true;
        for(auto&i:gr[u]) if(vaild[i]){
            for(auto&[c,w]:f[u]) (f[i][c+1]+=w)%=MOD;
            if(!(--in[i])) dfs(i);
        }
    }
    auto init(int u){
        if(vaild[u]) return;
        vaild[u]=true;
        for(auto&i:rgr[u]) init(i);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);++in[v];
        rgr[v].emplace_back(u);
    }
    auto init(){
        f[0][0]=1;init((int)(gr.size())-1);
        cir(i,0,(int)(gr.size())) if(!vis[i]) dfs(i);
        return f.back();
    }
    dag(int _n):gr(_n),f(_n),in(_n),rgr(_n),vis(_n),vaild(_n){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,k;inf>>n>>m>>k;
    dag gr(n);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        gr.link(u,v);
    }
    vector<lint> fct(m+7,1),ifct(m+7);
    cir(i,1,m+7) fct[i]=fct[i-1]*i%MOD;
    ifct=fct;
    for(auto&i:ifct) i=math.inv(i);
    auto C=[&](auto a,auto b){
        if(a<b) return 0ll;
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    };
    const auto fx=gr.init();
    if(fx.empty()){
        cir(i,0,k+1) ouf<<0<<' ';
        ouf<<'\n';
    }else{
        auto sum=0ll;
        for(auto&[l,w]:fx) (sum+=w)%=MOD;
        const auto px=math.inv(sum);
        cir(i,0,k+1){
            auto ans=0ll;
            for(auto&[l,w]:fx)  (ans+=C(m-l,i)*w%MOD*px%MOD*math.inv(C(m,i)))%=MOD;
            ouf<<ans<<' ';
        }
        ouf<<'\n';
    }
    return 0;
}
