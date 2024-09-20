#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("string.in");
ofstream fcout("string.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lf=long double;
static constexpr auto eps=1e-12l;
constexpr auto extinfoln(auto info){
    exit((fcout<<info<<'\n',0));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;fcin>>n>>m;lf p;fcin>>p;
    fcout<<fixed<<setprecision(15);    
    if(p<eps||p>1-eps) extinfoln(1);
    if(n>22) extinfoln(0);
    vector<string> as(n);
    for(auto&i:as) fcin>>i;
    for(auto&x:as) for(auto&i:x) i-='0';
    vector<lf> f(1<<n);f[(1<<n)-1]=1;
    for(auto s=(1<<n)-2;~s;--s){
        vector<array<int,2>> to(n*m+7);
        vector<int> endt(n*m+7,-1);
        auto cnt=0;
        cir(i,0,n) if(!(s&(1<<i))){
            auto u=0;
            for(auto&x:as[i]){
                if(!to[u][x]) to[u][x]=++cnt;
                u=to[u][x];
            }
            endt[u]=i;
        }
        auto dfs=[&](auto __self,int u)->lf {
            if(endt[u]>-1) return f[s|(1<<endt[u])];
            const auto lw=(to[u][0]?__self(__self,to[u][0]):0.0l);
            const auto rw=(to[u][1]?__self(__self,to[u][1]):0.0l);
            return max(lw*p+rw*(1-p),lw*(1-p)+rw*p);
        };
        f[s]=dfs(dfs,0);
    }
    fcout<<f[0]<<'\n';
    return 0;
}
